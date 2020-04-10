#pragma once

/*
	스택 템플릿
*/

/*
	노드
*/
template <typename T>
class StackNode
{
public:
	// 변수
	T	m_Data;				// 현재 보유한 자료
	StackNode<T>* m_Before;	// 이전 노드의 주소

	// 생성자
	StackNode<T>() : m_Data(0), m_Before(nullptr) {}				// 노드를 그냥 만들면 mData가 없이 노드를 만든다
	StackNode(T _data) : m_Data(_data), m_Before(nullptr) {}		// 타입이 같은 인자값을 넣어주면 mData에 해당 인자값을 대입한다

	// 소멸자
	~StackNode() { delete m_Data; }			// 어떤식으로든 할당받은 mData를 제거
};

template <typename T>
class Stack
{
private:
	// 변수
	StackNode<T>* m_Floor;			// 스택의 바닥
	StackNode<T>* m_Top;			// 스택의 가장 윗부분
	int m_Count;							// 현재 스택의 크기

public:

	// 생성자
	Stack<T>()
	{
		m_Floor = new StackNode<T>();		// 더미 데이터로 쓰일 노드를 m_Floor에 대입, m_Floor는 쓰이지 않는다
		m_Top = m_Floor;							// 스택의 바닥과 가장 윗부분이 동일하도록 한다
		m_Count = 0;									// 리스트의 크기를 0으로 잡는다
	}

	// 소멸자
	~Stack<T>()
	{
		StackNode<T>* ptr = m_Top;		// 포인터가 m_Top을 향하게 한다

		// 가리키고 있는 노드가 없을 때까지 반복
		while (ptr != nullptr)
		{
			m_Top = ptr;				// m_Top를 현재 노드로 설정한다
			ptr = ptr->m_Before;	// 포인터는 이전 노드를 향하도록 한다
			delete m_Top;			// m_Top를 해방
		}
	}

	// 스택의 현재 크기를 구한다
	int Size() { return m_Count; }

	// 스택에 변수 넣기
	void Insert(T _data)
	{
		// 인자값으로 받은 _data를 노드에 넣어준다
		StackNode<T>* ptr = new StackNode<T>(_data);

		ptr->m_Before = m_Top;	// 현재 만든 노드가 스택 천장을 이전 노드로 향하도록 설정
		m_Top = ptr;					// 스택 천장을 자신으로 설정
		m_Count += 1;				// 크기용 변수 1 증가
	}

	// 스택에서 변수 빼내기
	T Pop()
	{
		if (m_Count == 0)
			return nullptr;

		StackNode<T>* ptr = m_Top;	// 임시 노드를 스택 천장으로 설정
		m_Top = ptr->m_Before;			// 스택 천장은 한 층 낮은 노드로 설정
		m_Count -= 1;						// 크기용 변수 1 감소

		return ptr->m_Data;	// 빼낸 천장을 반환
	}

	T Peek()
	{
		if (m_Count == 0)
			return nullptr;

		return m_Top->m_Data;
	}
};