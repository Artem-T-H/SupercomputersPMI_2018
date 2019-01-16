//Работа Тикиджи-Хамбурьяна Артема, группа 4.1
//Лабораторная OMPBegin11

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <cmath>

using namespace std;

int main(){
	int n;
	n = 2;
	int x = 5;
	int N = 100;
	int k = (sqrt(0.5)*N);
	int k1 = N - k;
	cout << k << " " << k1 << endl;
	double result = 0.0, result1 = 0.0;
#pragma omp parallel private(n)
	{
		n = omp_get_thread_num();
#pragma omp sections
		{
#pragma omp section
			{
				for (int i1 = 1; i1 <= k; ++i1){
					double sum0 = 0.0;
					for (int j1 = i1; j1 <= N; ++j1){
						sum0 = sum0 + (j1 + log(1.0 + x + j1)) / (2.0*i1*j1 - 1.0);
					}
					result = result + 1.0 / sum0;
				}
				cout << n << "result" << endl;
			}
#pragma omp section
			{
				for (int i2 = k + 1; i2 <= N; ++i2){
					double sum2 = 0.0;
					for (int j = i2; j <= N; ++j){
						sum2 = sum2 + (j + log(1.0 + x + j)) / (2.0*i2*j - 1.0);
					}
					result1 = result1 + 1.0 / sum2;
				}
				cout << n << "result1" << endl;
			}

		}
	}

	cout << result + result1 << endl;
	result1 = 0.0;
	for (int i2 = 1; i2 <= N; ++i2){
		double sum2 = 0.0;
		for (int j = i2; j <= N; ++j){
			sum2 = sum2 + (j + log(1.0 + x + j)) / (2.0*i2*j - 1.0);
		}
		result1 = result1 + 1.0 / sum2;
	}
	cout << result1 << endl;
	system("pause");
	return 0;
}
