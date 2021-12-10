#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

// log file handle
extern FILE *logger;
// creates a log file, in case of failure sets logger to stderr
void init_logger(const char* file_name);

// closes the logger file if its not stderr
void close_logger();

// logs message 'msg' with time of function call
void log_msg(const char* msg);

#endif /* LOGGER_H_ */