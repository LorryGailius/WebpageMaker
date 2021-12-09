#include <stdlib.h>
#include <stdio.h>

#include <timeline.h>

int main(int argc, char **argv) {
    init_logger("logs.txt");
    HTML_doc_t *doc = create_timeline(3);
    print_doc(doc, stdout);
    destroy_doc(doc);
    close_logger();
    return EXIT_SUCCESS;
}