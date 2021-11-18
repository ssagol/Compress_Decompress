/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   compress.h
 * Author: SalihaSAGOL
 *
 * Created on 03 Kasım 2020 Salı, 18:12
 */


#define COMPRESS_H_
#define BOYUT 6

void compress_IJ(int **, int *, int *, int *);
int **decompress_IJ(int *, int *, int *);


void compress_CRS(int **, int *, int *, int *);
int **decompress_CRS(int *, int *, int *);


void compress_CCS(int **, int *, int *, int *);
int **decompress_CCS(int *, int *, int *);









