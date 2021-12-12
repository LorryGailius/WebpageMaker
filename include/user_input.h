#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_DATA_POINTS 65536

typedef struct data{
    char* header;
    char* description;
    char* image;
}data_t;

void getInput(int argc, char **argv, data_t **data, char **title, char **desc, int *size);

void readFile(FILE *input, data_t *data, char **title, char **desc, int *size);

void freeInput(data_t *data, char *title, char* desc, int pointNum);

#endif /* USER_INPUT_H */