#ifndef HEAP_H
#define HEAP_H
#include <cassert>
template <class T>
class Heap
{
	T * arr;
	int Count;
	int Size;
	int getLeftChildIndex (int parent)const;
	int getRightChildIndex (int parent)const;
	int getParentIndex (int child)const;
	bool isLeaf (int index)const;
public:
	Heap(int s=300);
	bool isEmpty() const;
	int getNumberOfNodes () const;
	T peekTop() const;
	bool add(T t);
	bool remove();
	void clear();
	~Heap();
};
#endif
