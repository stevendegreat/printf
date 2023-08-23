#include "main.h"

int _printf(const char *format, ...)
{
    int char_print = 0;
    va_list arg_list;

    va_start(arg_list, format);

    while (*format)
    {
        if (*format != '%')
        {
            write(1, format, 1);
            char_print++;
        }
        else
        {
            format++;
            if (*format == '\0')
                break;
            else if (*format == 'd' || *format == 'i')
            {
                int num = va_arg(arg_list, int);
                char buffer[20]; /*Assuming a maximum of 20 characters for the number*/

                int num_chars = snprintf(buffer, sizeof(buffer), "%d", num);
                write(1, buffer, num_chars);
                char_print += num_chars;
            }
            /*Add handling for other specifiers here*/
            else
            {
                /*Handle unknown specifier*/
                write(1, "Unsupported format specifier", sizeof("Unsupported format specifier") - 1);
                char_print += sizeof("Unsupported format specifier") - 1;
            }
        }
        format++;
    }

    va_end(arg_list);

    return (char_print);
}
