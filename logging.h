#ifndef LOGGING_H
#define LOGGING_H

// #include <stdio.h>
// #include <windows.h>
// #include <stdlib.h>
// #include <stdarg.h>
// #include <ctype.h>
// #include <math.h>
// #include <string.h>
// #include <pthread.h>

typedef enum LogLevel{FATAL, ERRORN, WARNING, INFO, DEBUG } LogLevel;


void init_logging(LogLevel logLevel, const char* logfilename);

void write_log(LogLevel logLevel, const char* message);


// const char* log_level_strings[] = {
//     "DEBUG",
//     "INFO",
//     "WARN",
//     "ERROR",
//     "FATAL"
// };

// LogLevel current_log_level = LOG_LEVEL_DEBUG;
// FILE *log_file = NULL;
// pthread_mutex_t log_mutex;

// #define MAX_LOG_FILE_SIZE 1048576  // 1 MB
// void init_logging(const char *filename, LogLevel level) ;
// void close_logging();
// void log_message(LogLevel level, const char *format, ...) ;
// long get_file_size(const char *filename);
// void rotate_log(const char *filename);

#endif //LOGGING_H