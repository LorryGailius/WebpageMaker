#include <timeline.h>

HTML_doc_t *create_timeline_html(char *title, char *description, data_t *data, size_t size) {
    // head elements
    elem_t* head_elems[3];
    head_elems[0] = create_tag_element(TAG_META);
    push_element_attribute(head_elems[0], create_attribute(ATTR_NAME, "viewport"));
    push_element_attribute(head_elems[0], create_attribute(ATTR_CONTENT, "width=device-width, initial-scale=1.0"));

    head_elems[1] = create_tag_element(TAG_TITLE);
    push_element(head_elems[1], create_text_element(title ? title : ""));

    head_elems[2] = create_timeline_style();
    // body elements
    elem_t *body_elems[] = {
        create_tag_element(TAG_H1),
        create_tag_element(TAG_H3),
        create_timeline_post_section(data, size),
        create_timeline_footer()
    };

    if(title != NULL) {
        const char * attr_str = "text-align: center; padding-top: 1%;color:white;font-size:350%;";
        push_element_attribute(body_elems[0], create_attribute(ATTR_STYLE, attr_str));
        push_element(body_elems[0], create_text_element(title));
    }

    if(description != NULL) {
        const char* attr_str = "text-align: center; padding-bottom: 5%;color:white;";
        push_element_attribute(body_elems[1], create_attribute(ATTR_STYLE, attr_str));
        push_element(body_elems[1], create_text_element(description));
    }

    push_element_attribute(body_elems[2], create_attribute(ATTR_CLASS, "timeline"));
    return create_doc(head_elems, 3, body_elems, 4);
}

elem_t* create_timeline_post_section(data_t *data, size_t size) {
    elem_t *section = create_tag_element(TAG_DIV);
    for(size_t i = 0; i < size; ++i) {
        if((data[i].header == NULL) && (data[i].description == NULL) && (data[i].image == NULL)) continue;

        elem_t *inside_div = create_tag_element(TAG_DIV);
        attr_t *idiv_class = create_attribute(ATTR_CLASS, "content");   
        push_element_attribute(inside_div, idiv_class);

        if(data[i].header != NULL) {
            elem_t *h2 = create_tag_element(TAG_H2);
            push_element(h2, create_text_element(data[i].header));
            push_element(inside_div, h2);
        }

        if(data[i].description != NULL) {
            elem_t *par = create_tag_element(TAG_PAR);
            push_element(par, create_text_element(data[i].description));
            push_element(inside_div, par);
        }

        if(data[i].image != NULL) {
            elem_t *img = create_tag_element(TAG_IMG);
            const char* attr_str = "height: 100%; width: 100%; object-fit: contain;display:block;margin:auto";
            push_element_attribute(img, create_attribute(ATTR_SRC, data[i].image));
            push_element_attribute(img, create_attribute(ATTR_STYLE, attr_str));
            push_element(inside_div, img);
        }

        elem_t *outside_div = create_tag_element(TAG_DIV);
        const char *val = ((i % 2) == 0)? "container left":"container right";
        attr_t *odiv_class = create_attribute(ATTR_CLASS, val);
        push_element_attribute(outside_div, odiv_class);
        push_element(outside_div, inside_div);
        push_element(section, outside_div);
    }
    return section;
}

elem_t* create_timeline_style() {
    FILE *handle = fopen("bin/style.css", "rb");
    if(handle == NULL) {
        fprintf(stderr, "create_timeline_style(): /bin/style.css is missing, returned NULL.\n");
        return NULL;
    }
    size_t file_size = get_file_size("bin/style.css");
    if(file_size == 0) {
        fprintf(stderr, "create_timeline_style(): /bin/style.css is empty, style is NULL.\n");
        return NULL;
    }

    char *src = (char*) malloc(file_size);
    fread(src, sizeof(char), file_size, handle);
    fclose(handle);

    elem_t *style = create_tag_element(TAG_STYLE);
    push_element(style, create_text_element(src));
    return style;
}

elem_t* create_timeline_footer() {
    elem_t *footer = create_tag_element(TAG_FOOTER);
    elem_t *div = create_tag_element(TAG_DIV);
    attr_t *attrib = create_attribute(ATTR_CLASS, "footer-content");
    push_element_attribute(div, attrib);
    // footer header
    elem_t *heading = create_tag_element(TAG_H3);
    elem_t *heading_text = create_text_element("WebpageMaker");
    push_element(heading, heading_text);
    push_element(div, heading);
    // footer paragraph
    elem_t *par = create_tag_element(TAG_PAR);
    elem_t *par_text = create_text_element("Made with<a href=\"https://github.com/LorryGailius/WebpageMaker\">WebpageMaker</a>");
    push_element(par, par_text);
    push_element(div, par);
    push_element(footer, div);
    return footer;
}