/**
* @date 14.3.2018
* @file ppm.c
* @author Tomas Dorda (xdorda00)
* @brief Functions for manipulation with .ppm files
* GCC 6.4.0
*/

#include "ppm.h"

/**
 * @brief  Loads data from file and checks its validity
 * @param filename name of the file
 * @return structure with read data else NULL
*/
struct ppm *ppm_read(const char *filename) {
    FILE *fr;
    struct ppm *ppm_picture;
    fr = fopen(filename, "rb");
    if (fr == NULL) {
        warning_msg("Could open file %s", filename);
        return NULL;
    }

    unsigned xsize, ysize;

    if ((fscanf(fr, "P6\n%u %u\n255", &xsize, &ysize)) != 2) {
        fclose(fr);
        warning_msg("File %s has wrong format.\n", filename);
        return NULL;
    }

    ppm_picture = (struct ppm *) malloc(sizeof(struct ppm) + (xsize * ysize * 3));
    if (ppm_picture == NULL) {
        fclose(fr);
        warning_msg("Allocation error");
        return NULL;
    }

    ppm_picture->xsize = xsize;
    ppm_picture->ysize = ysize;

    if(fread(&ppm_picture->data, sizeof(char), xsize * ysize * 3,fr)!=(xsize * ysize * 3)){
        fclose(fr);
        free(ppm_picture);
        error_exit("Data reading error");
    }

    fclose(fr);
    return ppm_picture;
}

/**
 * @brief Writes ppm structure into ppm file
 * @param p ppm structure to write
 * @param filename name of the file
 * @return it will return negative number when error
*/
int ppm_write(struct ppm *p, const char *filename) {
    FILE *fwb;
    fwb = fopen(filename, "wb");
    if (fwb == NULL) {
        warning_msg("Opening file error", filename);
        return -1;
    }

    unsigned long velikost = p->xsize * p->ysize * 3;
    unsigned long pocet_nactenych = fwrite(&p->data, sizeof(char), velikost, fwb);
    if (pocet_nactenych != velikost) {
        fclose(fwb);
        warning_msg("Couldn't write into file %s", filename);
        return -1;
    }

    fclose(fwb);
    return 0;
}
