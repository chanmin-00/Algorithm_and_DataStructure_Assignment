#include <iostream>
#include <numeric> // accumulate 알고리즘 사용 위해 include
using namespace std;

class Number{
	private :
		int num;
	public :
		Number(int n) : num(n){}
		void ShowData() {cout<<num<<" ";}
		Number* operator->(){ return this;}
		Number& operator*(){ return *this;}
		int operator+(Number& tmp){ return num+tmp.num;} //Number class의 +연산자 사용을 위해 overloading
}; // <T>형을 Number로 구체화위해서 정의
template <typename T> 
struct DblListOp{
	T operator()(T& tmp1,T& tmp2){
		return tmp1+tmp2;
	}
}; // DblList의 +연산을 정의한 구조체

template <typename T> class DblList;

template <typename T>
class DblListNode {
	friend class DblList<T>;
	public : 
		DblListNode(T data=0,DblListNode<T>* left=0,DblListNode<T>* right=0)
		:data(data),left(left),right(right)
		{}
	private :
		T data;
		DblListNode<T> *left, *right;
}; //이중 연결 원형리스트의 노드 클래스
					
template <typename T>
class DblList {
	public :
		DblList(); //헤더 노드를 가진 공백리스트를 생성하는 생성자
		~DblList(); // 모든 노드 삭제 소멸자
		class DblListIterator { // 전진, 후진 지원하는 반복자 public 중첩 클래스
			public :
			DblListIterator(DblListNode<T>* startNode =0){
				current = startNode;
			}
			T& operator*() const {return current->data;} // 역참조 연산
			T* operator->() const { return &current->data;} // Node의 data 주소 리턴
			DblListIterator& operator++(){ // 반복자의 사전 전진 연산자 
				current=current->right;return *this; // 오른쪽으로 이동 및 반복자 리턴
			}
			DblListIterator& operator--(){ // 반복자의 사전 후진 연산자
				current=current->left;return *this; // 왼쪽으로 이동 및 반복자 리턴
			}
			bool operator!=(const DblListIterator tmp) const{ 
				return current!=tmp.current;} // 반복자가 가리키는 노드가 같은지 확인
                        bool operator==(const DblListIterator tmp) const{
                                return current==tmp.current;}
			DblListNode<T>* getRight(){ return current->right;} // 오른쪽 링크가 가리키는 노드 주소 리턴
			DblListNode<T>* getLeft(){ return current->left;}
			DblListNode<T>* getCurrent(){ return current;} // 현재 가리키고 있는 노드 주소 리턴
			private :
			DblListNode<T>* current;
		};
		DblListIterator begin(){return DblListIterator(first->right);}; // 1번째 노드를 가리키는 반복자 리턴
		DblListIterator end(){return DblListIterator(first);} // 헤더 노드를 가리키는 반복자 리턴
		void InsertBack(int num1,DblListNode<T>* p); // i번째 노드 뒤에 삽입하는 함수
		void plusNode(int num0,DblListNode<T>* p); // i번째에 노드를 삽입하는 함수
		void DeleteI(int num2); // i번째 노드를 삭제하는 함수

	private :
		DblListNode<T>* first;
};

template <typename T>
DblList<T>::DblList(){ // 헤더 노드를 가진 공백 리스트를 생성하는 생성자
	first = new DblListNode<T>(); // 헤더노드  생성
	first->left = first; // 헤더노드의 left가 자기 자신을 가리킴.
	first->right= first; // 헤더 노드의 right가 자기 자신을 가리킴
}
template <typename T>
DblList<T>::~DblList(){ //리스트의 모든 노드를 삭제하는 소멸자
	DblListIterator deleteNode = end(); 
	DblListNode<T>* di = deleteNode.getCurrent()->left; // 마지막 노드를 가리키는 포인터
	DblListNode<T>* tmp=0;
	for(di;di!=first;){ 
		tmp=di;
		di=di->left; // 왼쪽으로 이동
		delete tmp; // 가리키는 노드 객체 공간 삭제
	}
	delete first; // 헤더 노드 삭제
}

template <typename T>
void DblList<T>::plusNode(int num0,DblListNode<T>* p){ // i번째에 삽입하는 함수->초기에 DblList삽입 
        DblListIterator ai_0 = end();
        for(int i=0;i<num0;i++){
                ++ai_0;
        }
        p->left= ai_0.getCurrent();p->right=ai_0.getCurrent()->right;
        ai_0.getCurrent()->right->left=p;ai_0.getCurrent()->right=p;
}
template <typename T>
void DblList<T>::InsertBack(int num1,DblListNode<T>* p){ // i번째 뒤에 삽입하는 함수->중간에 삽입
	DblListIterator ai = end();
	for(int i=0;i<num1+1;i++){ // 반복 횟수 한 번 더 수행
		++ai;
	}
	p->left= ai.getCurrent();p->right=ai.getCurrent()->right;
	ai.getCurrent()->right->left=p;ai.getCurrent()->right=p;
}
template <typename T>
void DblList<T>::DeleteI(int num2){ // i번째 노드 삭제
	DblListIterator bi = begin(); // 반복자 first->right 노드에서 시작
	for(int i=0;i<num2;i++){
		++bi;
	}
	bi.getCurrent()->left->right = bi.getCurrent()->right;
	bi.getCurrent()->right->left = bi.getCurrent()->left;
	delete bi.getCurrent();
}


int main(void) {
	DblList<Number> numDblList;
	// 1. 1부터 9까지의 정수를 갖는 노드를 추가
	cout<<"1부터 9까지의 정수를 갖는 노드 추가"<<endl;
	for(int i=0;i<9;i++){
		numDblList.plusNode(i,new DblListNode(Number(i+1)));
	}
	// 2. 반복자를 이용하여 체인의 각 노드들을 출력
        DblList<Number>::DblListIterator start_1 = numDblList.begin();
	DblList<Number>::DblListIterator fin_1 = numDblList.end();
	for(start_1;start_1!=fin_1;++start_1){
		start_1->ShowData();
	}
	cout<<endl;
	// 3. 3과 4 노드 사이에 100을 삽입(2번째 원소 뒤에 삽입)
	cout<<"3과 4 노드 사이에 100을 삽입, 2번째 원소 뒤에 삽입"<<endl;
	numDblList.InsertBack(2,new DblListNode(Number(100)));
	// 4. 반복자를 이용하여 체인의 각 노드들을 출력
	DblList<Number>::DblListIterator start_2 = numDblList.begin();
        DblList<Number>::DblListIterator fin_2 = numDblList.end();
        for(start_2;start_2!=fin_2;++start_2){
                start_2->ShowData();
        }
	cout<<endl;
	// 5. 6을 삭제(6번째 원소 삭제)
	cout<<"6번째 원소 삭제"<<endl;
	numDblList.DeleteI(6);
	// 6. 반복자를 이용하여 체인의 각 노드들을 출력
	DblList<Number>::DblListIterator start_3 = numDblList.begin();
        DblList<Number>::DblListIterator fin_3 = numDblList.end();
        for(start_3;start_3!=fin_3;++start_3){
                start_3->ShowData();
        }
	cout<<endl;
	// 7. 전체 노드의 총합을 출력
	cout<<"전체 노드의 총합"<<endl;
	Number sum(0);
	DblListOp<Number> op; // DblListOp<Number> 형 객체 생성, Number 타입에 맞는 연산 수행
	sum=accumulate(numDblList.begin(),numDblList.end(),Number(0),op);
	sum.ShowData();
	cout<<endl;
	// 8. 제일 마지막 원소부터 맨 처음 원소까지 순서대로 출력
	cout<<"제일 마지막 원소부터 맨 처음 원소까지 출력"<<endl;
	DblList<Number>::DblListIterator start_4 = numDblList.end();
	DblList<Number>::DblListIterator fin_4 = --numDblList.end(); // 마지막 원소 가리키는 반복자
	for(fin_4;fin_4!=start_4;--fin_4){
		fin_4->ShowData();
	}
	cout<<endl;

	return 0;
}

		



