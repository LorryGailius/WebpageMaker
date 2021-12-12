#include <stdlib.h>
#include <stdio.h>

#include <timeline.h>
#include <user_input.h>

int main(int argc, char **argv) {

    data_t *dataPoints = NULL;
    char *title = NULL; 
    char *description = NULL;
    int pointNum = 0;

    getInput(argc, argv, &dataPoints, &title, &description, &pointNum);
    
    freeInput(dataPoints, title, description, pointNum);

    init_logger("logs.txt");

    FILE *html_file = fopen("index.html", "wb");
    HTML_doc_t *html = create_timeline_html(3);
    print_doc(html, html_file);
    destroy_doc(html);
    fclose(html_file);

    close_logger();
    return EXIT_SUCCESS;
}