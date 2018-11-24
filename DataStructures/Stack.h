#ifndef Stack_H
#define Stack_H
#include "Node.cpp"
#include <cassert>
template<typename T>
class Stack
{
	Node<T>* Top;
	int Size;
	void Clear();							//utility used in destructor
public:
	Stack();
	Stack(const T&);
	~Stack();

	bool IsEmpty() const;
	bool Pop();
	T Peek();
	bool Push(const T&);
	void Reverse();
	int GetSize() const;
};
#endif
