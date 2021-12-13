#include <stdlib.h>
#include <stdio.h>

#include <timeline.h>
#include <user_input.h>

int main(int argc, char **argv) {
    data_t *dataPoints = NULL;
    char *title = NULL; 
    char *description = NULL;
    int pointNum = 0; 
    if(getInput(argc, argv, &dataPoints, &title, &description, &pointNum) == 0) return EXIT_SUCCESS;
    FILE *html_file = fopen("index.html", "wb");
    HTML_doc_t *html = create_timeline_html(title, description, dataPoints, pointNum);
    freeInput(dataPoints, title, description, pointNum);
    print_doc(html, html_file);
    printf("Website created successfully!");
    destroy_doc(html); 
    fclose(html_file);
    return EXIT_SUCCESS;
}