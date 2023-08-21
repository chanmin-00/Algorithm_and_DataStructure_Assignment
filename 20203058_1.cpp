#include <iostream>
using namespace std;

void divide(const int &tmp1,const int &tmp2, int &tmpResult1, int &tmpResult2){

        if(tmp2==0){
		throw 0;
	}
	tmpResult1 = tmp1/tmp2;
        tmpResult2 = tmp1%tmp2;

}

int main(void){

	int num1, num2; // 피연산자1, 피연산2
	int result1=0; // 몫
	int result2=0; // 나머지
	cout<<"피연산자 두 개를 입력하세요 :"; 
	cin>>num1>>num2;
	
	try{
	divide(num1,num2,result1,result2);
	cout<<"몫은 "<<result1<<", 나머지는 "<<result2<<"입니다."<<endl;
	}
	catch(int error){
		cout<<"잘못된 입력값입니다."<<endl;
	}


	return 0;
}

