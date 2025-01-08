#### [My Utils](index.html) > Logger

## logger

A simple logging module to be used in C and C++ projects.

###### Description

A program log file is opened at the beginning of the application. The application can write to the log. When this is called, a mutex is locked during the entry write; only one thread can write to the log at a time. 

Each log entry has

- **Time-Stamp**: the time since log initialization
- **Log Level**: the level of log entry (*Log*, *Error*, *Warning*, *Success*)

###### Usage

Initialize the log with `Logger_initLog`. 

Any translation unit can create a log entry using by including `logger.h` and calling `Logger_log`, `Logger_logFast` or `Logger_logMatrix`.

Use log levels `LOG`, `ERR`, `WAR` or `SUC`.

Call `Logger_tearDown` after finishing using the log.

###### Functions
- [**Logger_initLog**](#logger_initlog): Initializes log
- [**Logger_teardownLog**](#logger_teardownlog): Tears down log
- [**Logger_log**](#logger_log): Write to log
- [**Logger_logFast**](#logger_logfast): Fast write to log
- [**Logger_logMatrix**](#logger_logmatrix): Creates log entry with matrix of elements

---

#### Logger_initLog
Initializes log.

> `void Logger_initLog(...);`

Must be called before using the log; should only be called once. Program log remains open until it is torn down. 

**Arguments**:

- `const char* filename`: name of program log.

#### Logger_teardownLog
Tears down log.

> `void Logger_teardownLog();`

Is called at the end of the application; closes the program log.

#### Logger_log
Write to log.

> `void Logger_log(...);`

Logs a message with C-style formatted arguments. Entry includes a time-stamp, log level and message. 

**Arguments**:

- `Logger_LogLevel level`: level of entry
- `const char* message`: message of entry; can include C-style formatting, (*e.g.*, `%i`)
- `...`: args for C-style formatting

#### Logger_logFast
Fast write to log.

> `void Logger_logFast(...);`

Logs a message; cannot use C-style formatting. 

**Arguments**:

- `const char* message`: message to be logged

#### Logger_logMatrix 
Creates a log entry with a matrix of elements.

> `void Logger_logMatrix(...);`

Logs and message (with C-style formatting) and writes a matrix of elements. Takes array and dimensions and writes the array as a matrix. Can read the array as either row major or column major. 

Must specify how each element is printed by passing in `const char* mat_format`. (*E.g.*, the format specifier `"f"` will, by default, print each element of the array as a float with two decimal points of precision using the C-style format `"%.2f"` on each write.)

To specify writing more formats, modify the `logMatrixElement` function in `logger.c`. 

**Arguments**:

- `Logger_LogLevel level`: level of entry
- `void* array_ptr`: array of elements (*e.g.*, `float[]`)
- `size_t el_size`: size of each element (*e.g.*, `sizeof(float)`)
- `size_t M`: number of rows in matrix
- `size_t N`: number of columns in matrix
- `bool column_major`: array is read as column major; else, read as row major
- `const char* mat_format,`: format for each element write (*e.g.*, `"f"`)
- `const char* message`: message to be logged; can use C-style formatting
- `...`: args for C-style formatting
