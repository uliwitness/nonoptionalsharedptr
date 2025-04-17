#pragma once

#include <memory>

/*
	Companion to nonoptional_shared_ptr that forces you to call lock() to access the actual
 	underlying shared_ptr, the idea being that, like with weak_ptr, you access it by checking
 	the result beforehand, like
	if (auto sptr = osptr.lock()) {
 		sptr->foo();
 	}
 	This mostly just serves as a more obvious marker that a pointer may be an optional,
 	and that code has been reviewed against being optional, and isn't just a historical
 	shared_ptr.

 */

template<class T>
class optional_shared_ptr {
public:
	optional_shared_ptr(const std::shared_ptr<T> &p) : _ptr(p) {}
	optional_shared_ptr<T>& operator= (const optional_shared_ptr<T>& p) { _ptr = p._ptr; }
	optional_shared_ptr<T>& operator= (const std::shared_ptr<T>& p) { _ptr = p; }

	std::shared_ptr<T> lock() { return _ptr; }

	operator bool () { return _ptr != nullptr; }

protected:
	std::shared_ptr<T> _ptr;
};