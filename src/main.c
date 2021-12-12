#include <stdlib.h>
#include <stdio.h>

#include <timeline.h>

int main(int argc, char **argv) {

    init_logger("logs.txt");

    FILE *html_file = fopen("index.html", "wb");
    HTML_doc_t *html = create_timeline_html(3);
    print_doc(html, html_file);
    destroy_doc(html);
    fclose(html_file);

    close_logger();
    return EXIT_SUCCESS;
}