/**
* @date 14.3.2018
* @file error.h
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#ifndef PROJECT_CODE_ERROR
#define PROJECT_CODE_ERROR

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);

#endif
