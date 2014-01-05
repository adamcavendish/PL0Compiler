#pragma once

#include <memory>
#include <type_traits>
#include <utility>

/*
 * Referin' to Paper of N3656.
 */

namespace auc {

template <typename T>
struct _Unique_if {
	typedef std::unique_ptr<T> _Single_object;
};

template <typename T>
struct _Unique_if<T[]> {
	typedef std::unique_ptr<T[]> _Unknown_bound;
};

template <typename T, size_t N>
struct _Unique_if<T[N]> {
	typedef void _Known_bound;
};

template <typename T, typename ... Args>
typename _Unique_if<T>::_Single_object
make_unique(Args && ... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
typename _Unique_if<T>::_Unknown_bound
make_unique(size_t n) {
	typedef typename std::remove_extent<T>::type U;
	return std::unique_ptr<T>(new U[n]());
}

template <class T, class... Args>
typename _Unique_if<T>::_Known_bound
make_unique(Args && ...) {
	static_assert(std::extent<T>::value == 0,
			"make_unique<T[N]>() is forbidden, please use make_unique<T[]>() version.");
}

}//namespace auc

