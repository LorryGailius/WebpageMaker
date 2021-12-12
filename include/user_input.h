#ifndef USER_INPUT_H
#define USER_INPUT_H

#define MAX_HEADER_LENGTH 256
#define MAX_DESCRIPTOR_LENGTH 65536
#define MAX_IMAGE_LENGTH 256
#define MAX_WEBPAGE_NAME 256
#define MAX_TITLE_LENGTH 256

typedef struct data{
    char* header;
    char* description;
    char* image;
}data_t;

#endif /* USER_INPUT_H */