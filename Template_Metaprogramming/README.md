# metaalgorithm (Unfinished, updating...)

Some algorithm realized with templates. The result is saved in the static constant member variable named `val` of every templates below.  

+ `meta_type`: Basic data type. Belows are some specializations defined to use directly:  
  
  + `meta_int`
  + `meta_schar`: `signed char`
  + `meta_wchar`
  + `meta_short`
  + `meta_long`
  + `meta_long_long`
  + `meta_uint`
  + `meta_uchar`
  + `meta_ushort`
  + `meta_ulong`
  + `meta_ulong_long`
  + `meta_intn`: Where `n` can be 8, 16, 32 or 64
  + `meta_float`: Need cxx20
  + `meta_double`: Need cxx20
  + `meta_long_double`: need cxx20

+ Four basic operations: 

  + `meta_add<_Meta_Ty1, _Meta_Ty2>`
  + `meta_sub<_Meta_Ty1, _Meta_Ty2>`
  + `meta_mul<_Meta_Ty1, _Meta_Ty2>`: multiply
  + `meta_div<_Meta_Ty1, _Meta_Ty2>`: division

examples:  

```cpp
#include <iostream>
#include <metaalgorithm.h>
using namespace Timothy;

int main()
{
    std::cout << meta_add<meta_uint32<16>, meta_uint32<4>>::val << std::endl;   //9
    return 0;
}
```

---
  > **Notice: If you want to use cxx20, you should define `TIMOTHY_CXX20_SUPPORT` ahead of this file.**  
  > **Example:**

  ```cpp
  #define TIMOTHY_CXX20_SUPPORT
  #include <metaalgorithm>
  #include <iostream>
  using std::cout;
  using std::endl;
  using namespace Timothy;
  int main()
  {
      std::cout << meta_double<5.5>::val << std::endl;  //5.5
      return 0;
  }
  ```

---

+ `factorial<unsigned int n>`: Calculate *n*!.  

+ `double<unsigned int n>`: Calculate *n*!!.

examples:  

```cpp
#include <iostream>
#include <metaalgorithm.h>
using namespace Timothy;

int main()
{
    std::cout << factorial<5>::val << std::endl;    //120
    return 0;
}
```

---

+ `number_of_permutation<unsigned int n, unsigned int m>`: Calculate the number of permutation *P*(*n*, *m*).  

+ `number_of_combination<unsigned int n, unsigned int m>`: Calculate the number of combination *C*(*n*, *m*).  

examples:  

```cpp
#include <iostream>
#include <metaalgorithm.h>
using namespace Timothy;

int main()
{
    std::cout << number_of_permutation<4, 2>::val << std::endl; //12
    std::cout << number_of_combination<4, 2>::val << std::endl; //6
    return 0;
}
```

---

+ `meta_continuous_sum<unsigned int n>`: Calculate the sum from 1 to n.  

+ `meta_sum<typename _Ty, _Ty... nums>`: Calculate the sum of all numbers of type `_Ty`.  

examples:  

```cpp
#include <iostream>
#include <metaalgorithm.h>
using namespace Timothy;

int main()
{
    std::cout << meta_continuous_sum<4>::val << std::endl; //10
    std::cout << meta_sum<int, 1, 10, 20>::val << std::endl; //31
    return 0;
}
```

---

+ `meta_average<typename _Ty, typename _ResTy, _Ty...  nums>`: Calculate the average (of type `_ResTy`) of all the numbers *nums* (of type `_Ty`).  

+ `meta_auto_average<typename _Ty, _Ty... nums>`: Calculate the average (of type `_Ty`) of all the numbers *nums* (of type `_Ty`).  

examples:  

```cpp
#include <iostream>
#include <metaalgorithm.h>
using namespace Timothy;

int main()
{
    std::cout << meta_average<int, double, 1, 2, 3, 4>::val << std::endl; //2.5
    std::cout << meta_auto_average<int, 1, 2, 3, 4>::val << std::endl; //2
    return 0;
}
```

---

+ `meta_factorial_sum<unsigned int from, unsigned int to>`: Calculate the sum from the factorial of *from* to that of *to*.  

+ `meta_factorial_sum_from_zero<unsigned int n>`: Calculate the sum from the factorial of 0 to that of *n*. In other words, 0!+1!+...+*n*!  

+ `meta_factorial_sum_from_one<unsigned int n>`: Calculate the sum from the factorial of 1 to that of *n*. In other words, 1!+2!+...+*n*!  

examples:  

```cpp
#include <iostream>
#include <metaalgorithm.h>
using namespace Timothy;

int main()
{
    std::cout << meta_factorial_sum<2, 3>::val << std::endl; //8
    std::cout << meta_auto_average_from_zero<3>::val << std::endl; //10
    std::cout << meta_auto_average_from_one<3>::val << std::endl; //9
    return 0;
}
```

---

`is_prime<unsigned int n>`: Determine if *n* is a prime number.  
`is_composite<unsigned int n>`: Determine if *n* is a composite number.  

examples:  

```cpp
#include <iostream>
#include <metaalgorithm.h>
using namespace Timothy;

int main()
{
    if constexpr (is_prime<3>::val)             //3 is a prime number, true
    {
        /*code*/
    }
    else if constexpr (is_composite<3>::val)    //3 is not a composite number, false
    {
        /*code*/
    }
    return 0;
}
```

---

+ `second_order_homogeneous_linear_recursive_sequence<unsigned int n, long long initial0, long long initial1, long long para1, long long para2>`:  
  Assume that *f*(0)=*initial0*, *f*(1)=*initial1*, *f*(*k*)=*para1*\**f*(*k*-1)+*para2*\**f*(*k*-2), then calculate *f*(*n*).

+ `fibonacci<unsigned int n>`: Calculate the *n*th number of Fibonacci sequence.

examples:  

```cpp
#include <iostream>
#include <metaalgorithm.h>
using namespace Timothy;

int main()
{
    std::cout << fibonacci<10>::val << std::endl;   //55
    cout << second_order_homogeneous_linear_recursive_sequence<5, 1, 2, 2, 3>::val << std::endl;    //182: f(0) = 1, f(1) = 2, f(k) = 2 * f(k - 1) + 3 * f(k - 2), then f(5) = 182
    return 0;
}
```
