#include <iostream>
#include <vector>
#include <climits>
using namespace::std;
#define I 6
#define J 6

class edge {
public:
	int vertex[2];
	int weight;

	edge() {
		this->vertex[0] = 0;
		this->vertex[1] = 0;
		this->weight = 0;
	}

	edge(int vertex1, int vertex2, int weight) {
		this->vertex[0] = vertex1;
		this->vertex[1] = vertex2;
		this->weight = weight;
	}

	bool operator < (edge& edge) {
		return this->weight < edge.weight;
	}

};

void dijkstra(int n, const int (&W)[I][J], vector<edge>& F) {
	int i, vnear;
	edge e;
	int* touch = new int[n + 1];
	int* length = new int[n + 1];
	int count;
	int min;
	
	F.clear();	//F는 공집합

	for (i = 2; i <= n; i++) {
		touch[i] = 1;
		length[i] = W[1][i];
	}
	count = 1;
	while (count <= n - 1) {
		min = INT_MAX; // 정수 자료형의 최댓값을 무한대 값으로 사용
		for (i = 2; i <= n; i++) {
			if (0 <= length[i] && length[i] <= min) {
				min = length[i];
				vnear = i;
			}
		}
		e = edge(touch[vnear], vnear, W[touch[vnear]][vnear]);
		F.push_back(e);
		for(i=2;i<=n;i++)
			if (length[vnear] + W[vnear][i] < length[i] && W[vnear][i] != INT_MAX) {
				length[i] = length[vnear] + W[vnear][i];
				touch[i] = vnear;
			}
		length[vnear] = -1;
		count++;
	}
}

int main(void) {
	vector<edge> F;
	int W[6][6];
	int input;
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 5; j++) {
			cin >> input;
			if (input == -1)
				input = INT_MAX; // 입력값의 -1을 무한대로 생각
			W[i][j] = input;

		}
	}
	dijkstra(5, W, F);

	// 결과 출력 코드
	cout << "집합 F의 엣지 목록" << endl;
	for (int i = 0; i < F.size(); i++) {
		cout << "간선의 정점 : ";
		cout << F[i].vertex[0] << ", " << F[i].vertex[1];
		cout << " 간선의 가중치 : ";
		cout << F[i].weight << endl;
	}
}
