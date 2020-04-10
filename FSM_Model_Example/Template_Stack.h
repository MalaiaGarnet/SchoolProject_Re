#pragma once

/*
	���� ���ø�
*/

/*
	���
*/
template <typename T>
class StackNode
{
public:
	// ����
	T	m_Data;				// ���� ������ �ڷ�
	StackNode<T>* m_Before;	// ���� ����� �ּ�

	// ������
	StackNode<T>() : m_Data(0), m_Before(nullptr) {}				// ��带 �׳� ����� mData�� ���� ��带 �����
	StackNode(T _data) : m_Data(_data), m_Before(nullptr) {}		// Ÿ���� ���� ���ڰ��� �־��ָ� mData�� �ش� ���ڰ��� �����Ѵ�

	// �Ҹ���
	~StackNode() { delete m_Data; }			// ������ε� �Ҵ���� mData�� ����
};

template <typename T>
class Stack
{
private:
	// ����
	StackNode<T>* m_Floor;			// ������ �ٴ�
	StackNode<T>* m_Top;			// ������ ���� ���κ�
	int m_Count;							// ���� ������ ũ��

public:

	// ������
	Stack<T>()
	{
		m_Floor = new StackNode<T>();		// ���� �����ͷ� ���� ��带 m_Floor�� ����, m_Floor�� ������ �ʴ´�
		m_Top = m_Floor;							// ������ �ٴڰ� ���� ���κ��� �����ϵ��� �Ѵ�
		m_Count = 0;									// ����Ʈ�� ũ�⸦ 0���� ��´�
	}

	// �Ҹ���
	~Stack<T>()
	{
		StackNode<T>* ptr = m_Top;		// �����Ͱ� m_Top�� ���ϰ� �Ѵ�

		// ����Ű�� �ִ� ��尡 ���� ������ �ݺ�
		while (ptr != nullptr)
		{
			m_Top = ptr;				// m_Top�� ���� ���� �����Ѵ�
			ptr = ptr->m_Before;	// �����ʹ� ���� ��带 ���ϵ��� �Ѵ�
			delete m_Top;			// m_Top�� �ع�
		}
	}

	// ������ ���� ũ�⸦ ���Ѵ�
	int Size() { return m_Count; }

	// ���ÿ� ���� �ֱ�
	void Insert(T _data)
	{
		// ���ڰ����� ���� _data�� ��忡 �־��ش�
		StackNode<T>* ptr = new StackNode<T>(_data);

		ptr->m_Before = m_Top;	// ���� ���� ��尡 ���� õ���� ���� ���� ���ϵ��� ����
		m_Top = ptr;					// ���� õ���� �ڽ����� ����
		m_Count += 1;				// ũ��� ���� 1 ����
	}

	// ���ÿ��� ���� ������
	T Pop()
	{
		if (m_Count == 0)
			return nullptr;

		StackNode<T>* ptr = m_Top;	// �ӽ� ��带 ���� õ������ ����
		m_Top = ptr->m_Before;			// ���� õ���� �� �� ���� ���� ����
		m_Count -= 1;						// ũ��� ���� 1 ����

		return ptr->m_Data;	// ���� õ���� ��ȯ
	}

	T Peek()
	{
		if (m_Count == 0)
			return nullptr;

		return m_Top->m_Data;
	}
};