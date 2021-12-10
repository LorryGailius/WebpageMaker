#include <logger.h>

FILE *logger = NULL;

void init_logger(const char* file_name) {
    logger = fopen(file_name, "wb");
    if (logger == NULL) {
        printf("init_logger(): Failed to create logger file, logger set to stderr!\n");
        logger = stderr;
    }
}

void close_logger() {
    if (logger != stderr) {
        fclose(logger);
    }
}

void log_msg(const char* msg) {
    fprintf(logger, "[%s] %s\n", __TIME__, msg);
    fflush(logger);
}