
#ifndef SORT_HPP
#define SORT_HPP

#include <Timothy_all.h>
#include <traits.hpp>
#include <type_traits>
#include <utility>

__TIMOTHY_NAMESPACE_BEGIN

template <typename T, typename L, typename R, T pv>
struct choose_min;

template <typename T, T... lvals, T pv>
struct choose_min<T, sequence<T, lvals...>, sequence<T>, pv> : ::std::pair<constant<T, pv>, sequence<T, lvals...>> {};

template <typename T, T... lvals, T first, T... rvals, T pv>
struct choose_min<T, sequence<T, lvals...>, sequence<T, first, rvals...>, pv>
    : ::std::conditional < pv < first, choose_min<T, sequence<T, lvals..., first>, sequence<T, rvals...>, pv>, choose_min<T, sequence<T, lvals..., pv>, sequence<T, rvals...>, first> >::type{};

template <typename lval_meta, typename rsequence>
struct choose_sort_join;

template <typename T, T lval, T... rvals>
struct choose_sort_join<constant<T, lval>, sequence<T, rvals...>> : ::std::enable_if<true, sequence<T, lval, rvals...>> {};

template <typename Seq>
struct choose_sort;

template <typename T>
struct choose_sort<sequence<T>> : ::std::enable_if<true, sequence<T>> {};

template <typename T, T first, T... vals>
struct choose_sort<sequence<T, first, vals...>>
    : choose_sort_join<typename choose_min<T, sequence<T>, sequence<T, vals...>, first>::first_type, typename choose_sort<typename choose_min<T, sequence<T>, sequence<T, vals...>, first>::second_type>::type> {};



__TIMOTHY_NAMESPACE_END

#endif // !SORT_HPP

