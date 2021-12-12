// structures in these files are based on DOM tree
// https://javascript.info/dom-nodes

#ifndef HTML_DOC_H
#define HTML_DOC_H

// system headers
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// user headers
#include <logger.h>
#include <file_utils.h>

// tag indices
#define TAG_NONE    0
#define TAG_HTML	1
#define TAG_HEAD	2
#define TAG_BODY	3
#define TAG_META	4
#define TAG_LINK	5
#define TAG_IMG		6
#define TAG_DIV		7
#define TAG_H1		8
#define TAG_H2		9
#define TAG_PAR		10
#define TAG_H3		11
#define TAG_STYLE	12
#define TAG_NUM		13

// attribute indices
#define ATTR_CONTENT	0
#define ATTR_CLASS		1
#define ATTR_STYLE		2
#define ATTR_NAME		3
#define ATTR_HREF		4
#define ATTR_SRC		5
#define ATTR_REL		6
#define ATTR_NUM		7

// tag and attribute string tables
extern const char *tag_table[TAG_NUM];
extern const char *attr_table[ATTR_NUM];

// HTML attribute structure
typedef struct attr_t {
    uint8_t attr_index; // attribute name index in attr_table
    char *value;        // asigned attribute value
} attr_t;

attr_t* create_attribute(uint8_t attr_index, const char* value);
void destroy_attribute(attr_t *attribute);

#define MAX_CHILDREN 100
#define MAX_ATTRIBUTES 10


#define ELEM_TEXT 0
#define ELEM_UNARY 1
#define ELEM_BINARY 2

// HTML element
typedef struct elem_t {
    uint8_t tag_index; 			            // tag name index in tag_table
    attr_t* attributes[MAX_ATTRIBUTES];        // attributes
    size_t attr_cnt;
    struct elem_t* children[MAX_CHILDREN];	// children elements
    size_t child_cnt;   			        // initialized (non NULL) child count
    char *text;         			        // element can also have text
    uint8_t elem_type;
} elem_t;

elem_t* create_element();
elem_t* create_tag_element(uint16_t tag_index);
elem_t* create_text_element(const char* text);
void push_element_attribute(elem_t *element, attr_t *attribute);
// pushes 'child' element to the back of 'elements' children
void push_element(elem_t *element, elem_t* child);
// frees 'element' and its attributes
void destroy_element(elem_t *element);
// frees all elements children, their children ans so on until the end 
// (note that it does not free the element itself)
void destroy_subelements(elem_t *element);

typedef struct HTML_doc_t {
    elem_t *html; // html tag node
} HTML_doc_t;

// creates an HTML document structure given the head and body elemnts 
HTML_doc_t* create_doc(
    elem_t *head_elem[MAX_CHILDREN], 
    size_t head_elem_cnt,
    elem_t *body_elem[MAX_CHILDREN],
    size_t body_elem_cnt
);
// frees HTML document
void destroy_doc(HTML_doc_t *doc);
// printing
void print_doc(HTML_doc_t *doc, FILE *os);
void print_element(elem_t *element, FILE *const os, uint8_t ident_level);

#endif /* HTML_DOC_H */