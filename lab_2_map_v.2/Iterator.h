#pragma once
#include <cstddef>

template <class T, class T2>
class Iterator
{
public:
	virtual T2 operator*() const = 0;
	virtual void operator++(int) = 0;
	virtual bool operator==(const nullptr_t) const = 0;
	virtual bool operator!=(const nullptr_t) const = 0;
	virtual T current_key() = 0;
	virtual char current_color() = 0;
};