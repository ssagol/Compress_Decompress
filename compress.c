/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   compress.c
 * Author: SalihaSAGOL
 *
 * Created on 03 Kasım 2020 Salı, 18:13
 */

#include <stdio.h>
#include <stdlib.h>
#include "compress.h"
#define BOYUT 6

void compress_IJ(int **A, int *nz, int *row, int *column) {

    int i, j;
    int iSayac = 0;

    for (i = 0; i < BOYUT; i++) {
        for (j = 0; j < BOYUT; j++) {
            if (A[i][j] != 0) {
                nz[iSayac++] = A[i][j];

            }
        }
    }
    int sayac2 = 0;
    int sayac3;
    for (i = 0; i < BOYUT; i++) {
        sayac3 = 1;
        for (j = 0; j < BOYUT; j++) {
            if (A[i][j] != 0) {
                row[sayac2++] = 0;
                sayac3 = 1;
            } else {
                row[sayac2] = sayac3;
                sayac3++;

            }
        }
    }
    /*for (i = 0; i < sayac2; i++) {
        printf("%d", row[i]);
    }*/
}

int **decompress_IJ(int *nz, int *row, int *column) {

    int i, j;
    int **decA;

    int sayac1 = 0; //row sayac
    int sayac2 = 0; //nz indis sayc

    for (i = 0; i < BOYUT; i++) {
        for (j = 0; j < BOYUT; j++) {

            if (row[sayac1] == 0) {
                decA[i][j] = nz[sayac2];
                sayac1++;
                sayac2++;

            } else {
                decA[i][j] = 0;
                row[sayac1] -= 1;
                if (row[sayac1] == 0) {
                    sayac1++;
                }
            }
        }
    }
    /*for (i = 0; i < sayac1; i++) {
        printf("%d", row[i]);
    }*/

    return decA;
}

void compress_CRS(int **A, int *nz, int *col_ind, int *row_ptr) {

    printf("\nCompress CRS : ");
    int i, j; //for loop sayaclari
    int colSayac = 0; //col_ind icin sayac
    int rowSayac = 0; //row_ptr icin sayac
    int sifirSayac = 0; //satirdaki sifirdan farkli sayilari saymak icin sayac
    int ilkSayiKontrol; //satirdaki sifirdan farkli ilk sayi olup olmadigina bakmak icin sayac

    // col_ind olustur
    for (i = 0; i < BOYUT; i++) {
        for (j = 0; j < BOYUT; j++) {
            if (A[i][j] != 0) {
                col_ind[colSayac] = j;
                colSayac++;
            }
        }
    }

    //row_ptr olustur
    for (i = 0; i < BOYUT; i++) {
        ilkSayiKontrol = 0;
        for (j = 0; j < BOYUT; j++) {
            if (A[i][j] != 0) {
                if (ilkSayiKontrol == 0) {
                    row_ptr[rowSayac] = sifirSayac;
                    rowSayac++;
                    ilkSayiKontrol = 1;
                }
                sifirSayac++;
            }
        }
    }

    //row_ptr son indenksinde nz'nin son indeksi bulunur
    row_ptr[rowSayac] = sifirSayac;

    //yazdır
    printf("\ncol_ind[] = ");
    for (i = 0; i < sifirSayac; i++) {
        printf("%d,", col_ind[i]);
    }

    printf("\nrow_ptr[] = ");
    for (i = 0; i < BOYUT + 1; i++) {
        printf("%d,", row_ptr[i]);
    }
    printf("\n");
}

int **decompress_CRS(int *nz, int *col_ind, int *row_ptr) {

    int **decA;
    int i, j;
    int indisSayac = 0; //indeks sayaci

    decA = malloc(BOYUT * sizeof *decA);
    for (i = 0; i < BOYUT; i++) {
        decA[i] = malloc(BOYUT * sizeof *decA[i]);
    }

    for (i = 0; i < BOYUT; i++) {
        for (j = 0; j < BOYUT; j++) {
            if (j == col_ind[indisSayac]) {
                decA[i][j] = nz[indisSayac];
                indisSayac++;
            } else {
                decA[i][j] = 0;
            }
        }
    }

    printf("\nDecompressed A :\n");
    for (i = 0; i < BOYUT; i++) {
        for (j = 0; j < BOYUT; j++) {
            printf("%d ", decA[i][j]);
        }
        printf("\n");
    }

    return decA;
}

void compress_CCS(int **A, int *nz, int *row_ind, int *col_ptr) {

    int i, j;
    printf("\nCompress CCS : ");

    int counter = 0;
    int rowSayac = 0; //row_ind icin sayac
    int colSayac = 0; //col_ptr icin sayac
    int sifirSayac = 0; //sutundaki sifirdan farkli sayilari saymak icin sayac
    int ilkSayiKntrl; //sutundaki sifirdan farkli ilk sayi olup olmadigina bakmak icin sayac

    for (i = 0; i < BOYUT; i++) {
        for (j = 0; j < BOYUT; j++) {
            if (A[j][i] != 0) {
                nz[counter] = A[j][i];
                counter++;
            }
        }
    }

    // row_ind olustur
    for (i = 0; i < BOYUT; i++) {
        for (j = 0; j < BOYUT; j++) {
            if (A[j][i] != 0) {
                row_ind[rowSayac] = j;
                rowSayac++;
            }
        }
    }

    //yazdır
    printf("\nrow_ind[] = ");
    for (i = 0; i < rowSayac; i++) {
        printf("%d,", row_ind[i]);
    }

    rowSayac = 0;
    for (i = 0; i < BOYUT; i++) {
        for (j = 0; j < BOYUT; j++) {
            if (A[j][i] != 0) {
                row_ind[rowSayac] = j;
                rowSayac++;
            }
        }
    }

    //col_ptr olustur
    for (i = 0; i < BOYUT; i++) {
        ilkSayiKntrl = 0;
        for (j = 0; j < BOYUT; j++) {
            if (A[j][i] != 0) {
                if (ilkSayiKntrl == 0) {
                    col_ptr[colSayac] = sifirSayac;
                    colSayac++;
                    ilkSayiKntrl = 1;
                }
                sifirSayac++;
            }
        }
    }

    //row_ptr son indenksinde nz'nin son indeksini bul
    col_ptr[colSayac] = sifirSayac;

    printf("\ncol_ptr[] = ");
    for (i = 0; i < BOYUT + 1; i++) {
        printf("%d,", col_ptr[i]);
    }
}

int **decompress_CCS(int *nz, int *row_ind, int *col_ptr) {

    int **decA; //decompress A matrisi
    int i, j;
    int indisSayac = 0;

    decA = malloc(BOYUT * sizeof *decA);
    for (i = 0; i < BOYUT; i++) {
        decA[i] = malloc(BOYUT * sizeof *decA[i]);
    }

    for (i = 0; i < BOYUT; i++) {
        for (j = 0; j < BOYUT; j++) {
            if (j == row_ind[indisSayac]) {
                decA[j][i] = nz[indisSayac];
                indisSayac++;
            } else {
                decA[j][i] = 0;
            }
        }
    }

    printf("\n");
    printf("\nDecompressed A : \n");
    for (i = 0; i < BOYUT; i++) {
        for (j = 0; j < BOYUT; j++) {
            printf("%d ", decA[i][j]);
        }
        printf("\n");
    }

    return decA;
}

