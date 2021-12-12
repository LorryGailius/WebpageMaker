#ifndef TIMELINE_H
#define TIMELINE_H

#include <html_doc.h>
#include <user_input.h>

HTML_doc_t *create_timeline_html(char *title, char *description, data_t *data, size_t size);

elem_t* create_timeline_post_section(data_t *data, size_t size);

elem_t* create_timeline_style();

elem_t* create_timeline_footer();

#endif /* TIMELINE_H */