
#include "MacroFunctionOverload.h"

#define TIMOTHY_STRUCT_NAME foo
#define TIMOTHY_STRUCT_BODY \
TIMOTHY_MEMBER_INT32(i32, 5)

#include "struct_generator.hpp"

int main()
{
	//TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_INT(5, 4, "5");
	//TIMOTHY_MACRO_FUNCTION_OVERLOAD_PRINT_ZERO("");

	return 0;
}
