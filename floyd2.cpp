#include <iostream>
using namespace::std;

int W[6][6];
int D[6][6];
int P[6][6];

void floyd2(int n, const int (*W)[6], int (*D)[6], int (*P)[6]) {
	int i, j, k;
	for (i = 1; i <= n; i++) {
		for (j=1;j<=n;j++){
			P[i][j] = 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			D[i][j] = W[i][j];
		}
	}
	for (k = 1; k <= n; k++) {
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				
				if ((D[i][k] + D[k][j] < D[i][j] && D[i][k] >= 0  && D[k][j] >= 0)|| (D[i][j] == -1&& D[i][k] >= 0  && D[k][j] >= 0))  {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}

void path(int q, int r) {
	if(P[q][r] != 0) {
		path(q, P[q][r]);
		cout << " V" << P[q][r];
		path(P[q][r],r);
	}
}

int main(void) {
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 5; j++) {
			cin >> W[i][j];
		}
	}
	floyd2(5, W, D, P);
	path(5,3);

}
