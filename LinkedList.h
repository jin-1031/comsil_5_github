#ifndef __LINKEDLIST__ // 해당 헤더파일이 한 번만 포함되도록 한다
#define __LINKEDLIST__

#include <iostream>
using namespace std;

//LinkedList Node
template <typename T> class Node{ // 노드 클래스 
	public:
		// 노드는 데이터와 다음 노드를 가리키는 포인터로 구성
		T data; // 노드의 데이터를 저장하는 멤버 변수
		Node *link; //노드 구조체 이용; 다음 노드의 주소를 저장할 포인터 선언
		
		Node(T element){ // 생성자; 
		  data = element; // 노드 데이터(data) 초기화 
		  link = 0; // 포인터(link)를 널포인터로 초기화
		}
};

//LinkedList Class
template <typename T> class LinkedList{ // 연결 리스트 클래스
	protected:
		Node<T> *first; // 첫번째 노드의 주소를 저장할 포인터 선언
		int current_size; // 현재 리스트의 크기를 저장하는 멤버 변수
	public:
		LinkedList(){ //생성자;
			first = 0; // 포인터(first) 초기화
			current_size = 0; // 현재 리스트의 크기 0으로 초기화
		};

		int GetSize(){ 
			return current_size; // 현재 리스트의 크기(노드 개수)를 리턴
		};

		void Insert(T element); // 맨 앞에 원소를 삽입, LinkedList와 Stack 둘다 같다
		
		virtual bool Delete(T &element); // 맨 뒤의 원소를 삭제(LinkedList), 맨 앞의 원소 삭제(Stack)
		// LinkedList와 Stack, 2가지 구조에 따라 다르게 작동하므로 virtual로 선언한 뒤 파생 클래스 Stack에서 Delete()를 재정의한다.

		void Print(); // LinkedList 출력
};


//새 노드를 맨 앞에 붙이고 값을 넣음
template <typename T> void LinkedList<T>::Insert(T element){
	//동적 할당으로 노드 생성, 이때 newnode는 포인터.
	Node<T> *newnode = new Node<T>(element);

	//새 노드가 첫번째 노드를 가리킴
	// 객체의 멤버에 접근하는 방법으로는 '->', '.' 이 있다.
	// 여기서 newnode는 포인터이기 때문에 . 사용이 불가능하므로 -> 를 사용해 함수, 변수를 불러옴 
	// newnode.link와 뜻은 같다
	newnode -> link = first; // newnode가 가리키는 노드의 link에 first가 가리키는 노드의 주소를 할당
	// 즉 다음 노드는 first가 가리키는 노드가 된다
	first = newnode; // newnode가 첫번째 노드이므로 첫번째 노드를 가리키는 first에 이를 반영
	current_size++; // 노드가 증가했으므로 연결리스트 길이에 이를 반영
}

//마지막 노드의 값을 리턴하면서 메모리에서 할당 해제
template <typename T> bool LinkedList<T>::Delete(T &element){

	if (first == 0)
		return false; // 삭제할 것이 없으므로 false 반환
	
	Node<T> *current = first; // 현재 노드를 가리키는 포인터 선언
	// 처음에는 현재 노드가 first가 가리키는 노드이므로 first 초기화
	Node<T> *previous = 0; // 이전 노드를 가리키는 포인터 선언, 처음에는 널 포인터
	
	// 마지막 노드까지 찾아가는 반복문
	while(1){
		if (current->link == 0){  // 다음 노드를 가리키는 포인터가 널 포인터인 마지막 노드를 찾는다
			// 이전 노드와 현재 노드를 이동시키며 마지막 노드에 도달하면 이전 노드가 마지막 노드가 되도록 한다.
			if (previous) // 이전 노드가 존재한다면
				previous -> link = current -> link; // 이전 노드의 다음을 가리키는 포인터가 현재 노드의 다음(널)을 가리키게 함(주소값 할당)
			else // 이전 노드가 없다면(노드가 1개인 경우)
				first = first -> link; // 첫번째 노드를 가리키는 포인터가 첫번째 노드의 다음(널)을 가리키게 함(널 포인터로 만든다)
			break;
		}
		previous = current; // 이전 노드를 가리키는 포인터가 현재 노드를 가리키게 함
		current = current -> link; // 현재 노드를 가리키는 포인터가 현재 노드의 다음 노드를 가리키게 함
	}
	element = current -> data; // 현재 노드(삭제될 마지막 노드)의 데이터의 값을 저장
	delete current; // 현재 노드(삭제될 마지막 노드) 할당 해제
	current_size--; // 노드가 감소했으므로 연결 리스트 길이에 이를 반영

	return true; // 정상적으로 삭제한 경우 true를 반환
}

//리스트를 출력하는 Print 함수
template <typename T> void LinkedList<T>::Print(){
	Node<T> *i; // 출력하기 위해 순회하는 노드를 가리키는 포인터 선언
	T index = 1; // 리스트의 크기와 비교할 변수 선언 및 초기화

	if (current_size != 0){ // 리스트의 길이가 0이 아닌 경우
		for( i = first; i != NULL; i=i->link){ // i가 널 포인터가 되기 전까지 반복
			if (index == current_size){ // 마지막 노드에 이르면
				cout << "[" << index << "|";
				cout << i -> data <<"]";
			}
			
			else { // 그 외의 모든 노드
				cout << "[" << index << "|";
				cout << i -> data << "]->"; 
				index++; // index를 증가
			}
		}
		cout << endl;
	}

}


#endif
