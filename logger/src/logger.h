#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <stdbool.h>

typedef enum Logger_LogLevel {
    EMP, LOG, ERR, WAR, SUC
} Logger_LogLevel;


// --- Init ---
void Logger_initLog(const char* filename);
void Logger_taredownLog();

// --- Logging ---
void Logger_log(Logger_LogLevel level, const char* message, ...);
void Logger_logFast(const char* message);
void Logger_logMatrix(Logger_LogLevel level, 
                      void* array_ptr, 
                      size_t el_size, 
                      size_t M, 
                      size_t N,
                      bool column_major,
                      const char* mat_format, 
                      const char* message, ...);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LOGGER_H
