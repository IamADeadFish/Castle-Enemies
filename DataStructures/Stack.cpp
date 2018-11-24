#include "Stack.h"

template<typename T>
Stack<T>::Stack()
{
	Top=NULL;
	Size=0;
}

template<typename T>
Stack<T>::Stack(const T& Data)
{
	Node<T>* NodeToAdd=new Node<T>;
	if(!NodeToAdd)													// memory is full
	{
		Top=NULL;
		return;
	}
	NodeToAdd->SetData(Data);
	Top=NodeToAdd;
}

template<typename T>
Stack<T>::~Stack()
{
	Clear();
}

template<typename T>
bool Stack<T>::Pop()
{
	if(IsEmpty())
		return false;
	Node<T>* Temp;
	Temp=Top;
	Top=Top->GetNext();
	Temp->SetNext(NULL);
	delete Temp;
	Size--;
	return true;
}

template<typename T>
T Stack<T>::Peek()
{
	assert(!IsEmpty());
	return Top->GetData();
}

template<typename T>
bool Stack<T>::Push(const T& Data)
{
	Node<T>* NodeToAdd=new Node<T>;
	if(!NodeToAdd)															//memory is full
		return false;
	NodeToAdd->SetData(Data);
	NodeToAdd->SetNext(Top);
	Top=NodeToAdd;
	Size++;
	return true;
}

template<typename T>
void Stack<T>::Reverse()
{
	Stack<T>aux;
	Stack<T>aux2;
	while (!IsEmpty())
	{
		aux.Push(Peek());
		Pop();
	}
	while (!aux.IsEmpty())
	{
		aux2.Push(aux.Peek());
		aux.Pop();
	}
	while (!aux2.IsEmpty())
	{
		Push(aux2.Peek());
		aux2.Pop();
	}
}


template<typename T>
bool Stack<T>::IsEmpty() const
{
	if(!Top)
		return true;
	return false;
}

template<typename T>
int Stack<T>::GetSize() const
{
	return Size;
}

			
												/*utility function*/						
																
template<typename T>
void Stack<T>::Clear()
{
	while(!(IsEmpty()))
	{
		Pop();
	}
}
