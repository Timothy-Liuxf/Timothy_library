#ifndef EXTENSION_TIM_H

#define EXTENSION_TIM_H

#include <Timothy_All.h>

__TIMOTHY_NAMESPACE_BEGIN

template <typename Iteratable>
struct _Make_Revserse_t
{
	Iteratable&& iteratable;
	auto begin() { return iteratable.rbegin(); }
	auto end() { return iteratable.rend(); }
};

template <typename Iteratable>
inline _Make_Revserse_t<Iteratable> MakeReverse(Iteratable&& iteratable)
{
	return { iteratable };
}

__TIMOTHY_NAMESPACE_END


#endif //!EXTENSION_TIM_H
