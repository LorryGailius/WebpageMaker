#ifndef TIMELINE_H
#define TIMELINE_H

#include <html_doc.h>
#include <user_input.h>

HTML_doc_t *create_timeline_html(char *title, char *description, data_t *data, size_t post_cnt);

#endif /* TIMELINE_H */