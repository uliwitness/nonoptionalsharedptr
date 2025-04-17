#pragma once

#include <memory>
#include <functional>
#include <exception>
#include "optional_shared_ptr.hpp"

/*  Since shared_ptr may always be nullptr, optional<shared_ptr<T>> makes no sense, that's what it already is.
    But that means we need a non-nullable version of shared_ptr. This file is it.

    Prerequisites: 1. Can't be assigned a null value (like an un-checked shared_ptr)
                   2. Can be assigned a non-null value
                   3. Can be copied to a shared_ptr or another nonoptional_shared_ptr

    Would probably also need nonoptional_shared_ptr-returning versions of make_shared<T> etc.
*/

template<class T>
class nonoptional_shared_ptr {
public:
	nonoptional_shared_ptr(const nonoptional_shared_ptr<T>& p) : _ptr(p._ptr) {}
	nonoptional_shared_ptr<T>& operator= (const nonoptional_shared_ptr<T>& p) { _ptr = p._ptr; return *this; }

	operator std::shared_ptr<T> () { return _ptr; }

	T* get() { return _ptr.get(); }
	T* operator -> () { return _ptr.get(); }
	T& operator * () { return *_ptr; }

	// Add more methods here that forward shared_ptr methods so it can be used same way.

protected:
	explicit nonoptional_shared_ptr(const std::shared_ptr<T>& p) : _ptr(p) {}
	std::shared_ptr<T> _ptr;

	template<class B>
	friend void if_nonnullptr(const std::shared_ptr<B> &possiblyNull, const std::function<void(const nonoptional_shared_ptr<B>&)> &nonnullHandler, const std::function<void(void)> &nullHandler);
	template<class C, typename... Args>
	friend nonoptional_shared_ptr<C> make_nonoptional_shared(Args&&... args);
};

template<class T>
static void if_nonnullptr(const std::shared_ptr<T> &possiblyNull, const std::function<void(const nonoptional_shared_ptr<T>&)> &nonnullHandler, const std::function<void(void)> &nullHandler) {
	if (possiblyNull) {
		nonnullHandler(nonoptional_shared_ptr(possiblyNull));
	} else {
		nullHandler();
	}
}

template<class T>
static void if_nonnullptr(const std::shared_ptr<T> &possiblyNull, const std::function<void(const nonoptional_shared_ptr<T>&)> &nonnullHandler) {
	if (possiblyNull) {
		nonnullHandler(nonoptional_shared_ptr(possiblyNull));
	} else {
		throw std::bad_alloc();
	}
}

template<class T, typename... Args>
static nonoptional_shared_ptr<T> make_nonoptional_shared(Args&&... args) {
	std::shared_ptr<T> possiblyNull = std::make_shared<T>(std::forward<Args>(args)...);
	if (!possiblyNull) {
		throw std::bad_alloc();
	}
	return nonoptional_shared_ptr(possiblyNull);
}

