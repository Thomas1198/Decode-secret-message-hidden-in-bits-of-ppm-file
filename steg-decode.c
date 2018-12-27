/**
* @date 14.3.2018
* @file steg-decode.c
* @author Tomas Dorda (xdorda00)
* @brief Decodes message ended with \0 and is saved on LSB bit of prime indexes.
* GCC 6.4.0
*/

#include "steg-decode.h"


void decode(char data[]) {
    bit_array_create(pole, 222000000L);
    //unsigned long pole[100] = {222000000L, 0};
    Eratosthenes(pole);

    int znak = 0;
    int pocitadlo = 1;
    int bit = 0;

    printf("Odsifrovana zprava: ");
    for (long i = 11; i < 222000000L - 1; i++) {
        if (bit_array_getbit(pole, i) == 0) {
            bit = bit_array_getbit((&data[i]), 0);
            bit_array_setbit((&znak), pocitadlo, bit);
            pocitadlo++;
            if (pocitadlo == CHAR_BIT) {
                if (znak == '\0') {
                    return;
                }
                printf("%c", znak);
                pocitadlo = 0;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        error_exit("Spatny format argumentu");
    }

    struct ppm *ppm_img = ppm_read(argv[1]);
    if (ppm_img == NULL) {
        error_exit("Spatny soubor");
    }

    decode(ppm_img->data);

    free(ppm_img);
    return 0;
}
