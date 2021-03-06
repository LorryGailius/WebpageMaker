#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdint.h>
#include <stdio.h>

void print_idents(uint8_t ident_level, FILE *const os);

size_t get_file_size(const char* filename);

#endif /* FILE_UTILS_H */