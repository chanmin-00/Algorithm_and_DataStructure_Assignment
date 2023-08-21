#include <iostream>
using namespace std;

template <class K,class E> class BST; // 이원 탐색 트리에 대한 전방선언
template <class K,class E>
class TreeNode{ // 이원 탐색 트리의 노드 클래스
	friend class BST<K,E>;
	public : // 트리 노드 생성자
		TreeNode(const pair<K,E>& data=pair<K,E>(),TreeNode<K,E>* left=0,TreeNode<K,E>* right=0,int num=1)
			:data(data),leftChild(left),rightChild(right),leftSize(num)
		{}
	private :
		pair<K,E> data; // pair 객체를 data로 갖는다, pair 필드
		TreeNode<K,E>* leftChild; // 왼쪽 자식
		TreeNode<K,E>* rightChild; // 오른쪽 자식
		int leftSize; // 순위 계산을 위한 leftSize 필드, 왼쪽 서브트리의 원소 수+1
}; 

template <class K,class E>
class BST{
	public : 
		BST(){root=0;} // 생성 시 0으로 초기화
		void Insert(const pair<K,E>& thePair); // 삽입 함수
		void Inorder(); /// 중위 순회 함수
		void Inorder(TreeNode<K,E>* currentNode);
		void changeRank(); // Delete 함수 호출 시 순위 변경을 위한 함수
                void changeRank(TreeNode<K,E>* currentNode); 
                int countVisit(); // 중위순회를 이용한 방문 횟수로 서브트리 수 구하는 함수
                int countVisit(TreeNode<K,E>* currentNode);
		void Delete(const K&); // key 값을 이용한 삭제 함수
		pair<K,E>* Get(const K& k); // key 값을 이용한 탐색 함수
		pair<K,E>* Get(TreeNode<K,E>* p, const K& k);
		pair<K,E>* Rank(int r); // 순위에 의한 이원 트리 탐색
	private :
		TreeNode<K,E>* root; // 트리의 루트르 가리키는 포인터  root 필드
};

template <class K, class E>
void BST<K,E>::Insert(const pair<K,E>& thePair){ // 삽입 함수
	TreeNode<K,E>* p = root,*pp=0; // pp는 p의 부모 포인터
	while(p){ // 같은 키 값이 없는지 확인, 같은 키 값 있으면 leftSize 갱신 불 필요
		pp=p;
		if(thePair.first<p->data.first) p=p->leftChild;
		else if(thePair.first>p->data.first) p=p->rightChild;
		else {p->data.second = thePair.second;return;}
	}
	TreeNode<K,E>* p_1 = root,*pp_1=0; // leftSize 갱신을 위한 새로운 포인터
	while(p_1){ // leftSize 갱신 위한 반복
		pp_1=p_1;
		if(thePair.first<p_1->data.first) {
			p_1=p_1->leftChild;
			pp_1->leftSize++;
		}
		else if(thePair.first>p_1->data.first) p_1=p_1->rightChild;
	}
	// 삽입 수행
	p=new TreeNode<K,E>(thePair); // 새로운 노드 생성
	if(root)
		if(thePair.first<pp->data.first) pp->leftChild=p;
		else pp->rightChild=p;
	else root=p;
}

template <class K, class E>
void BST<K,E>::Inorder(){Inorder(root);}
template <class K, class E>
void BST<K,E>::Inorder(TreeNode<K,E> * currentNode){ // 중위순회 함수 , LVR
	if(currentNode){
		Inorder(currentNode->leftChild);
		cout<<currentNode->data.first<<"("<<currentNode->data.second<<") "; // 방문시 바로 출력
		Inorder(currentNode->rightChild);
	}
}

template <class K, class E>
int BST<K,E>::countVisit(TreeNode<K,E> * currentNode){ // 왼쪽 서브트리의 수 결정, 방문횟수를 통해
	if(!currentNode) return 0;

	int count=0;
        count+=countVisit(currentNode->leftChild); // 순환, 재귀를 통해 방문 횟수 결정
        count+=countVisit(currentNode->rightChild);
        
	return count+1;
}

template <class K, class E>
void BST<K,E>::changeRank(){ changeRank(root);} // Delete 시 발생하는 왼쪽 서브트리 원소 수 변경에 의한 갱신
template <class K, class E>
void BST<K,E>::changeRank(TreeNode<K,E> * currentNode){ // 중위순회의 방문 순서를 통한 rank 변경
        if(currentNode){
                changeRank(currentNode->leftChild); 
                currentNode->leftSize=1+countVisit(currentNode->leftChild); // 노드 방문 시 왼쪽 서브트리 수 계산해서 leftSize 계산
                changeRank(currentNode->rightChild);
        }
}

template <class K, class E>
void BST<K,E>::Delete(const K& key){ // 삭제 함수의 경우는 3가지 경우의 수가 있다.
	// K값에 대한 탐색부터 실행
	TreeNode<K,E>* p = root, *pp=0; // pp는 부모 포인터
	while(p){ // key 값이 가리키는 노드를 찾기 위한 탐색
		if(key<p->data.first) {
			pp=p;
			p=p->leftChild;
		}
		else if(key>p->data.first) {pp=p;p=p->rightChild;}
		else break;
	}
	// 주의할 점: pp가 0인 경우에 대한 생각 즉, 삭제 노드가 루트인 경우
	// 리프 노드에 대한 삭제(부모 자식 필드는 0으로, 삭제된 노드 반환)
	if(p->leftChild==0 && p->rightChild==0) {
		if(pp==0) { // 루트 노드에 대한 삭제일 경우
			root=0;
			delete p;
		}
		else if(key<pp->data.first){
			pp->leftChild=0;
			delete p;
		}
		else{
			pp->rightChild=0;
			delete p;
		}	
	}
	// 하나의 자식만 가진 노드에 대한 삭제(삭제된 노드의 자식을 삭제된 노드 자리에 위치)
	else if(p->leftChild==0 || p->rightChild==0){
		if(pp==0) { // root노드의 경우에 대한 삭제
			if(p->rightChild==0) { root=p->leftChild;delete p;} 
			else { root=p->rightChild;delete p;}
		}
		else if(key<pp->data.first){ // 부모의 왼쪽 포인터에 대한 변경
			if(p->leftChild==0){ // key값이 오른쪽 자식이 있음
				pp->leftChild=p->rightChild;
				delete p; //반환
			}
			else { // key값이 왼쪽 자식이 있음
				pp->leftChild=p->leftChild;
				delete p;
			}
		}
		else{ // 부모의 오른쪽 포인터에 대한 변경
			if(p->leftChild==0){
				pp->rightChild=p->rightChild;
				delete p;
			}
			else {
				pp->rightChild=p->leftChild;
				delete p;
			}
		}
	}
	else { // 두개의 자식 가진 노드에 대한 삭제, 오른쪽 서브트리에서 가장 작은 원소 삭제
		TreeNode<K,E>* tmp = p->rightChild,*tmp_pp=p; //tmp는 삭제할려는 노드의 오른쪽 서브트리 루트,tmp_pp는 부모
		while(tmp->leftChild){ 
			tmp_pp=tmp;
			tmp=tmp->leftChild; 
		} // 반복 수행 후 tmp가 가리키는 값은 오른쪽 서브트리에서 가장 작은 값
		// 2가지 경우로 나누어 생각
		if(tmp_pp!=p) { // p의 오른쪽 서브트리의 루트가 가장 작은 경우가 아닌 경우
			tmp_pp->leftChild=tmp->rightChild; // tmp->rightChild는 0일수도 있고 아닐수도 있고
			tmp->rightChild=p->rightChild; // 대체한 원소의 오른쪽 자식을 p의 오른쪽 자식으로 설정
		}//p의 오른쪽 서브트리 루트가 가장 작으면 그대로 올려주면 됨
		tmp->leftChild=p->leftChild; // 어느 경우로 대체되더라도 왼쪽 자식은 대체되는 것의 왼쪽자식
		if(pp==0){ // root 노드인 경우
			root = tmp;
			delete p;
		}
		else if(key<pp->data.first){ // 부모의 왼쪽
				pp->leftChild=tmp;
				delete p;
			}
		else {	// 부모의 오른쪽
				pp->rightChild=tmp;
				delete p;
			}	
		}
		BST<K,E>::changeRank(); // rank 갱신을 위한 changeRank 함수 
					// 삽입 시와 삭제 시 rank 갱신이 일어나야 함
	}

template <class K,class E> 
pair<K,E>* BST<K,E>::Get(const K& k){ return Get(root,k);}
template <class K,class E>
pair<K,E>* BST<K,E>::Get(TreeNode<K,E>* p,const K& k){ //탐색을 위한 함수 정의
	if(!p) return 0;
	if(k<p->data.first) return Get(p->leftChild,k);
	if(k>p->data.first) return Get(p->rightChild,k);
	return &p->data;
}
template<class K,class E>
pair<K,E>* BST<K,E>::Rank(int r){ // 순위에 의한 이원 탐색트리의 탐색 함수
	TreeNode<K,E>* currentNode=root;
	while(currentNode)
		if(r<currentNode->leftSize) currentNode=currentNode->leftChild;
		else if(r>currentNode->leftSize){
			r-=currentNode->leftSize;
			currentNode=currentNode->rightChild;
		}
		else return &currentNode->data;
	return 0;
}

int main(void) {
	BST<int,int> bst; // 이원 탐색 트리 객체 생성
	// 1. Insert 함수를 사용한 노드 추가
	bst.Insert(make_pair(33,90));
	bst.Insert(make_pair(50,73));
	bst.Insert(make_pair(43,99));
	bst.Insert(make_pair(11,82));
	bst.Insert(make_pair(24,78));
	bst.Insert(make_pair(46,96));
	bst.Insert(make_pair(1,72));
	bst.Insert(make_pair(8,88));
	bst.Insert(make_pair(36,77));
	bst.Insert(make_pair(56,93));
	bst.Insert(make_pair(53,82));
	bst.Insert(make_pair(59,100));
	// 2. 중위 순회 이용 모든 노드 출력
	bst.Inorder();
	// 3. 번호 50 노드 삭제
	bst.Delete(50);cout<<endl;
	// 4. 중위 순회 이용 모든 노드 출력
	bst.Inorder();
	// 5. 번호 8 노드 삭제
	bst.Delete(8);cout<<endl;
	// 6. 중위 순회 이용 모든 노드 출력
	bst.Inorder();
	// 7. 번호 56 노드 삭제
	bst.Delete(56);cout<<endl;
	// 8. 중위 순회 이용 모든 노드 출력
	bst.Inorder();
	// 9. 43 노드 있는지 확인
	cout<<endl<<"43이 있는지 확인"<<endl;
	cout<<bst.Get(43)->first<<"("<<bst.Get(43)->second<<")"<<endl;
	// 10. 순위 5 입력, 5번째로 작은 번호 출력
	cout<<"5번째 작은 번호 출력"<<endl;
	cout<<bst.Rank(5)->first<<"("<<bst.Rank(5)->second<<")"<<endl;

	return 0;
}
