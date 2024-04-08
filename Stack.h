#include "LinkedList.h"


// 1. 템플릿 클래스로 확장해야함
// 2. Stack형식으로 Delete 함수 재정의해야함
// 주의: first, current_size는 class의 멤버 변수이기 때문에 this 포인터를 사용하여 가져와야함
// this 포인터: 멤버 함수가 호출된 객체의 주소를 가리키는 포인터
// 클래스의 멤버 함수를 인스턴스(객체를 실체화시킨 것)끼리 공유해서 사용하기 위해 어떤 인스턴스가 함수를 호출했는지 구분할 수 있게 한다.
// 평소에도 내부적으로는 this가 사용된다(생략되어 있음)

//LinkedList class를 상속받음
template <typename T>
class Stack : public LinkedList<T>{
	public:
		virtual bool Delete (T &element){ // virtual은 상위 클래스에 사용하면 하위 클래스(파생 클래스)에는 사용해도 되고 안 해도 됨
			if(this->first == nullptr) { // c++에서는 nullptr을 많이 사용
				return false; // first가 0이면 false 반환
			} 

			// LinkedList와 달리 Stack은 가장 최근에 저장된(first가 가리키는) 노드를 삭제
            element = this->first->data; // 삭제하기 전, 삭제할 노드의 데이터를 저장
			Node<T> *tmp = this->first; // 마지막 노드를 변경한 후에는 삭제할 노드의 위치를 알 수 없어 메모리가 누수되기 때문에 삭제할 노드를 임시 저장
			this->first = this->first->link; // 삭제하는 노드의 다음 노드를 첫 노드로 설정
			this->current_size--; // 노드의 수(스택의 크기) 감소
			delete tmp; // 임시로 만든 노드 할당 해제
			return true; // 정상적으로 삭제했으므로 true 반환
			
		}	
};
