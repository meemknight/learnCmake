#include <stdio.h>
#include <istream>
#include <iostream>
#include <vector>
#include <sstream>
//for _mm256_fmadd_ps
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

using i64 = long long int;

struct Point
{
	i64 x;
	i64 y;
};

Point operator-(Point a, Point b)
{
	return {a.x - b.x, a.y - b.y};
}

static inline i64 cross(const Point a, const Point b)
{
	return a.x * b.y - b.x * a.y;
}


inline i64 determinant(i64 x1, i64 y1, i64 x2, i64 y2, i64 x3, i64 y3)
{
	Point a{x1, y1};
	Point b{x2, y2};
	Point c{x3, y3};

	return cross({c - a}, {c - b});
	
}

inline float determinant2(float x1, float y1, float x2, float y2, float x3, float y3)
{
	float rez = x1 * y2 + x2 * y3 + x3 * y1
		- x3 * y2 - x1 * y3 - y1 * x2;
	return rez;
}


template <typename T> int sgn(T val)
{
	return (T(0) < val) - (val < T(0));
}

static void fast_io() { std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr); }

int main()
{
	fast_io();
	int n;
	scanf("%d", &n);

	std::vector<i64> data;
	data.resize(n*6);

	for (int i = 0; i < n*6; i++)
		scanf("%ld", &data[i]);

	const char *res[] = {
		"RIGHT",
		"TOUCH",
		"LEFT",
	};

	for (int i = 0; i < n; i++)
	{
		i64 rez = determinant(data[(i) * 6 + 0], data[(i) * 6 + 1], data[(i) * 6 + 2], data[(i) * 6 + 3], data[(i) * 6 + 4], data[(i) * 6 + 5]);
		puts(res[sgn(rez)+1]);
	}
	
	
	return 0;
}
