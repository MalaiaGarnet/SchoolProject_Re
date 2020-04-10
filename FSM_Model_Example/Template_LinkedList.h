#pragma once

/*
	���� ����Ʈ ���ø�
*/

/*
	���
*/
template <typename T>
class ListNode
{
public:
	// ����
	T	m_Data;				// ���� ������ �ڷ�
	ListNode<T>* m_Next;	// ���� ����� �ּ�

	// ������
	ListNode<T>() : m_Data(0), m_Next(nullptr) {}				// ��带 �׳� ����� m_Data�� ���� ��带 �����
	ListNode(T _data) : m_Data(_data), m_Next(nullptr) {}		// Ÿ���� ���� ���ڰ��� �־��ָ� m_Data�� �ش� ���ڰ��� �����Ѵ�

	// �Ҹ���
	~ListNode()
	{ }
};


/*
	���� ����Ʈ
*/
template <typename T>
class LinkedList
{
private:
	// ����
	ListNode<T>* m_Head;		// ����Ʈ�� ���� �պκ�
	ListNode<T>* m_Tail;			// ����Ʈ�� ���� �޺κ�
	int    m_NodeCount;		// ���� ����Ʈ�� ũ��

public:
	// ������
	LinkedList<T>()
	{
		m_Head = new ListNode<T>();		// ���� �����ͷ� ���� ��带 m_Head�� ����	
		m_Tail = m_Head;					// ����Ʈ�� ���� �޺κа� �պκ��� �����ϵ��� �Ѵ�
		m_NodeCount = 0;				// ����Ʈ�� ũ�⸦ 0���� ��´�
	}

	// �Ҹ���
	~LinkedList<T>()
	{
		ListNode<T>* ptr = m_Head->m_Next;	// �����Ͱ� ���� �������� m_Head�� ���� ��带 ���ϵ��� �Ѵ�
		delete m_Head;							// ������� m_Head�� �ٷ� �����

		// ����Ű�� �ִ� ��尡 ���� ������ �ݺ�
		while (ptr != nullptr)
		{
			m_Head = ptr;			// m_Head�� ���� ���� �����Ѵ�
			ptr = ptr->m_Next;	// �����ʹ� ���� ��带 ���ϵ��� �Ѵ�
			delete m_Head;		// m_Head�� �ع�
		}
	}

	// ����Ʈ�� ���� ũ��(����� ������ ����)�� ���Ѵ�
	int Size() { return m_NodeCount; }

	ListNode<T>* Get_Head()
	{ return m_Head; }

	// ����Ʈ�� ��ü �ֱ�
	bool Insert(T _data)
	{
		// ���ڰ����� ���� _data�� ��忡 �־��ش�
		ListNode<T>* ptr = new ListNode<T>(_data);

		m_Tail->m_Next = ptr;	// ����Ʈ�� ���� �޺κ��� ����Ű�� m_Tail�� ���� ��带 ���� ���� ���� ����
		m_Tail = ptr;				// m_Tail�� ���� ���� ���� ����
		m_NodeCount++;			// ����Ʈ ũ�⸦ 1 ����
		return true;
	}

	// ����Ʈ���� ���� �����
	bool Delete(T _data)
	{
		ListNode<T>* pre = m_Head;			// ���� ���
		ListNode<T>* ptr = pre->m_Next;	// ���� ���

		// ����Ű�� �ִ� ��尡 ���� ������ �ݺ�
		while (ptr != nullptr)
		{
			if (ptr->m_Data == _data)			// ���� ��尡 ���� �ڷᰡ ���ڰ����� ���� �ڷ�� ��ġ�ϴٸ�
			{
				pre->m_Next = ptr->m_Next;	// ���� ����� [���� ��� �ּ�]�� ���� ����� [���� ��� �ּ�]�� ����
				if (ptr->m_Next == nullptr)		// ���� ���� ����� [���� ��� �ּ�]�� ���ٸ�
				{
					m_Tail = pre;					// ���� ��尡 ����Ʈ�� ���� �޺κп� �ִٴ� ���� �ǹǷ�, m_Tail�� ���� ��带 ����Ű���� �Ѵ�
				}
				delete ptr;							// ���� ��带 �ع�
				m_NodeCount--;					// ����Ʈ ũ�⸦ 1 ����
				return true;								// ��带 �������Ƿ� �ݺ����� ������ �ʿ䰡 ����. Ż��
			}
			// ���� ��尡 ���� �ڷᰡ ���ڰ����� ���� �ڷ�� ����ġ�ϴ� ��쿡��
			pre = ptr;				// ���� ��尡 ���� ��带 ����Ű���� �Ѵ�
			ptr = ptr->m_Next;	// ���� ���� [���� ��� �ּ�]�� ����Ű���� �Ѵ�
		}
		return false;
	}
};