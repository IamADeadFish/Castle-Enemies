#ifndef COMPARE_H
#define COMPARE_H

template <class T>
class Compare
{
public:
	static bool Comp(const T &t1, const T &t2)
	{
		return t1<t2;
	}
};


template <class T>
class Compare<T*>
{
	public:
	static bool Comp(const T* t1,const T* t2)
	{
		return Compare<T>::Comp(*t1,*t2);
	}
};
#endif