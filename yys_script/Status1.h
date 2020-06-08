#pragma once
#include "Enum.h"

template<typename T>
class Status1
{
public:
	Status1(T pre, T now)
		: status_pre(pre)
		, status_now(now)
	{

	};

	void change_status(T next);

	T current_status() const;

	T pre_status() const;

	T status_pre;
	T status_now;

};

template <typename T>
void Status1<T>::change_status(T next)
{
	status_pre = status_now;
	status_now = next;
}

template <typename T>
T Status1<T>::current_status() const
{
	return status_now;
}

template <typename T>
T Status1<T>::pre_status() const
{
	return status_pre;
}
