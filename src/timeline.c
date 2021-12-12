#include <timeline.h>

HTML_doc_t *create_timeline_html(char *title, char *description, data_t *data, size_t post_cnt) {
    elem_t* head_elems[4];
    head_elems[0] = create_tag_element(TAG_META);
    head_elems[1] = create_tag_element(TAG_LINK);
    head_elems[2] = create_tag_element(TAG_TITLE);
    head_elems[3] = create_tag_element(TAG_STYLE);

    attr_t *meta_attr[2];
    meta_attr[0] = create_attribute(ATTR_NAME, "viewport");
    meta_attr[1] = create_attribute(ATTR_CONTENT, "width=device-width, initial-scale=1.0");
    
    attr_t *link_attr[2];
    link_attr[0] = create_attribute(ATTR_REL, "stylesheet");
    link_attr[1] = create_attribute(ATTR_HREF, "style.css");

    push_element_attribute(head_elems[0], meta_attr[0]);
    push_element_attribute(head_elems[0], meta_attr[1]);

    push_element_attribute(head_elems[1], link_attr[0]);
    push_element_attribute(head_elems[1], link_attr[1]);

    elem_t *title_elem = create_text_element(title);
    push_element(head_elems[2], title_elem);

    FILE *css_file = fopen("bin/style.css", "rb");
    char *src = NULL;
    if(css_file == NULL) {
        log_msg("create_timeline_html(): /bin/style.css is missing.");
    } else {
        log_msg("create_timeline_html(): opened /bin/style.css");
        fseek(css_file, 0, SEEK_END);
        size_t src_size = ftell(css_file);
        rewind(css_file);
        src = (char*) malloc(src_size);
        size_t read = fread(src, sizeof(char), src_size, css_file);
        if(read != src_size) {
            log_msg("create_timeline_html(): /bin/style.css could not be read.");
        } else {
            log_msg("create_timeline_html(): /bin/style.css has been read.");
        }
        fclose(css_file);
        log_msg("create_timeline_html(): /bin/style.css has been closed.");
    }
    
    elem_t *style_src = create_text_element(src);
    push_element(head_elems[3], style_src);
    elem_t *body_elems[] = {
        create_tag_element(TAG_H1),
        create_tag_element(TAG_H3),
        create_tag_element(TAG_DIV),
        create_tag_element(TAG_FOOTER)
    };

    elem_t *h_text = create_text_element(title);
    attr_t *h_attr = create_attribute(ATTR_STYLE, "text-align: center; padding-top: 1%;color:white;font-size:350%;");
    push_element_attribute(body_elems[0], h_attr);
    push_element(body_elems[0], h_text);

    elem_t *d_text = create_text_element(description);
    attr_t *d_attr = create_attribute(ATTR_STYLE, "text-align: center; padding-bottom: 5%;color:white;");
    push_element_attribute(body_elems[1], d_attr);
    push_element(body_elems[1], d_text);

    attr_t *tl_attr = create_attribute(ATTR_CLASS, "timeline");
    push_element_attribute(body_elems[2], tl_attr);

    for(size_t i = 0; i < post_cnt; ++i) {

        if(data[i].header == NULL && data[i].description == NULL &&data[i].image == NULL) continue;

        elem_t *inside_div = create_tag_element(TAG_DIV);
        attr_t *idiv_class = create_attribute(ATTR_CLASS, "content");   
        push_element_attribute(inside_div, idiv_class);

        if(data[i].header != NULL) {
            elem_t *year = create_text_element(data[i].header);
            elem_t *h2 = create_tag_element(TAG_H2);
            push_element(h2, year);
            push_element(inside_div, h2);
        }

        if(data[i].description != NULL) {
            elem_t *text = create_text_element(data[i].description);
            elem_t *par =  create_tag_element(TAG_PAR);
            push_element(par, text);
            push_element(inside_div, par);
        }

        if(data[i].image != NULL) {
            elem_t *img = create_tag_element(TAG_IMG);
            attr_t *img_src = create_attribute(ATTR_SRC, data[i].image);
            attr_t *img_style = create_attribute(ATTR_STYLE, "height: 100%; width: 100%; object-fit: contain;display:block;margin:auto");
            push_element_attribute(img, img_src);
            push_element_attribute(img, img_style);
            push_element(inside_div, img);
        }

        elem_t *outside_div = create_tag_element(TAG_DIV);
        const char *val = ((i % 2) == 0)? "container left":"container right";
        attr_t *odiv_class = create_attribute(ATTR_CLASS, val);
        push_element_attribute(outside_div, odiv_class);
        push_element(outside_div, inside_div);
        push_element(body_elems[2], outside_div);
    }

    // footer magic

    elem_t *f_div = create_tag_element(TAG_DIV);
    attr_t *f_div_class = create_attribute(ATTR_CLASS, "footer-content");
    push_element_attribute(f_div, f_div_class);
    push_element(body_elems[3], f_div);
    // footer header 3
    elem_t *f_h3 = create_tag_element(TAG_H3);
    elem_t *f_h3_text = create_text_element("WebpageMaker");
    push_element(f_h3, f_h3_text);
    push_element(f_div, f_h3);

    elem_t *f_p = create_tag_element(TAG_PAR);
    // inside text tags are not supported
    elem_t *f_p_text = create_text_element("Made with<a href=\"https://github.com/LorryGailius/WebpageMaker\">WebpageMaker</a>");
    push_element(f_p, f_p_text);
    push_element(f_div, f_p);

    HTML_doc_t *doc = create_doc(head_elems, 4, body_elems, 4);
    if(doc == NULL) {
        log_msg("create_timeline_html(): doc could not be created, returned NULL.");
        return NULL;
    }
    log_msg("create_timeline_html(): doc successfully created.");
    return doc;
}