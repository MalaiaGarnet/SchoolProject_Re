#pragma once

/*
	연결 리스트 템플릿
*/

/*
	노드
*/
template <typename T>
class ListNode
{
public:
	// 변수
	T	m_Data;				// 현재 보유한 자료
	ListNode<T>* m_Next;	// 다음 노드의 주소

	// 생성자
	ListNode<T>() : m_Data(0), m_Next(nullptr) {}				// 노드를 그냥 만들면 m_Data가 없이 노드를 만든다
	ListNode(T _data) : m_Data(_data), m_Next(nullptr) {}		// 타입이 같은 인자값을 넣어주면 m_Data에 해당 인자값을 대입한다

	// 소멸자
	~ListNode()
	{ }
};


/*
	연결 리스트
*/
template <typename T>
class LinkedList
{
private:
	// 변수
	ListNode<T>* m_Head;		// 리스트의 가장 앞부분
	ListNode<T>* m_Tail;			// 리스트의 가장 뒷부분
	int    m_NodeCount;		// 현재 리스트의 크기

public:
	// 생성자
	LinkedList<T>()
	{
		m_Head = new ListNode<T>();		// 더미 데이터로 쓰일 노드를 m_Head에 대입	
		m_Tail = m_Head;					// 리스트의 가장 뒷부분과 앞부분이 동일하도록 한다
		m_NodeCount = 0;				// 리스트의 크기를 0으로 잡는다
	}

	// 소멸자
	~LinkedList<T>()
	{
		ListNode<T>* ptr = m_Head->m_Next;	// 포인터가 더미 데이터인 m_Head의 다음 노드를 향하도록 한다
		delete m_Head;							// 쓸모없는 m_Head는 바로 지운다

		// 가리키고 있는 노드가 없을 때까지 반복
		while (ptr != nullptr)
		{
			m_Head = ptr;			// m_Head를 현재 노드로 설정한다
			ptr = ptr->m_Next;	// 포인터는 다음 노드를 향하도록 한다
			delete m_Head;		// m_Head를 해방
		}
	}

	// 리스트의 현재 크기(연결된 노드들의 개수)를 구한다
	int Size() { return m_NodeCount; }

	ListNode<T>* Get_Head()
	{ return m_Head; }

	// 리스트에 객체 넣기
	bool Insert(T _data)
	{
		// 인자값으로 받은 _data를 노드에 넣어준다
		ListNode<T>* ptr = new ListNode<T>(_data);

		m_Tail->m_Next = ptr;	// 리스트의 가장 뒷부분을 가리키는 m_Tail의 다음 노드를 현재 만든 노드로 설정
		m_Tail = ptr;				// m_Tail을 현재 만든 노드로 설정
		m_NodeCount++;			// 리스트 크기를 1 증가
		return true;
	}

	// 리스트에서 변수 지우기
	bool Delete(T _data)
	{
		ListNode<T>* pre = m_Head;			// 이전 노드
		ListNode<T>* ptr = pre->m_Next;	// 현재 노드

		// 가리키고 있는 노드가 없을 때까지 반복
		while (ptr != nullptr)
		{
			if (ptr->m_Data == _data)			// 현재 노드가 가진 자료가 인자값으로 받은 자료와 일치하다면
			{
				pre->m_Next = ptr->m_Next;	// 이전 노드의 [다음 노드 주소]를 현재 노드의 [다음 노드 주소]로 설정
				if (ptr->m_Next == nullptr)		// 만약 현재 노드의 [다음 노드 주소]가 없다면
				{
					m_Tail = pre;					// 현재 노드가 리스트의 가장 뒷부분에 있다는 뜻이 되므로, m_Tail이 이전 노드를 가리키도록 한다
				}
				delete ptr;							// 현재 노드를 해방
				m_NodeCount--;					// 리스트 크기를 1 감소
				return true;								// 노드를 지웠으므로 반복문을 지속할 필요가 없다. 탈출
			}
			// 현재 노드가 가진 자료가 인자값으로 받은 자료와 불일치하는 경우에는
			pre = ptr;				// 이전 노드가 현재 노드를 가리키도록 한다
			ptr = ptr->m_Next;	// 현재 노드는 [다음 노드 주소]를 가리키도록 한다
		}
		return false;
	}
};