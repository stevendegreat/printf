#pragma once
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

enum flags {
    F_MINUS = 1,
    F_PLUS = 2,
    F_ZERO = 4,
    F_HASH = 8,
    F_SPACE = 16
};

enum sizes {
    S_SHORT = 1,
    S_LONG = 2
};

typedef struct fmt {
    char fmt;
    int (*fn)(va_list, char[], int, int, int, int);
} fmt_t;

typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char fmt, int i,
                 va_list list, char buffer[], int flags, int width, int precision, int size);

/* Function prototypes with doxygen-style comments*/
/**
 * @brief Prints a character to the buffer.
 *
 * @param types The list of arguments.
 * @param buffer The buffer to write to.
 * @param flags The flags for formatting.
 * @param width The minimum width for printing.
 * @param precision The maximum number of characters to print.
 * @param size The size modifier for the argument.
 * @return The number of characters printed.
 */
int print_char(va_list types, char buffer[],
              int flags, int width, int precision, int size);

/* ... Define the rest of your functions similarly*/

/* Include guards can be replaced with #pragma once*/

