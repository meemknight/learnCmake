#include <stdio.h>
#include <iostream>
#include <vector>
#include <limits.h>

struct Point
{
	int x;
	int y;
};

int main()
{
	std::ios_base::sync_with_stdio(false);

	std::vector<Point> points;
	int n = 0;
	scanf("%d", &n);
	
	points.resize(n);

	int minY = INT_MAX;
	int minX = INT_MAX;
	int maxY = INT_MIN;
	int maxX = INT_MIN;

	int minYinddex = 0;
	int minXinddex = 0;
	int maxYinddex = 0;
	int maxXinddex = 0;

	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &points[i].x, &points[i].y);

		if (points[i].x > maxX)
		{
			maxX = points[i].x;
			maxXinddex = i;
		}else
		if (points[i].x < minX)
		{
			minX = points[i].x;
			minXinddex = i;
		}

		if (points[i].y > maxY)
		{
			maxY = points[i].y;
			maxYinddex = i;
		}
		else
		if (points[i].y < minY)
		{
			minY = points[i].y;
			minYinddex = i;
		}
	}

	auto next = [&](int i)
	{
		i++;
		i = i % points.size();
		return i;
	};

	auto prev = [&](int i)
	{
		i--;
		if (i < 0)
		{
			i = points.size() - 1;
		}
		return i;
	};

	bool monotonX = true;
	for (int i = next(maxXinddex); i != minXinddex; i = next(i))
	{
		if (points[prev(i)].x < points[i].x)
		{
			monotonX = false;
			break;
		}
	}
	if (monotonX)
	{
		for (int i = prev(maxXinddex); i != minXinddex; i = prev(i))
		{
			if (points[next(i)].x < points[i].x)
			{
				monotonX = false;
				break;
			}
		}
	}

	bool monotonY = true;
	for (int i = next(maxYinddex); i != minYinddex; i = next(i))
	{
		if (points[prev(i)].y < points[i].y)
		{
			monotonY = false;
			break;
		}
	}
	if (monotonY)
	{
		for (int i = prev(maxYinddex); i != minYinddex; i = prev(i))
		{
			if (points[next(i)].y < points[i].y)
			{
				monotonY = false;
				break;
			}
		}
	}

	if (monotonX) { puts("YES"); } else { puts("NO"); }
	if (monotonY) { puts("YES"); } else { puts("NO"); }

	return 0;
}