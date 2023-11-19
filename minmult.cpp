#include <iostream>
#include <climits>
using namespace::std;

int P[7][7];


int minimum(int**& M, const int*& d, int i, int j, int& p) {
	int minValue = INT_MAX;
	int value;
	p = 0;
	for (int k = i; k < j; k++) {
		value = M[i][k] + M[k + 1][j];
		value += d[i - 1] * d[k] * d[j];
		if (minValue > value) {
			minValue = value;
			p = k;
		}
	}
	return minValue;
}

int minmult(int n, const int d[], int (*P)[7]) {
	int i, j, k, diagonal;
	int** M = new int*[n + 1];
	int p;
	for (int i = 0; i < n + 1; i++)
		M[i] = new int[n + 1];

	for (i = 1; i <= n; i++)
		M[i][i] = 0;
	for(diagonal = 1;diagonal<=n-1;diagonal++)
		for (i = 1; i <= n - diagonal; i++) {
			j = i + diagonal;
			M[i][j] = minimum(M, d, i, j, p);
			P[i][j] = p;
		}

	return M[1][n] = p;
}

void order(int i, int j) {
	int k;
	if (i == j) cout << "A" << i;
	else {
		k = P[i][j];
		cout << "(";
		order(i,k);
		order(k+1,j);
		cout<< ")";
	}
}

int main(void) {
	int d[7];
	for (int i = 0; i < 7; i++) {
		cin >> d[i];
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			P[i][j] = 0;
		}
	}
	minmult(6, d, P);
	order(1,6);
}


