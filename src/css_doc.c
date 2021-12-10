#include <css_doc.h>

const char* property_table[PROP_NUM] = {
    "none",
    "background-color",
    "border-radius",
    "padding-right",
    "border-width",
    "padding-left",
    "border-color",
    "max-width",
    "position",
    "padding",
    "content",
    "z-index",
    "margin",
    "height",
    "border",
    "width",
    "right",
    "left",
    "top",
    "font-family"
};

css_decl_t* create_css_decl(uint8_t prop_index, const char* value) {
    css_decl_t *decl = (css_decl_t*) malloc(sizeof(css_decl_t));
    if(decl == NULL) {
        log_msg("create_css_decl(): malloc failed, returned NULL!");
        return NULL;
    }
    decl->prop_index = prop_index;
    size_t len = strlen(value);
    decl->value = (char*) malloc((len + 1) * sizeof(char));
    if(decl->value == NULL) {
        log_msg("create_css_decl(): malloc failed, declaration value is NULL!");
    }
    memcpy(decl->value, value, len + 1);
    return decl;
}

void destroy_css_decl(css_decl_t *decl) {
    char *val = decl->value;
    if(val != NULL) free(val);
    free(decl);
}

css_rule_t* create_css_rule(const char* selector) {
    css_rule_t *rule = (css_rule_t*) malloc(sizeof(css_rule_t));

    size_t len = strlen(selector);
    rule->selector = (char*) malloc((len + 1) * sizeof(char));
    if(rule->selector == NULL) {
        log_msg("create_css_rule(): malloc failed, rule selector is NULL!");
    }
    memcpy(rule->selector, selector, len + 1);
    if(rule == NULL) {
        log_msg("create_css_rule(): malloc failed, returned NULL!");
        return NULL;
    }
    for(size_t i = 0; i < MAX_DECLARATIONS; ++i) {
        rule->decls[i] = NULL;
    }
    rule->decl_cnt = 0;
    return rule;
}

void destroy_css_rule(css_rule_t *rule) {
    for(size_t i = 0; i < rule->decl_cnt; ++i) {
        free(rule->decls[i]);
    }
    free(rule);
}

void css_rule_push_decl(css_rule_t *rule, css_decl_t *decl) {
    if(rule->decl_cnt == MAX_DECLARATIONS) {
        log_msg("css_rule_push_decl(): rule already has a maximum number of declarations!");
        return;
    }
    rule->decls[rule->decl_cnt++] = decl;
}

css_doc_t* create_css_doc() {
    css_doc_t *doc = (css_doc_t*) malloc(sizeof(css_doc_t));
    if(doc == NULL) {
        log_msg("create_css_doc(): malloc failed, returned NULL!");
        return NULL;
    }
    for(size_t i = 0; i < MAX_RULES; ++i) {
        doc->rules[i] = NULL;
    }
    doc->rule_cnt = 0;
    return doc;
}

void destroy_css_doc(css_doc_t *doc) {
    for(size_t i = 0; i < doc->rule_cnt; ++i) {
        free(doc->rules[i]);
    }
    free(doc);
}

void css_doc_push_rule(css_doc_t *doc, css_rule_t *rule) {
    if(rule->decl_cnt == MAX_DECLARATIONS) {
        log_msg("css_doc_push_rule(): doc already has a maximum number of rules!");
        return;
    }
    doc->rules[doc->rule_cnt++] = rule;
}

void print_css_decl(css_decl_t *decl, FILE *const os) {
    fprintf(os, "\t%s: %s;\n", property_table[decl->prop_index], decl->value);
}

void print_css_rule(css_rule_t *rule, FILE *const os) {
    fprintf(os, "%s {\n", rule->selector);
    for(size_t i = 0; i < rule->decl_cnt; ++i) {
        print_css_decl(rule->decls[i], os);
    }
    fprintf(os, "}\n");
}

void print_css_doc(css_doc_t *doc, FILE *const os) {
    for(size_t i = 0; i < doc->rule_cnt; ++i) {
        print_css_rule(doc->rules[i], os);
    }
    fprintf(os, "\n");
}