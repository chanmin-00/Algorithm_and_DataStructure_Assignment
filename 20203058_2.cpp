#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

class Character{
	protected : 
		char * charname;
		int level,power,speed,smart,atkpower,defpower,fitness,mind;

	public : 
	Character(){}
	Character(const char * charname ,const int num1,const int num2,const int num3,const int num4,const int num5,const int num6,const int num7,const int num8)
	:level(num1),power(num2),speed(num3),smart(num4),atkpower(num5),defpower(num6),fitness(num7),mind(num8)
	{
		this->charname = new char[strlen(charname)+1];
                strcpy(this->charname,charname);
	}
	virtual ~Character(){
	}
	virtual void move() const{
		cout<<"이동했습니다"<<endl;
	}
	virtual void showInfo() const{
		cout<<"객체의 정보를 보여줍니다."<<endl;
	}
	virtual void attack() const {
		cout<<"공격을 합니다."<<endl;
	}
};

class Warrior : public Character{
	protected : 
		char * warr_weapon_name;
	public : 
	Warrior(const char * weapon_name,const char * charname)
	:Character(charname,1,100,50,20,5,3,80,20)
	{
		warr_weapon_name = new char[strlen(weapon_name)+1];
		strcpy(this->warr_weapon_name,weapon_name);
	}
	virtual ~Warrior(){
		delete [] warr_weapon_name;
		delete [] charname;
	}
	virtual void showInfo() const{
		cout<<"캐릭터 이름: "<<charname<<endl;cout<<"무기이름: "<<warr_weapon_name<<endl;
	        cout<<"레벨: "<<level;cout<<"   힘: "<<power;cout<<"   민첩: "<<speed;cout<<"   지능: "<<smart<<endl;
                cout<<"공격력: "<<atkpower;cout<<"   방어력: "<<defpower;cout<<"   체력: "<<fitness;cout<<"   정신력: "<<mind<<endl;
	}
	virtual void attack() const{
		cout<<warr_weapon_name<<" 칼로 찔렀습니다."<<endl;
	}
};

class Archer : public Character{
        protected :
                char * arch_weapon_name;
	public :
        Archer(const char * weapon_name,const char * charname)
        :Character(charname,1,50,100,20,5,3,50,50)
        {
		arch_weapon_name = new char[strlen(weapon_name)+1];
		strcpy(this->arch_weapon_name,weapon_name);
        }
	virtual ~Archer(){
                delete [] arch_weapon_name;
                delete [] charname;
	}
	virtual void showInfo() const{
      	        cout<<"캐릭터 이름: "<<charname<<endl;cout<<"무기이름: "<<arch_weapon_name<<endl;
		cout<<"레벨: "<<level;cout<<"   힘: "<<power;cout<<"   민첩: "<<speed;cout<<"   지능: "<<smart<<endl;
                cout<<"공격력: "<<atkpower;cout<<"   방어력: "<<defpower;cout<<"   체력: "<<fitness;cout<<"   정신력: "<<mind<<endl;
	}
	virtual void attack() const{
		cout<<arch_weapon_name<<" 화살로 쐈습니다."<<endl;
	}
};
class Sorcerer : public Character{
        protected :
                char * sorc_weapon_name;
	public : 
        Sorcerer(const char * weapon_name,const char * charname)
        :Character(charname,1,20,50,100,5,3,20,80)
        {
                sorc_weapon_name = new char[strlen(weapon_name)+1];
		strcpy(this->sorc_weapon_name,weapon_name);
        }
	virtual ~Sorcerer(){
                delete [] sorc_weapon_name;
     		delete [] charname;
        }
	virtual void showInfo() const{
                cout<<"캐릭터 이름: "<<charname<<endl;cout<<"무기이름: "<<sorc_weapon_name<<endl;
                cout<<"레벨: "<<level;cout<<"   힘: "<<power;cout<<"   민첩: "<<speed;cout<<"   지능: "<<smart<<endl;
                cout<<"공격력: "<<atkpower;cout<<"   방어력: "<<defpower;cout<<"   체력: "<<fitness;cout<<"   정신력: "<<mind<<endl;
        }
	virtual void attack() const{
		cout<<sorc_weapon_name<<" 마법을 걸었습니다."<<endl;
	}
};

template <typename T>
class Bag{
	public:
	      Bag(int bagCapacity = 3);
	      ~Bag();
	      int Size() const;
	      bool IsEmpty() const;
	      T* Element() const;
	      void Push(T*);
	      void Pop();
	private:
	      T** array;
	      int capacity;
	      int top;
};

template <typename T>
Bag<T>::Bag(int bagCapacity):capacity(bagCapacity){
	if(capacity<1) throw "Capacity must be > 0";
	array = new T*[capacity];
	top=-1;
}
template <typename T>
Bag<T>::~Bag(){
	for(int i=0;i<Size();i++)
	delete array[i];
	delete [] array;
}
template <typename T>
inline int Bag<T>::Size() const {
	return  top+1;
}
template <typename T>
inline bool Bag<T>::IsEmpty() const {
	return Size()==0;
}
template <typename T>
T* Bag<T>::Element() const {
	if(IsEmpty()) throw "Bag is empty";
	srand((unsigned int)time(NULL));
	int i = rand()%Size();
	return array[i]; 
	
}
template <typename T>
void Bag<T>::Push(T* x){
	if(capacity==top+1) {
	ChangeSize1D(array,capacity,2*capacity);
	capacity*=2;
	}
	array[++top]=x;
}
template <typename T>
void Bag<T>::Pop(){
	if(IsEmpty()) throw "Bag is empty, cannot delete";
	srand((unsigned int)time(NULL));
	int deletePos = rand()%Size();
	array[deletePos]->~T();
	copy(array+deletePos+1,array+top+1,array+deletePos);
	array[top--]= NULL;
}
template <typename T>
void ChangeSize1D(T**& a, const int oldSize, const int newSize){
       if(newSize<0) throw "New length must be >=0";
       T** temp = new T*[newSize];
       int number = min(oldSize,newSize);
       copy(a,a+number,temp);
       delete [] a;
       a = temp;
}       



int main(void)	{

	Warrior *w_1=new Warrior("1번 무기","1번 전사");
	Warrior *w_2=new Warrior("2번 무기","2번 전사");
	Warrior *w_3=new Warrior("3번 무기","3번 전사");
	Archer *a_1=new Archer("1번 무기","1번 궁수");
	Archer *a_2=new Archer("2번 무기","2번 궁수");
	Archer *a_3=new Archer("3번 무기","3번 궁수");
	Sorcerer *s_1=new Sorcerer("1번 무기","1번 마법사");
	Sorcerer *s_2=new Sorcerer("2번 무기","2번 마법사");
	Sorcerer *s_3=new Sorcerer("3번 무기","3번 마법사");
	cout<<"Bag 객체 생성"<<endl;
	Bag<Character> bag;
	cout<<"size:"<<bag.Size()<<endl;cout<<"비었는가?  ";
	if(bag.IsEmpty()) cout<<"비었습니다"<<endl;
	else cout<<"안 비었습니다"<<endl;
	cout<<"\n3개의 객체 추가"<<endl;
	bag.Push(w_1);bag.Push(a_1);bag.Push(s_1);
	cout<<"size:"<<bag.Size()<<endl<<"비었는가?  ";
	if(bag.IsEmpty()) cout<<"비었습니다"<<endl;
        else cout<<"안 비었습니다"<<endl;
	bag.Element()->showInfo();bag.Element()->move();bag.Element()->attack();
	cout<<"\n6개의 객체 추가"<<endl;
	bag.Push(w_2);bag.Push(a_2);bag.Push(s_2);
        bag.Push(w_3);bag.Push(a_3);bag.Push(s_3);
        cout<<"size:"<<bag.Size()<<endl;cout<<"비었는가?  ";
	if(bag.IsEmpty()) cout<<"비었습니다"<<endl;
        else cout<<"안 비었습니다"<<endl;
	bag.Element()->showInfo();bag.Element()->move();bag.Element()->attack();
	cout<<"\n2개의 객체 삭제"<<endl;
	bag.Pop();bag.Pop();
	cout<<"size:"<<bag.Size()<<endl;cout<<"비었는가?  ";
	if(bag.IsEmpty()) cout<<"비었습니다"<<endl;
        else cout<<"안 비었습니다"<<endl;
	bag.Element()->showInfo();bag.Element()->move();bag.Element()->attack();

	return 0;
}
