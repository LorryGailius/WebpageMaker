#ifndef CSS_DOC_H
#define CSS_DOC_H

// system headers
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// user headers 
#include <logger.h>
#include <file_utils.h>
// property indices
#define PROP_NONE       0
#define PROP_BG_COL     1
#define PROP_BORDER_R   2
#define PROP_PADDING_R0 3
#define PROP_BORDER_W   4
#define PROP_PADDING_L  5
#define PROP_BORDER_COL 6
#define PROP_MAX_W      7
#define PROP_POSITION   8
#define PROP_PADDING    9
#define PROP_CONENT     10
#define PROP_Z_INDEX    11
#define PROP_MARGIN     12
#define PROP_HEIGHT     13
#define PROP_BORDER     14
#define PROP_WIDTH      15
#define PROP_RIGHT      16
#define PROP_LEFT       17
#define PROP_TOP        18
#define PROP_FONT_FAM   19
#define PROP_NUM        20
// property string table
extern const char* property_table[PROP_NUM];

// everything here is based on this:
// https://developer.mozilla.org/en-US/docs/Learn/CSS/First_steps/How_CSS_is_structured

// css declaration structure
typedef struct css_decl_t {
    uint8_t prop_index; // property index
    char *value;        // declaration vaue
} css_decl_t;

css_decl_t* create_css_decl(uint8_t prop_index, const char* value);
void destroy_css_decl(css_decl_t *decl);

#define MAX_DECLARATIONS 100

typedef struct css_rule_t {
    char *selector;
    css_decl_t *decls[MAX_DECLARATIONS];
    size_t decl_cnt;
} css_rule_t;

css_rule_t* create_css_rule(const char* selector);
// frees rule and all stored declarations
void destroy_css_rule(css_rule_t *rule);
void css_rule_push_decl(css_rule_t *rule, css_decl_t *decl);

#define MAX_RULES 1000

typedef struct css_doc_t {
    css_rule_t *rules[MAX_RULES];
    size_t rule_cnt;
} css_doc_t;

css_doc_t* create_css_doc();
void destroy_css_doc(css_doc_t *doc);
void css_doc_push_rule(css_doc_t *doc, css_rule_t *rule);

void print_css_decl(css_decl_t *decl, FILE *const os);
void print_css_rule(css_rule_t *rule, FILE *const os);
void print_css_doc(css_doc_t *doc, FILE *const os);

#endif /* CSS_DOC_H */ 