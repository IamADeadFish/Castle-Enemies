#ifndef Node_H
#define Node_H
#include <iostream>
template<typename T>
class Node
{
	T Data;
	Node* Next;
public:
	Node();

	Node<T>* GetNext();
	void SetNext(Node<T>*);     //needs operator overloading

	void SetData(T);       //needs operator overloading
	T GetData() const;          // needs operator overloading


};
#endif
