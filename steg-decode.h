/**
* @date 14.3.2018
* @file steg-decode.h
* @author Tomas Dorda (xdorda00)
* @brief Decodes message ended with \0 and is saved on LSB bit of prime indexes.
* GCC 6.4.0
*/

#include <stdio.h>
#include "eratosthenes.h"
#include "ppm.h"
#include "error.h"

void decode(char *data);

