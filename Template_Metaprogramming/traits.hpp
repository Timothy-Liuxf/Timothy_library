
#ifndef TRAITS_HPP

#define TRAITS_HPP

#include "Timothy_all.h"

__TIMOTHY_NAMESPACE_BEGIN

template <typename T, T... vals>
struct sequence {};

template <typename T, T val>
struct constant
{
    static inline constexpr const T value = val;
};

__TIMOTHY_NAMESPACE_END

#endif // !TRAITS_HPP
