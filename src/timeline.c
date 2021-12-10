#include <timeline.h>

HTML_doc_t *create_timeline_html(size_t post_cnt) {

    elem_t* head_elems[2];
    head_elems[0] = create_tag_element(TAG_META);
    head_elems[1] = create_tag_element(TAG_LINK);

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

    elem_t *body_elems[3] = {
        create_tag_element(TAG_H1),
        create_tag_element(TAG_H3),
        create_tag_element(TAG_DIV)
    };

    elem_t *h_text = create_text_element("Timeline name");
    attr_t *h_attr = create_attribute(ATTR_STYLE, "text-align: center; padding-top: 1%;color:white;font-size:350%;");
    push_element_attribute(body_elems[0], h_attr);
    push_element(body_elems[0], h_text);

    elem_t *d_text = create_text_element("Timeline description");
    attr_t *d_attr = create_attribute(ATTR_STYLE, "text-align: center; padding-bottom: 5%;color:white;");
    push_element_attribute(body_elems[1], d_attr);
    push_element(body_elems[1], d_text);

    attr_t *tl_attr = create_attribute(ATTR_CLASS, "timeline");
    push_element_attribute(body_elems[2], tl_attr);

    for(size_t i = 0; i < post_cnt; ++i) {
        elem_t *year = create_text_element("2021");
        elem_t *h2 = create_tag_element(TAG_H2);
        push_element(h2, year);
        elem_t *text = create_text_element(LOREM_IPSUM_STR);
        elem_t *par =  create_tag_element(TAG_PAR);
        push_element(par, text);
        elem_t *img = create_tag_element(TAG_IMG);
        attr_t *img_src = create_attribute(ATTR_SRC, "3.jpg");
        attr_t *img_style = create_attribute(ATTR_STYLE, "height: 100%; width: 100%; object-fit: contain;display:block;margin:auto");
        push_element_attribute(img, img_src);
        push_element_attribute(img, img_style);

        elem_t *inside_div = create_tag_element(TAG_DIV);
        attr_t *idiv_class = create_attribute(ATTR_CLASS, "content");   
        push_element_attribute(inside_div, idiv_class);
        push_element(inside_div, h2);
        push_element(inside_div, par);
        push_element(inside_div, img);

        elem_t *outside_div = create_tag_element(TAG_DIV);
        const char *val = ((i % 2) == 0)? "container left":"container right";
        attr_t *odiv_class = create_attribute(ATTR_CLASS, val);
        push_element_attribute(outside_div, odiv_class);
        push_element(outside_div, inside_div);
        push_element(body_elems[2], outside_div);
    }

    HTML_doc_t *doc = create_doc(head_elems, 2, body_elems, 3);
    return doc;
}

css_doc_t *create_timeline_css() {
    return NULL;
}