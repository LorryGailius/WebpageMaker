#include <stdlib.h>
#include <stdio.h>

#include <timeline.h>
#include <css_doc.h>

int main(int argc, char **argv) {
    init_logger("logs.txt");

    HTML_doc_t *doc = create_timeline_html(3);
    print_doc(doc, stdout);
    destroy_doc(doc);

    css_decl_t *decl1 = create_css_decl(PROP_BG_COL, "#c8c8c8");
    css_decl_t *decl2 = create_css_decl(PROP_FONT_FAM, "Helvetica, sans-serif");
    
    css_rule_t *rule = create_css_rule("body");
    css_rule_push_decl(rule, decl1);
    css_rule_push_decl(rule, decl2);

    //print_css_rule(rule, stdout);

    destroy_css_rule(rule);

    close_logger();
    return EXIT_SUCCESS;
}