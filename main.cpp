//
//  main.cpp
//  Individual_task
//
//  Created by Artem on 20/12/2018.
//  Copyright © 2018 Artem. All rights reserved.
//

#include "main_header.h"
#define MATIX_SIZE 360


int main(int argc, const char * argv[]) {
    //printf("hellow\n");
    int size = MATIX_SIZE, bl_size = 1;
    int bl_cnt = size/bl_size;
    int sizes[] = {2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 18, 20, 24, 30, 36, 40, 45, 60, 72, 90, 180, 360};
    int size_cnt = 22;
    time_t time_begin, time_end;
    long long int *work_time;
    work_time = (long long int*)calloc(size_cnt, sizeof(long long int));
    //printf("I'm gere!\n");
    int **matrixA = read_matrix("input_A.txt", size);

    int **matrixB = read_matrix("input_B.txt", size);
    //printf("Can we talk?\n");
    int **vectorC = NULL, **matrixC = NULL;
    matrixC = (int **)calloc(size, sizeof(int *));
    for(int i = 0; i < size; ++i)
        matrixC[i] = (int *)calloc(size, sizeof(int));
    
    // умножение
    convert_inp conv_input;
    conv_input.size = size;
    //printf("Why do you leav?\n");
    for (int i = 0; i < size_cnt; ++i){
        bl_size = sizes[i];
        int bl_matr_cnt = bl_cnt * (bl_cnt + 1)/2;
        conv_input.block_size = bl_size;
        //printf("stop NOW! %d\n", i);
        vectorC = (int **)calloc(bl_cnt*bl_cnt, sizeof(int*));
        for(int j = 0; j < bl_matr_cnt; ++j){
            vectorC[j] = (int *)calloc(bl_size*bl_size, sizeof(int));
        }
        
        conv_input.matrix = matrixA;
        int **vectorA = convert_down_treungle(conv_input);
        
        conv_input.matrix = matrixB;
        int **vectorB = convert_up_treungle(conv_input);
        //printf("hellow?\n");
        matrix_mult mult_inp;
        mult_inp.bl_cnt = size/bl_size;
        mult_inp.bl_size = bl_size;
        mult_inp.matrA = vectorA;
        mult_inp.matrB = vectorB;
        mult_inp.martC = vectorC;
        //printf("it's time!\n");
        time_begin = clock();
        matr_mult(mult_inp);
        time_end = clock();
        //printf("meu\n");
        work_time[i] = time_end - time_begin;
        printf("bl_sz: %3d time: %d\n", bl_size, work_time[i]);
        for (int j = 0; j < bl_matr_cnt; ++j){
            //free(vectorA[j]);
            //free(vectorB[j]);
            //free(vectorC[j]);
        }
        //printf("ho-ho-ho\n");
        //free(vectorA);
        //free(vectorB);
        //free(vectorC);
    }
    
    
    time_begin = clock();
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            for (int k = 0; k < size; ++k)
                matrixC[i][j] += matrixA[i][k]*matrixB[k][j];
    time_end = clock();
    
    bool correct = 0;
    for(int i = 0; i < size/bl_size; ++i)
        for( int k = 0; k < bl_size; ++k){
            for( int j = 0; j < size/bl_size; ++j){
                for( int p = 0; p < bl_size; ++p){
                    int tmp_vect_adr = (i*bl_cnt + j)*bl_size*bl_size + k*bl_size + p;
                    int tmp_iAdr = i*bl_size + k, tmp_jadr = j*bl_size + p;
                    correct = correct || (vectorC[tmp_vect_adr] == matrixC[tmp_iAdr][tmp_jadr]);
                }
            }
        }
    printf("correct is = %d\n", correct);
    
    
    
    FILE *fout;
    fout = fopen("block_time.txt", "w");
    for (int i = 0; i < size_cnt; ++i) {
        fprintf(fout, "%3d %5d\n", sizes[i], work_time[i]);
    }
    fclose(fout);
    
    fout = fopen("time_without_block.txt", "w");
    for (int i = 0; i < size_cnt; ++i) {
        fprintf(fout, "%3d %5d\n", sizes[i], time_end - time_begin);
    }
    fclose(fout);
    
    // отчитка памяти
    free(vectorC);
    for(int i = 0; i < size; ++i){
        free(matrixA[i]);
        free(matrixB[i]);
        free(matrixC[i]);
    }
    free(matrixA);
    free(matrixB);
    free(matrixC);
    return 0;
}
