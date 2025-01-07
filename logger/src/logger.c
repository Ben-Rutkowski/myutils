#include "logger.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <string.h>

#define LOG_BUFFER_SIZE 10000


// ================ Variables ================
static FILE*           Logger_log_file = NULL;
static pthread_mutex_t Logger_log_mutex;
static struct timeval  Logger_init_time;

static const unsigned long MILL = 1000000;
static char buf[LOG_BUFFER_SIZE];


// ================ Static ================
static struct timeval getDiffTime() {
    struct timeval diff_time;
    gettimeofday(&diff_time, NULL);

    if (diff_time.tv_usec < Logger_init_time.tv_usec) {
        diff_time.tv_usec += MILL;
        diff_time.tv_sec  -= 1;
    }

    diff_time.tv_sec  -= Logger_init_time.tv_sec;
    diff_time.tv_usec -= Logger_init_time.tv_usec;

    return diff_time;
}

static const char* levelString(Logger_LogLevel level) {
    switch (level) {
        case EMP: return "     ";
        case LOG: return "-   -";
        case ERR: return "-ERR-";
        case WAR: return "-WAR-";
        case SUC: return "-SUC-";
        default:  return "-NUL-";
    }
}

static inline void logHeader(Logger_LogLevel level) {
    struct timeval diff_timeval = getDiffTime();
    struct tm*     diff_tm      = gmtime(&diff_timeval.tv_sec);

    fprintf(Logger_log_file, "[%02i:%02i:%02i.%06u]", 
                diff_tm->tm_hour, 
                diff_tm->tm_min, 
                diff_tm->tm_sec, 
                diff_timeval.tv_usec
            );

    const char* level_str = levelString(level);
    fprintf(Logger_log_file, " %s ", level_str);
}

static inline void logMatrixElement(const char* format, void* element_ptr) {
    if (strcmp(format, "i") == 0)
        fprintf(Logger_log_file, "%2i", *(int*)element_ptr);

    else if (strcmp(format, "f") == 0)
        fprintf(Logger_log_file, "%.2f", *(float*)element_ptr);
    
    // Write more cases as needed
}


// ================ Init ================
void Logger_initLog(const char* filename) {
    Logger_log_file = fopen(filename, "w");
    if (!Logger_log_file) {
        perror("Failed to open the log file");
        exit(-1);
    }
    setvbuf(Logger_log_file, buf, _IOFBF, sizeof(buf));
    pthread_mutex_init(&Logger_log_mutex, NULL);
    gettimeofday(&Logger_init_time, NULL);

    printf("Log set to %s\n", filename);
}

void Logger_teardownLog() {
    fclose(Logger_log_file);
    Logger_log_file = NULL;
    pthread_mutex_destroy(&Logger_log_mutex);

    printf("Log closed\n");
}


// ================ Logging ================
void Logger_log(Logger_LogLevel level, const char *message, ...) {
    if (!Logger_log_file) {
        perror("Failed to write to the log file: log file not open!");
        return;
    }

    va_list args;
    va_start(args, message);

    pthread_mutex_lock(&Logger_log_mutex);
    logHeader(level);
    vfprintf(Logger_log_file, message, args);
    fprintf(Logger_log_file, "\n");
    fflush(Logger_log_file);
    pthread_mutex_unlock(&Logger_log_mutex);
}

void Logger_logFast(const char *message) {
    pthread_mutex_lock(&Logger_log_mutex);
    logHeader(EMP);
    fprintf(Logger_log_file, "%s\n", message);
    pthread_mutex_unlock(&Logger_log_mutex);
}

void Logger_logMatrix(Logger_LogLevel level, 
                      void* array_ptr, 
                      size_t el_size, 
                      size_t M, 
                      size_t N,
                      bool column_major,
                      const char* mat_format, 
                      const char* message, ...) 
{
    if (!Logger_log_file) {
        perror("Failed to write to the log file: log file not open!");
        return;
    }

    va_list args;
    va_start(args, message);

    pthread_mutex_lock(&Logger_log_mutex);
    logHeader(level); 
    vfprintf(Logger_log_file, message, args);
    fprintf(Logger_log_file, "\n");

    size_t id;
    for (int i=0; i<M; i++) {
        fprintf(Logger_log_file, "%*s[ ", 28, "");
        for (int j=0; j<N; j++) {
            if (column_major) id = j*M + i;
            else              id = i*N + j;

            logMatrixElement(mat_format, array_ptr+(id*el_size));
            fprintf(Logger_log_file, " ");
        }
        fprintf(Logger_log_file, "]\n");
    }

    fflush(Logger_log_file);
    pthread_mutex_unlock(&Logger_log_mutex);
}
