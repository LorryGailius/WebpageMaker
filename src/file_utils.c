#include <file_utils.h>

void print_idents(uint8_t ident_level, FILE *const os) {
    for(uint8_t i = 0; i < ident_level; ++i) {
        fputc('\t', os);
    }
}