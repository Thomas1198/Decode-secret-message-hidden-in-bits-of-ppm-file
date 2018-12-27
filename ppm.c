/**
* @date 14.3.2018
* @file ppm.c
* @author Tomas Dorda (xdorda00)
* @brief Functions for manipulation with .ppm files
* GCC 6.4.0
*/

#include "ppm.h"

/*
načte obsah PPM souboru do touto funkcí dynamicky
alokované struktury. Při chybě formátu použije funkci warning_msg
a vrátí NULL.  Pozor na "memory leaks".
*/
struct ppm *ppm_read(const char *filename) {
    FILE *fr;
    fr = fopen(filename, "rb");
    if (fr == NULL) {
        warning_msg("Could open file %s", filename);
        return NULL;
    }

    unsigned xsize, ysize;
    int color_depth;
    unsigned long scanned_num = fscanf(fr, "P6 %u %u %d", &xsize, &ysize, &color_depth);

    //Skip one whitespace
    while (getc(fr) != '\n');

    if (scanned_num != 3) {
        fclose(fr);
        warning_msg("File %s has wrong format.\n", filename);
        return NULL;
    }

    // Unsupported color format
    if (color_depth != 255) {
        warning_msg("Error in format of file %s detected.\n", filename);
        fclose(fr);
        return NULL;
    }

    struct ppm *ppm_picture = (struct ppm *) malloc(sizeof(struct ppm) + (xsize * ysize * 3));
    if (ppm_picture == NULL) {
        fclose(fr);
        warning_msg("Allocation error");
        return NULL;
    }

    ppm_picture->xsize = xsize;
    ppm_picture->ysize = ysize;

    if (fread(ppm_picture->data, sizeof(char), (xsize * ysize * 3), fr) != (xsize * ysize * 3)) {
        warning_msg("File %s has wrong format.\n", filename);
        fclose(fr);
        free(ppm_picture);
        return NULL;
    }

    //has to end with EOF
    if (fgetc(fr) != EOF) {
        warning_msg("File %s has wrong format.\n", filename);
        fclose(fr);
        free(ppm_picture);
        return NULL;
    }

    fclose(fr);
    return ppm_picture;
}


/*
zapíše obsah struktury p do souboru ve formátu PPM.
Při chybě použije funkci warning_msg a vrátí záporné číslo.
*/
int ppm_write(struct ppm *p, const char *filename) {
    FILE *fwb;
    fwb = fopen(filename, "wb");
    if (fwb == NULL) {
        warning_msg("Soubor %s se nepodarilo otevrit", filename);
        return -1;
    }

    unsigned long velikost = p->xsize * p->ysize * 3;
    unsigned long pocet_nactenych = fwrite(&p->data, sizeof(char), velikost, fwb);
    if (pocet_nactenych != velikost) {
        fclose(fwb);
        warning_msg("Zapis do souboru %s nebyl uspesny", filename);
        return -1;
    }

    fclose(fwb);
    return 0;
}
