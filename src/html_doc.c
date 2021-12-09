#include <html_doc.h>

const char *tag_table[TAG_NUM] = {
    "none",
    "html",
    "head",
    "body",
    "meta",
    "link",
    "img",
    "div",
    "h1",
    "h2",
    "p",
    "h3"
};

const char *attr_table[ATTR_NUM] = {
    "content",
    "class",
    "style",
    "name",
    "href",
    "src",
    "rel"
};

FILE *logger = NULL;

void init_logger(const char* file_name) {
    logger = fopen(file_name, "wb");
    if(logger == NULL) {
        printf("init_logger(): Failed to create logger file, logger set to stdout!\n");
        logger = stdout;
    }
}

void close_logger() {
    fclose(logger);
}

attr_t* create_attribute(uint8_t attr_index, const char* value) {
    attr_t *attr = (attr_t*) malloc(sizeof(attr_t));
    if(attr == NULL) {
        log_msg("create_attribute(): malloc failed, attribute is NULL!");
        return NULL;
    }
    attr->attr_index = attr_index;
    // dynamicly allocate value
    size_t val_len = strlen(value);
    attr->value = (char*) malloc((val_len + 1) * sizeof(char));
    if(attr->value == NULL) {
        log_msg("create_attribute(): malloc failed, attribute->value is NULL!");
    } else {
        memcpy(attr->value, value, val_len + 1);
    }
    return attr;
}

void destroy_attribute(attr_t *attribute) {
    char *val = attribute->value;
    if(val) free(val);
    free(attribute);
}

elem_t* create_element() {
    elem_t *elem = (elem_t*) malloc(sizeof(elem_t));
    if(elem == NULL) {
        log_msg("create_element(): malloc failed.");
        return NULL;
    }
    elem->tag_index = TAG_NONE;
    elem->text = NULL;
    elem->attr_cnt = 0;
    elem->child_cnt = 0;
    for(size_t i = 0; i < MAX_CHILDREN; ++i) {
        elem->children[i] = NULL;
    }
    for(size_t i = 0; i < MAX_ATTRIBUTES; ++i) {
        elem->attributes[i] = NULL;
    }
    return elem;
}

elem_t* create_tag_element(uint16_t tag_index) {
    elem_t *elem = create_element();
    elem->tag_index = tag_index;
    return elem;
}

elem_t* create_text_element(const char* text) {
    elem_t *elem = create_element();
    size_t len = strlen(text);
    elem->text = (char*) malloc((len + 1) * sizeof(char));
    if(elem->text == NULL) {
        log_msg("create_text_element(): malloc failed, element text is NULL!");
    }
    memcpy(elem->text, text, len + 1);
    return elem;
}

void push_element_attribute(elem_t *element, attr_t *attribute) {
    if(element->attr_cnt == MAX_ATTRIBUTES) {
        log_msg("push_element_attribute(): tag element already has a maximum number of attributes!");
        return;
    }
    if(element->text != NULL) {
        log_msg("push_element_attribute(): text element cannot have attributes!");
        return;
    }
    element->attributes[element->attr_cnt++] = attribute;
}

void push_element(elem_t *element, elem_t* child) {
    if(element->text != NULL) {
        log_msg("push_element(): text element cannot have children\n");
        return;
    }
    if(element->child_cnt == MAX_CHILDREN) {
        log_msg("push_element(): tag element already has a maximum number of children!\n");
        return;
    }
    element->children[element->child_cnt++] = child;
}

void destroy_element(elem_t *element) {
    // free attributes
    for(size_t i = 0; i < element->attr_cnt; ++i) {
        destroy_attribute(element->attributes[i]);
    }
    if(element->text) free(element->text);
    free(element);
}

void destroy_subelements(elem_t *element) {
    for(size_t i = 0; element->children[i]; ++i) {
        destroy_subelements(element->children[i]);
    }
}

HTML_doc_t* create_doc(
    elem_t *head_elem[MAX_CHILDREN], 
    size_t head_elem_cnt,
    elem_t *body_elem[MAX_CHILDREN],
    size_t body_elem_cnt
) {
    elem_t *html = create_tag_element(TAG_HTML);
    elem_t *head = create_tag_element(TAG_HEAD);
    elem_t *body = create_tag_element(TAG_BODY);

    if(html == NULL) return NULL;
    if(head == NULL) return NULL;
    if(body == NULL) return NULL;

    for (size_t i = 0; i < head_elem_cnt; ++i) {
        push_element(head, head_elem[i]);
    }
    for (size_t i = 0; i < body_elem_cnt; ++i) {
        push_element(body, body_elem[i]);
    }

    push_element(html, head);
    push_element(html, body);

    HTML_doc_t *doc = (HTML_doc_t*) malloc(sizeof(HTML_doc_t));
    if(doc == NULL) {
        log_msg("HTML_doc_t(): malloc failed, function terminated");
    }
    doc->html = html;
    return doc;
}

void destroy_doc(HTML_doc_t *doc) {
    destroy_subelements(doc->html);
    destroy_element(doc->html);
    free(doc);
}

void print_doc(HTML_doc_t *doc, FILE *os) {
    if (os == NULL) {
        log_msg("print_doc(): os is NULL, os set to stdout");
        os = stdout;
    }
    fprintf(os, "<!DOCTYPE html>\n");
    if (doc->html == NULL) {
        log_msg("print_doc(): doc->html is NULL, function terminated");
        return;
    }
    print_element(doc->html, os, 0);
}

void print_element(elem_t *element, FILE *const os, uint8_t ident_level) {
    if(element == NULL) {
        log_msg("print_element(): element is NULL, function terminated!");
        return;
    }
    // decide if it's a tag or text element
    if(element->text != NULL) {
        // print idents
        print_idents(ident_level, os);
        fprintf(os, "%s\n", element->text);
    }
    else {
        // it's a tag
        // print opening tag
        print_idents(ident_level, os);
        fprintf(os, "<%s", tag_table[element->tag_index]);
        // print attributes
        for(size_t i = 0; element->attributes[i]; ++i) {
            attr_t *attr = element->attributes[i];
            fprintf(os, " %s=\"%s\"", attr_table[attr->attr_index], attr->value);
        }
        fprintf(os, ">\n");
        // print children
        for(size_t i = 0; element->children[i]; ++i) {
            print_element(element->children[i], os, ident_level + 1);
        }
        // print closing tag
        print_idents(ident_level, os);
        fprintf(os, "</%s>\n", tag_table[element->tag_index]);
    }
}

void print_idents(uint8_t ident_level, FILE *const os) {
    for(uint8_t i = 0; i < ident_level; ++i) {
        fputc('\t', os);
    }
}

void log_msg(const char* msg) {
    fprintf(logger, "[%s] %s\n", __TIME__, msg);
    fflush(logger);
}