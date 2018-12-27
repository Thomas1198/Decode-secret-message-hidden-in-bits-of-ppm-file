/**
* @date 14.3.2018
* @file error.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "error.h"

void warning_msg(const char *fmt, ...) {
    printf("CHYBA: ");
    va_list ap;
    va_start (ap, fmt);
    vprintf(fmt, ap);
    va_end (ap);
}

void error_exit(const char *fmt, ...) {
    printf("CHYBA: ");
    va_list ap;
    va_start (ap, fmt);
    vprintf(fmt, ap);
    va_end (ap);
    exit(1);
}
