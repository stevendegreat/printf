#include "main.h"

void print_buffer(const char buffer[], int *buff_ind);

// Declare utility functions as static
static int get_flags(const char format, int *i);
static int get_width(const char format, int *i, va_list list);
static int get_precision(const char format, int *i, va_list list);
static int get_size(const char format, int *i);

typedef struct {
    char format;
    int (*fn)(va_list, char[], int, int, int, int);
} fmt_t;

int handle_print(const char fmt, int *i, va_list list, char buffer[], int flags, int width, int precision, int size)
{
    int printed = 0;
    const fmt_t fmts[] = {
        {'c', print_char},
        {'s', print_string},
        {'%', print_percent},
        {'d', print_int},
        {'i', print_int},
        {'b', print_binary},
        {'u', print_unsigned},
        {'o', print_octal},
        {'x', print_hexadecimal},
        {'X', print_hexa_upper},
        {'S', print_non_printable},
        {'p', print_pointer},
        {'r', print_reverse},
        {'R', print_rot13string},
    };

    switch (fmt)
    {
        case 'c':
        case 's':
        case '%':
        case 'd':
        case 'i':
        case 'b':
        case 'u':
        case 'o':
        case 'x':
        case 'X':
        case 'S':
        case 'p':
        case 'r':
        case 'R':
            printed = fmts[fmt - '%'].fn(list, buffer, flags, width, precision, size);
            break;
        default:
            return (-1);
    }

    return printed;
}

int _printf(const char *format, ...)
{
    int i, printed = 0, printed_chars = 0;
    int flags, width, precision, size, buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(list, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            printed_chars++;
        }
        else
        {
            print_buffer(buffer, &buff_ind);
            flags = get_flags(format, &i);
            width = get_width(format, &i, list);
            precision = get_precision(format, &i, list);
            size = get_size(format, &i);
            ++i;
            printed = handle_print(format[i], &i, list, buffer, flags, width, precision, size);
            if (printed == -1)
                return (-1);
            printed_chars += printed;
        }
    }

    print_buffer(buffer, &buff_ind);

    va_end(list);

    return printed_chars;
}

void print_buffer(const char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
        write(1, &buffer[0], *buff_ind);

    *buff_ind = 0;
}
