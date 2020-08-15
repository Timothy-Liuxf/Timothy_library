
#ifndef MATRIX_TIM_H

#define MATRIX_TIM_H

#include <Timothy_all.h>

__TIMOTHY_NAMESPACE_BEGIN

template <typename _Elem, unsigned int _dim>					//a _dim dimensions vector in R^_dim
class vector
{
public:
	vector() { _vec = new _Elem[_dim]{ 0 }; }
	vector(const vector& _srcvector);
	vector(vector&& _srcvector) noexcept;
	~vector() { delete[] _vec; }
private:
	_Elem* _vec;
};

template <typename _Elem, unsigned int _row, unsigned int _col>
class matrix													//matrix<_ELem> which is a _row ¡Á _col matrix
{
public:
	matrix();
	matrix(const matrix& _srcmatrix);
	matrix(matrix&& _srcmatrix) noexcept;
	~matrix() { delete[] _mat; };
private:
	_Elem* _mat;
};


__TIMOTHY_NAMESPACE_END

#endif
