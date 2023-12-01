#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool promising(int i, int profit, int weight);

const int W = 10;
const int n = 4;
int maxprofit; // 현재까지 찾은 최적해의 이익값
int numbest;
vector<int> p;
vector<int> w;
vector<string> bestset;
vector<string> include;

void knapsack(int i, int profit, int weight) {
	if (weight <= W && profit > maxprofit) {
		maxprofit = profit;
		numbest = i;
		bestset = include;
	
	}
	if (promising(i, profit, weight)) {
		include[i + 1] = "YES";
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		include[i + 1] = "NO";
		knapsack(i + 1, profit, weight);
	}
}

bool promising(int i, int profit, int weight) {
	int j, k;
	int totweight;
	float bound;
	if (weight >= W)
		return false;
	else {
		j = i + 1;
		bound = profit;
		totweight = weight;
		while ((j <= n) && (totweight + w[j] <= W)) {
			totweight = totweight + w[j];
			bound = bound + p[j];
			j++;
		}
		k = j;
		if (k <= n)
			bound = bound + (W - totweight) * p[k] / w[k];
		return bound > maxprofit;
	}
}

int main(void) {
	int tmp;
	
	p.resize(n+1);
	w.resize(n+1);
	p[0] = 0; // 1번째 인덱스부터 사용을 위해 0번째 초기화
	w[0] = 0; // 1번째 인덱스부터 사용을 위해 0번째 초기화
	//bestset.push_back("0"); // 1번째 인덱스부터 사용을 위해 0번째 초기화
	bestset.resize(n + 1);
	bestset[0] = "0";
	//include.push_back("0"); // 1번째 인덱스부터 사용을 위해 0번째 초기화
	include.resize(n + 1);
	include[0] = "0";
	cout << "각 " << n << "개 아이템의 무게를 입력하세요" << endl;
	for (int i = 1; i <= n; i++) {
		cin >> tmp;
		w[i] = tmp;
	}
	cout << "각 " << n << "개 아이템의 가치를 입력하세요" << endl;
	for (int i = 1; i <= n; i++) {
		cin >> tmp;
		p[i] = tmp;
	}
	maxprofit = 0;
	numbest = 0; // 각각의 변수 초기화
	knapsack(0, 0, 0); // knapsack 함수 호출
	cout << "bestset 결과" << endl;
	for (int i = 1; i < bestset.size(); i++) {
		cout << bestset[i] << " ";
	}
	cout << endl;
}
