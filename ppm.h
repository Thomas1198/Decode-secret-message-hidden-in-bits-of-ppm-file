/**
* @date 14.3.2018
* @file ppm.h
* @author Tomas Dorda (xdorda00)
* @brief Functions for manipulation with .ppm files
* GCC 6.4.0
*/

#ifndef PROJECT_ppm
#define PROJECT_ppm

#include <stdlib.h>
#include <stdio.h>
#include "error.h"

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

struct ppm *ppm_read(const char *filename);

int ppm_write(struct ppm *p, const char *filename);

#endif

