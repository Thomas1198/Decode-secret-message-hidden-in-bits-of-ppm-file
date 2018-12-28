/**
* @date 14.3.2018
* @file steg-decode.c
* @author Tomas Dorda (xdorda00)
* @brief Decodes message ended with \0 and is saved on LSB bit of prime indexes.
* GCC 6.4.0
*/

#include "steg-decode.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        error_exit("Wrong format of arguments");
    }

    struct ppm *ppm_img = ppm_read(argv[1]);
    if (ppm_img == NULL) {
        free(ppm_img);
        error_exit("Wrong file");
    }

    unsigned long j = 0;
    char c;
    bit_array_create(a, N);
    Eratosthenes(a);
    unsigned long size = ppm_img->xsize * ppm_img->ysize * 3;

    for (unsigned long long i = 11; i < size; i++) {
        if (bit_array_getbit(a, i) == 0) {
            unsigned long b = bit_array_getbit((&ppm_img->data[i]), 0);
            bit_array_setbit((&c - 1), j, b);
            j++;
        }
        if (j == CHAR_BIT) {
            if (c == '\0') {
                break;
            }
            printf("%c", c);
            j = 0;
        }
    }
    printf("\n");

    free(ppm_img);
    return 0;
}
