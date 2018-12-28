/**
* @date 14.3.2018
* @file eratosthenes.c
* @author Tomas Dorda (xdorda00)
* @brief Will set primes to 0 and non-primes to 1
* GCC 6.4.0
*/

#include "eratosthenes.h"

void Eratosthenes(bit_array_t pole) {
    unsigned long size = bit_array_size(pole);
    double stop_limit = sqrt(size);

    for (unsigned long i = 2; i < stop_limit; i++) {
        if (bit_array_getbit(pole, i) == 0) {
            for (unsigned long n = 2; n * i < size; n++) {
                bit_array_setbit(pole, n * i, 1);
            }
        }
    }
}
