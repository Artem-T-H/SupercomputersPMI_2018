//Работа Тикиджи-Хамбурьяна Артема, группа 4.1
//Лабораторная OMPBegin18

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <omp.h>

using namespace std;

int main(int argc, char *argv[]){
	int n = 2;
	int i = 1;
	int N = 500;
	double sum;
	double result = 0.0, result1 = 0.0;
	int j;
	double x = 5.0;


	double start = omp_get_wtime();
#pragma omp parallel num_threads(2) private(i, n, sum,  j)
	{
		n = omp_get_thread_num();
#pragma omp for schedule(static)
		for (i = 1; i <= N; i++){
			sum = 0.0;
			for (j = i; j <= i + N; ++j){
				sum = sum + (j + cos(x + j)) / (2 * i*j - 1);
			}
			result = result + 1.0 / sum;
		}

	}
	double end_t = omp_get_wtime();
	cout << result + result1 << " " << end_t - start << endl;

	start = omp_get_wtime();
	result = 0.0;
	for (i = 1; i <= N; ++i){
		sum = 0.0;
		for (j = i; j <= i + N; ++j){
			sum = sum + (j + cos(x + j)) / (2 * i*j - 1);
		}
		result = result + 1.0 / sum;

	}
	end_t = omp_get_wtime();
	cout << result + result1 << " " << end_t - start << endl;
	system("pause");
}
