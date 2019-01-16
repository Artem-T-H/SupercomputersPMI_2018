//
//  adreses.cpp
//  Individual_task
//
//  Created by Artem on 21/12/2018.
//  Copyright © 2018 Artem. All rights reserved.
//

#include "main_header.h"
#include <omp.h>

void block_mult(bl_mult inp){
    int bl_sz = inp.bl_size;
    int *A, *B, *C;
    A = inp.matrA;
    B = inp.matrB;
    C = inp.martC;
    //printf("in block!\n");
    for(int i = 0; i < bl_sz; ++i)
        for(int j = 0; j < bl_sz; ++j)
            for(int k = 0; k < bl_sz; ++k){
                //printf("in block i = %d, j = %d, k = %d\n", i, j, k);
                C[i*bl_sz + j] += A[i*bl_sz + k]*B[k*bl_sz + j];
            }
}

void matr_mult(matrix_mult inp){
    int **A = inp.matrA, **B = inp.matrB, **C = inp.martC;
    bl_mult blok_mult_in;
    blok_mult_in.bl_size = inp.bl_size;
    adr_conv adr_convA, adr_convB;
    adr_convA.bl_cnt = inp.bl_cnt;
    adr_convA.bl_size = inp.bl_size;
    adr_convB = adr_convA;
    //printf("do you know ho am I? (matr_mult)\n");
    #pragma omp parallel num_threads(2)
    {
    #pragma omp for schedule (static)
    for(int i = 0; i < inp.bl_cnt; ++i){
        for (int j = 0; j < inp.bl_cnt; ++j)
            for(int k = 0; k <= j; ++k){
                //printf("In matrix i %d, j %d, k %d\n", i, j, k);
                if (k > i){  // в силу симметрии
                    adr_convA.in_i = i;
                    adr_convA.in_j = k;
                }
                else{
                    adr_convA.in_i = k;
                    adr_convA.in_j = i;
                }
                adr_convB.in_i = j; // Изиенены в силу особенностетй функции адресации
                adr_convB.in_j = k; // (индексы i и j поменяны местами)
                //printf("prepare blocks\n");
                int *tmpA = A[adress(adr_convA)], *tmpB = B[adress(adr_convB)], *tmpC = C[i * inp.bl_cnt + j];
                blok_mult_in.matrA = tmpA;
                blok_mult_in.matrB = tmpB;
                blok_mult_in.martC = tmpC;
                //printf("to the bloks, NOW!\ninputs: %d, %d, %d\n", adress(adr_convA), adress(adr_convB), i * inp.bl_cnt + j);
                block_mult(blok_mult_in);
                //printf("ready\n");
            }
    }
    }
}
