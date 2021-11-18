/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: SalihaSAGOL
 *
 * Created on 03 Kasım 2020 Salı, 18:12
 */

#include <stdio.h>
#include <stdlib.h>
#include "compress.h"
#define BOYUT 6

int main() {
    int i, j;
    
    /*int matris[BOYUT][BOYUT] = {};
    int b;
    b = rand();
    
    for(i=0;i<BOYUT ; i++){
        printf("\n");
        for(j=0; j<BOYUT; j++){
            printf("%d " , 0+(rand()%10));
        }
    }
    */

    int matris[BOYUT][BOYUT] = {
        {10, 0, 0, 0, 2, 0},
        {3, 9, 0, 0, 0, 3},
        {0, 7, 8, 7, 0, 0},
        {3, 0, 8, 7, 5, 0},
        {0, 8, 0, 9, 9, 10},
        {0, 4, 0, 0, 2, 1}
    };

    int sayac = 0;

    // A yı tanımla 
    int **A; // double pointer A
    A = malloc(BOYUT * sizeof *A);
    for (i = 0; i < BOYUT; i++) {
        A[i] = malloc(BOYUT * sizeof *A[i]);
    }

    // A matrisinde 0 dan farkli sayilari bul

    int boyutNZ = 0; // nz nin boyutu
    for (i = 0; i < BOYUT; i++) {
        for (j = 0; j < BOYUT; j++) {
            if (matris[i][j] != 0) {
                boyutNZ++;
            }
            A[i][j] = matris[i][j];

        }
    }

    int *nz; // nz pointer

    int *col_ind, *row_ind, *col_ptr, *row_ptr; //  pointer col_ind , pointer row_ind, 
    // col_ptr pointer , row_ptr pointer
    int *row, *column;


    // dizileri tanımla
    nz = (int *) malloc(boyutNZ * sizeof (int));

    col_ind = (int *) malloc(boyutNZ * sizeof (int));
    row_ind = (int *) malloc(boyutNZ * sizeof (int));

    col_ptr = (int *) malloc((BOYUT + 1) * sizeof (int));
    row_ptr = (int *) malloc((BOYUT + 1) * sizeof (int));

    column = (int *) malloc(BOYUT * BOYUT * sizeof (int));
    row = (int *) malloc(BOYUT * BOYUT * sizeof (int));

    //nz yi olustur
    for (i = 0; i < BOYUT; i++) {
        for (j = 0; j < BOYUT; j++) {
            if (matris[i][j] != 0) {
                nz[sayac++] = matris[i][j];

            }
        }
    }

    // nz yi yazdır 
    printf("nz[] = ");
    for (i = 0; i < boyutNZ; i++) {
        printf("%d,", nz[i]);
    }
    puts("");

    // fonksiyonlari cagir

    compress_IJ(A, nz, row, column);
    //decompress_IJ(nz,row,column);

    compress_CRS(A, nz, col_ind, row_ptr);
    decompress_CRS(nz, col_ind, row_ptr);

    compress_CCS(A, nz, row_ind, col_ptr);
    decompress_CCS(nz, row_ind, col_ptr);


    // a ve nz yi bırak
    for (i = 0; i < BOYUT; i++) {
        free(A[i]);
    }
    free(A);
    free(nz);



}