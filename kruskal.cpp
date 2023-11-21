#include <iostream>
#include <vector>
#include <algorithm>
using namespace::std;
const int n = 5;
typedef int index;
typedef index set_pointer;

struct disjoint_set_data {

	struct nodetype
	{
		index parent;
		int depth;
	};
	typedef nodetype universe[n + 1];
	universe U;
	void makeset(index i) {
		U[i].parent = i;
		U[i].depth = 0;
	}
	void initial(int n) {
		index i;
		for (int i = 1; i <= n; i++) {
			makeset(i);
		}
	}
	set_pointer find(index i) {
		index j;

		j = i;
		while (U[j].parent != j)
			j = U[j].parent;
		return j;
	}
	void merge(set_pointer p, set_pointer q) {
		if (U[p].depth == U[q].depth) {
			U[p].depth = U[p].depth + 1;
			U[q].parent = p;
		}
		else if (U[p].depth < U[q].depth)
			U[p].parent = q;
		else
			U[q].parent = p;
	}
	bool equal(set_pointer p, set_pointer q) {
		if (p == q)
			return true;
		else
			return false;
	}
};

class edge {
public :
	int vertex[2];
	int weight;

	edge(){
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

void kruskal(int n, int m, vector<edge> E, vector<edge>& F) {
	disjoint_set_data disjoint_set;
	index i, j;
	set_pointer p, q;
	edge e;

	sort(E.begin(), next(E.begin(),m)); // m개의 간선 집합을 정렬
	F.clear();
	disjoint_set.initial(n); //초기화
	
	int count = 0;
	while (F.size() < n - 1) {
		e = E[count];
		count++;
		i = e.vertex[0];
		j = e.vertex[1];
		p = disjoint_set.find(i);
		q = disjoint_set.find(j);
		if (!disjoint_set.equal(p, q)) {
			disjoint_set.merge(p, q);
			F.push_back(e);
		}
		//cout<<endl;
		//for(int i=1;i<=5;i++)
		//	cout <<disjoint_set.U[i].parent<<",";
	}
}

int main(void) {
	vector<edge> E;
	vector<edge> F;
	E.push_back(edge(1, 2, 1));
	E.push_back(edge(2, 4, 2));
	E.push_back(edge(4, 5, 5));
	E.push_back(edge(3, 5, 4));
	E.push_back(edge(2, 3, 6));
	E.push_back(edge(1, 5, 3));
	E.push_back(edge(3, 4, 7));
	kruskal(5, 7, E, F);
	int count = 0;
	// 결과 출력 코드
	while (count < F.size()) {
		cout << "간선의 정점 : " << F[count].vertex[0] << ", ";
		cout << F[count].vertex[1] << " 간선의 가중치 : ";
		cout << F[count].weight << endl;
		count++;
	}

}
