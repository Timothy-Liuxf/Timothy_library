#ifndef TIMOTHY_STRUCT_NAME
#error You must define TIMOTHY_STRUCT_NAME to specify the name of the struct.
#endif

#ifndef TIMOTHY_STRUCT_BODY
#error You must define TIMOTHY_STRUCT_BODY to define members if the struct
#endif

#include <iostream>
#include <cstdint>

struct TIMOTHY_STRUCT_NAME
{

#undef TIMOTHY_MEMBRE_INT16
#define TIMOTHY_MEMBER_INT16(name, ...) ::std::int16_t name = { __VA_ARGS__ };

#undef TIMOTHY_MEMBRE_INT32
#define TIMOTHY_MEMBER_INT32(name, ...) ::std::int32_t name = { __VA_ARGS__ };

	TIMOTHY_STRUCT_BODY
};

inline ::std::ostream& operator<< (::std::ostream& o, const TIMOTHY_STRUCT_NAME& st)
{
#undef TIMOTHY_MEMBRE_INT16
#define TIMOTHY_MEMBER_INT16(name, ...) ::std::cout << #name" = " << name << ::std::endl;

#undef TIMOTHY_MEMBRE_INT32
#define TIMOTHY_MEMBER_INT32(name, ...) ::std::cout << #name" = " << name << ::std::endl;

	TIMOTHY_STRUCT_BODY
}

#undef TIMOTHY_STRUCT_BODY
#undef TIMOTHY_STRUCT_NAME
