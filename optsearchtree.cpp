#include <iostream>
#include <float.h>

using namespace::std;
#define N 4

float minimum(float**& A, int i, int j, int& minIndex) {
	float minValue = FLT_MAX;
	float value;
	minIndex = 0;
	for (int k = i; k <= j; k++) {
		value = A[i][k - 1] + A[k + 1][j];
		if (minValue > value) {
			minValue = value;
			minIndex = k;
		}
	}
	return minValue;
}

float sumP(const float*& p, int i, int j) {
	float sum = 0;
	for (int k = i; k <= j; k++) {
		sum += p[k];
	}
	return sum;
}


void optsearchtree(int n, const float p[], float& minavg, int**& R) {
	int i, j, k, diagonal;
	int minIndex;
	float** A = new float* [n + 2];
	for (int i = 0; i < n + 2; i++) {
		A[i] = new float[n + 1];
	}
	for (i = 1; i <= n; i++) {
		A[i][i - 1] = 0; A[i][i] = p[i]; R[i][i] = i; R[i][i - 1] = 0;
	}
	A[n + 1][n] = 0; R[n + 1][n] = 0;
	for (diagonal = 1; diagonal <= n - 1; diagonal++)
		for (i = 1; i <= n - diagonal; i++) {
			j = i + diagonal;
			A[i][j] = minimum(A, i, j, minIndex) + sumP(p, i, j);
			R[i][j] = minIndex;
		}
	minavg = A[1][n];
}

int main(void) {
	float p[N+1];
	float minavg;

	int** R = new int*[N + 2];
	for (int i = 0; i < N + 2; i++){
		R[i] = new int[N + 1];
	}
	for (int i = 1; i <= N; i++) {
		cin >> p[i];
	}
	optsearchtree(N, p, minavg, R);
}
