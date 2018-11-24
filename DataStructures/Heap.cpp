#include "Heap.h"
#include "Compare.h"

template <class T>
Heap<T>::Heap(int s)
{
	Size=s;
	Count=0;
	arr=new T[Size];
}

template <class T>
int Heap<T>::getLeftChildIndex(int parent)const
{
	if(2*parent+1<Count)
		return (2*parent+1);
	return -1;
}

template <class T>
int Heap<T>::getRightChildIndex (int parent) const
{
	if(2*parent+2<Count)
		return (2*parent+2);
	return -1;
}

template <class T>
int Heap<T>::getParentIndex(int child) const
{
	if(child != 0)
		return (child-1)/2;
	return -1;
}

template <class T>
bool Heap<T>::isLeaf(int index)const
{
	if((2*index+1) > Count)
		return true;
	return false;
}

template <class T>
bool Heap<T>::isEmpty() const
{
	return (Count==0);
}

template <class T>
int Heap<T>::getNumberOfNodes() const
{
	return Count;
}

template <class T>
T Heap<T>::peekTop() const
{
	assert(!isEmpty());
	return arr[0];
}

template <class T>
bool Heap<T>::add(T t)
{
	if(Count==Size)
		return false;
	int idx=Count++;
	arr[idx]=t;
	while (getParentIndex(idx)!=-1)
	{
		if(Compare<T>::Comp(arr[getParentIndex(idx)],arr[idx]))
		{
			arr[idx]=arr[getParentIndex(idx)];
			idx=getParentIndex(idx);
			arr[idx]=t;
		}
		else
			break;
	}
	return true;
}

template <class T>
bool Heap<T>::remove()
{
	if(isEmpty())
		return false;
	arr[0]=arr[--Count];
	int idx=0;
	while(getLeftChildIndex(idx)!=-1)
	{

		if((getRightChildIndex(idx)==-1 || Compare<T>::Comp(arr[getRightChildIndex(idx)],arr[getLeftChildIndex(idx)])) && Compare<T>::Comp(arr[idx],arr[getLeftChildIndex(idx)]))
		{
			T temp=arr[idx];
			arr[idx]=arr[getLeftChildIndex(idx)];
			idx = getLeftChildIndex(idx);
			arr[idx]=temp;
		}
		else if(getRightChildIndex(idx)!=-1 && Compare<T>::Comp(arr[getLeftChildIndex(idx)],arr[getRightChildIndex(idx)]) && Compare<T>::Comp(arr[idx],arr[getRightChildIndex(idx)]))
		{
			T temp=arr[idx];
			arr[idx]=arr[getRightChildIndex(idx)];
			idx = getRightChildIndex(idx);
			arr[idx]=temp;
		}
		else
			break;
	}
	return true;
}

template <class T>
void Heap<T>::clear()
{
	Count=0;
}

template <class T>
Heap<T>::~Heap()
{
	clear();
	arr=nullptr;
}
