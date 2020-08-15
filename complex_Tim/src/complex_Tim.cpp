
#include "complex_Tim.h"

__TIMOTHY_NAMESPACE_BEGIN

long double re_calculate::sqrt(long double x)
{
	if (x < 0.0L) throw math_error();
	if (x == 0.0L) return 0.0L;
	long double rt = x * 0.5L, last_rt = rt;
	do
	{
		rt = x * 0.5L / rt + (last_rt = rt) * 0.5L;
	} while (abs(rt - last_rt) > rt * (1.0e-15L));
	return rt;
}

long double re_calculate::logarithm(long double x)
{
	long double y = 1.0 - 2.0l / (x + 1.0);
	long double z = 1, s = 0, y2 = y * y;
	long long n = 1;
	for (s = 1; z != 0; s += ((z *= y2) / (n += 2ll)));
	return s * 2 * y;
}

long double re_calculate::log(long double x)
{
 	if (x <= 0) throw math_error();
	long long k = 0, l = 0;	//k---10; l---1.22
	for (; x > 1; ++k) x /= 10.0;
	for (; x < 0.1; --k) x *= 10.0;
	for (; x < 0.905; ++l) x *= 1.22;
	return logarithm(x) + k * TIMOTHY_COMPLEX_LOG10 - l * TIMOTHY_COMPLEX_LOG1_22;
}

long double re_calculate::log10(long double x)
{
	return log(x) / TIMOTHY_COMPLEX_LOG10;
}

long double re_calculate::logn(long double n, long double x)
{
	if (n > 0 && n != 1) return log(x) / log(n);
	throw math_error();
}

long double re_calculate::exp(long double x)
{
	long double z = 1, s = 1, fac = 1, term = z;
	int n = 0;
	bool flag = false;
	if (x < 0) { x = -x; flag = true; }
	for (; term > 1e-25; s += term = (z *= x) / (fac *= ++n));
	return flag ? 1.0L / s : s;
}

long double re_calculate::pow(long double n, long double x)
{
	if (n == 0.0L)
	{
		if (x == 0.0L) return 1.0L;
		else if (x > 0.0L) return 0.0L;
		else throw math_error();
	}
	return exp(x * log(n));
}

long double re_calculate::sine(long double x)
{
	long double sum = 1, y = x * x, z;
	signed char flag = 1;
	long long n = 1, fac = 1;
	for (z = 1; z / fac > 0; sum += (flag = -flag) * (z *= y) / fac) { fac *= (++n); fac *= (++n); }
	return x * sum;
}

long double re_calculate::cosine(long double x)
{
	long double sum = 1, z;
	x *= x;
	signed char flag = 1;
	long long n = 0, fac = 1;
	for (z = 1; z / fac > 0; sum += (flag = -flag) * (z *= x) / fac) { fac *= (++n); fac *= (++n); }
	return sum;
}

long double re_calculate::sin(long double x)
{
	char flag = 1;
	if (x > 100.0L)
	{
		long long tmp = static_cast<long long>((x - TIMOTHY_COMPLEX_PI_2) / TIMOTHY_COMPLEX_PI);
		flag = tmp % 2 ? -1 : 1;
		x -= tmp * TIMOTHY_COMPLEX_PI;
	}
	else if (x < -100.0L)
	{
		long long tmp = static_cast<long long>((-TIMOTHY_COMPLEX_PI_2 - x) / TIMOTHY_COMPLEX_PI);
		flag = tmp % 2 ? -1 : 1;
		x += tmp * TIMOTHY_COMPLEX_PI;
	}
	for (; x > TIMOTHY_COMPLEX_PI_2; x -= TIMOTHY_COMPLEX_PI) flag = -flag;
	for (; x < -TIMOTHY_COMPLEX_PI_2; x += TIMOTHY_COMPLEX_PI) flag = -flag;
	if (x > TIMOTHY_COMPLEX_PI_4 + 1e-10L) return flag * cosine(TIMOTHY_COMPLEX_PI_2 - x);
	if (x < -TIMOTHY_COMPLEX_PI_4 - 1e-10L) return -flag * cosine(TIMOTHY_COMPLEX_PI_2 + x);
	return flag * sine(x);
}

long double re_calculate::cos(long double x)
{
	char flag = 1;
	if (x > 100.0L)
	{
		long long tmp = static_cast<long long>((x - TIMOTHY_COMPLEX_PI_2) / TIMOTHY_COMPLEX_PI);
		flag = tmp % 2 ? -1 : 1;
		x -= tmp * TIMOTHY_COMPLEX_PI;
	}
	else if (x < -100.0L)
	{
		long long tmp = static_cast<long long>((-TIMOTHY_COMPLEX_PI_2 - x) / TIMOTHY_COMPLEX_PI);
		flag = tmp % 2 ? -1 : 1;
		x += tmp * TIMOTHY_COMPLEX_PI;
	}
	for (; x > TIMOTHY_COMPLEX_PI_2; x -= TIMOTHY_COMPLEX_PI) flag = -flag;
	for (; x < -TIMOTHY_COMPLEX_PI_2; x += TIMOTHY_COMPLEX_PI) flag = -flag;
	if (x > TIMOTHY_COMPLEX_PI_4 + 1e-10L) return flag * sine(TIMOTHY_COMPLEX_PI_2 - x);
	if (x < -TIMOTHY_COMPLEX_PI_4 - 1e-10L) return flag * sine(TIMOTHY_COMPLEX_PI_2 + x);
	return flag * cosine(x);
}

long double re_calculate::tan(long double x)
{
	long double cosx = cos(x);
	if (re_calculate::abs(cosx) < 1e-12L) throw math_error();
	return sin(x) / cosx;
}

long double re_calculate::sind(long double x)
{
	return sin(x * TIMOTHY_COMPLEX_PI / 180.0L);
}

long double re_calculate::cosd(long double x)
{
	return cos(x * TIMOTHY_COMPLEX_PI / 180.0L);
}

long double re_calculate::tand(long double x)
{
	return tan(x * TIMOTHY_COMPLEX_PI / 180.0L);
}

long double re_calculate::atan(long double x)
{
	signed char flag = 1;
	if (x < 0.0L) { x = -x; flag = -1; }
	if (x > 1.0L) return flag * (TIMOTHY_COMPLEX_PI_2 - atan(1.0L / x));
	if (abs(x > 0.5L)) return flag * (TIMOTHY_COMPLEX_PI_4 - atan((1 - x) / (1 + x)));
	long double z = 1, s = 1, y = x * x;
	signed char flag1 = 1;
	long long n = 1;
	for (; z / n > 1e-25; s += (flag1 = -flag1) * (z *= y) / (n += 2));
	return flag * x * s;
}

long double re_calculate::acot(long double x)
{
	return TIMOTHY_COMPLEX_PI_2 - atan(x);
}

long double re_calculate::asin(long double x)
{
	if (x == 1.0L) return TIMOTHY_COMPLEX_PI_2;
	if (x == -1.0L) return -TIMOTHY_COMPLEX_PI_2;
	return atan(x / sqrt(1.0L - x * x));
}

long double re_calculate::acos(long double x)
{
	return TIMOTHY_COMPLEX_PI_2 - asin(x);
}

void set_complex_format(complex_format::format _complex_format_setting)
{
	if (_complex_format_setting != complex_format::def_format
		&& _complex_format_setting != complex_format::std_math_format
		&& _complex_format_setting != complex_format::engi_math_format
		&& _complex_format_setting != complex_format::modarg_math_format
		&& _complex_format_setting != complex_format::magpi_math_format)
		throw no_format();
	complex_format::_compl_format = _complex_format_setting;
}

__TIMOTHY_NAMESPACE_END
