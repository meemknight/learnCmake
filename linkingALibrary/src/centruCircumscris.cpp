#include <stdio.h>
#include <iostream>

using i64 = long long int;

inline float determinant(
	i64 x1, i64 y1, i64 z1,
	i64 x2, i64 y2, i64 z2,
	i64 x3, i64 y3, i64 z3
	)
{
	return (x1*y2*z3 + x2*y3*z1 + x3*z2*y1) - (z1*y2*x3+z2*y3*x1+x2*y1*z3);
};

template <typename T> int sign(T val)
{
	return (T(0) < val) - (val < T(0));
}

int input[200000];

int main()
{	
	std::ios_base::sync_with_stdio(false);

	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	int x3 = 0;
	int y3 = 0;

	scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);

	int n = 0;
	scanf("%d", &n);
	
	i64 xa2 = x1 * x1;
	i64 ya2 = y1 * y1;
	i64 xb2 = x2 * x2;
	i64 yb2 = y2 * y2;
	i64 xc2 = x3 * x3;
	i64 yc2 = y3 * y3;

	const char *rezText[] = {
		"OUTSIDE",
		"BOUNDARY",
		"INSIDE"
	};

	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &input[i*2 + 0], &input[i * 2 + 1]);
	}

	for (int i = 0; i < n; i++)
	{
		int x4 = input[i * 2 + 0], y4 = input[i * 2 + 1];
		
		i64 xd2 = x4 * x4;
		i64 yd2 = y4 * y4;
		i64 D = (xd2 + yd2);

		auto rez = determinant
		(
			x1 - x4, y1 - y4, (xa2 + ya2) - D,
			x2 - x4, y2 - y4, (xb2 + yb2) - D,
			x3 - x4, y3 - y4, (xc2 + yc2) - D
		);

		puts(rezText[sign(rez) + 1]);
	}

	return 0;
}