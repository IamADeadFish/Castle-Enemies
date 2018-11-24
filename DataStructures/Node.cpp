#include "Node.h"


template<typename T>
Node<T>::Node()
	{
		Data=0;					//needs overloading
		Next=NULL;
	}




template<typename T>
Node<T>* Node<T>::GetNext()
	{
		return Next;
	}

template<typename T>
void Node<T>::SetNext(Node<T>* ptr)
	{
		Next=ptr;
	}

template<typename T>
void Node<T>::SetData(T data)
	{
		Data=data;
	}

template<typename T>
T Node<T>::GetData() const
	{
		return Data;
	}
