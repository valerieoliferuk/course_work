
#include <stdio.h>
#include "logging.h"
#include <stdlib.h>
#include <time.h>

#define STR_LOGLEVEL(loglevel) loglevel == FATAL ? "FATAL" : \
    loglevel == ERRORN ? "ERROR" : \
    loglevel == WARNING ? "WARNING" : \
    loglevel == INFO ? "INFO" : \
    loglevel == DEBUG ? "DEBUG" : "UNDEFINED"

LogLevel CurrentLogLevel;
FILE *logfile;


void init_logging(LogLevel logLevel, const char* logfilename){
    CurrentLogLevel = logLevel;
    logfile = fopen(logfilename, "a");
    if (logfile == NULL){
        printf("FATAL: could not open the file");
        exit(1);
    }
}

void write_log(LogLevel logLevel, const char* message){
    if (logLevel <= CurrentLogLevel){
        time_t now;
        time(&now);
        fprintf(logfile, "%s [%s]: %s\n", ctime(&now), STR_LOGLEVEL(logLevel), message);
        fflush(logfile);
    }
}
