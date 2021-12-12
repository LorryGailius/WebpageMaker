#include <file_utils.h>

void print_idents(uint8_t ident_level, FILE *const os) {
    for(uint8_t i = 0; i < ident_level; ++i) {
        fputc('\t', os);
    }
}

size_t get_file_size(const char* filename) {
    FILE *is = fopen(filename, "rb");
    if(is == NULL) {
        return 0;
    }
    fseek(is, 0, SEEK_END);
    size_t size = ftell(is);
    fclose(is);
    return size;
}