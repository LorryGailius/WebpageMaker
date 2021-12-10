#ifndef TIMELINE_H
#define TIMELINE_H

#include <html_doc.h>
#include <css_doc.h>

#define LOREM_IPSUM_STR "Lorem ipsum dolor sit amet, quo ei simul congue exerci, ad nec admodum perfecto mnesarchum, vim ea mazim fierent detracto. Ea quis iuvaret expetendis his, te elit voluptua dignissim per, habeo iusto primis ea eam."

HTML_doc_t *create_timeline_html(size_t post_cnt);
css_doc_t *create_timeline_css();

#endif /* TIMELINE_H */