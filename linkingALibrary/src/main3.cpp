#include <iostream>
#include <vector>

//for _mm256_fmadd_ps
#ifdef _MSC_VER
	#include <intrin.h>
#else
	#include <x86intrin.h>
#endif

//corecrt_math.h
#define _HUGE_ENUF  1e+300  // _HUGE_ENUF*_HUGE_ENUF must overflow
#define INFINITY   ((float)(_HUGE_ENUF * _HUGE_ENUF))

//returns (a*b) + c
//inline float fma(float a, float b, float c)
//{
//	__m256 _a = {a};
//	__m256 _b = {b};
//	__m256 _c = {c};
//
//	__m256 rez = _mm256_fmadd_ps(_a, _b, _c);
//	return ((float*)&rez)[0];
//}

inline float determinant(float x1, float y1, float x2, float y2, float x3, float y3)
{
	//fma();
	//float rez = x1 * y2 + x2 * y3 + x3 * y1 - x3 * y2 - x1 * y3 - y1 * x2;
	float firstHalf = 0;
	float secondHalf = 0;
	{
		float first = x1 * y2;
		float second = fma(x2, y3, first);
		firstHalf = fma(x3, y1, second);
	}
	
	//split it into 2 unrelated parts to paralelize on the cpu
	{
		float first = x3 * y2;
		float second = fma(x1, y3, first);
		secondHalf = fma(y1, x2, second);
	}

	return firstHalf - secondHalf;
}

struct vec2
{
	float x, y;
};


int main()
{
	std::vector<vec2> poligon;

	int n;
	std::cin >> n;

	float minX = -INFINITY;
	float maxX = INFINITY;
	float minY = -INFINITY;
	float maxY = INFINITY;

	for (int i = 0; i < n; i++)
	{
		float x, y;
		std::cin >> x >> y;
		poligon.push_back({x,y});

		minX = std::min(minX, x);
		minY = std::min(minY, y);
		maxX = std::max(maxX, x);
		maxY = std::max(maxY, y);
	}

	int m;
	std::cin >> m;

	for (int intrebare = 0; intrebare < m; intrebare++)
	{
		float x, y;
		std::cin >> x >> y;

		//early aabb rejection
		if (
			((x > maxX) || (x < minX)) &&
			((y > maxY) || (y < minY))
			)
		{
			std::cout << "OUTSIDE\n";
			continue;
		}

		int countNeg = 0;
		int countPoz = 0;
		int countEgal = 0;

		const int size = poligon.size();

		for (int i = 0; i < size; i++)
		{
			auto next = [&](int p) { return (p + 1) % size; };
			
			auto p2 = poligon[next(i)];
			auto p3 = poligon[next(next(i))];
		
			float value = determinant(x, y, p2.x, p2.y, p3.x, p3.y);
		
			if (value < 0) { countNeg++; }
			if (value > 0) { countPoz++; }
			if (value == 0) { countEgal++; }
		}

		if (countNeg != 0 && countPoz != 0)
		{
			std::cout << "OUTSIDE\n";
		}
		else if (countEgal)
		{
			bool edge = false;
			for (int i = 0; i < size; i++)
			{
				auto next = [&](int p) { return (p + 1) % size; };

				auto p2 = poligon[next(i)];
				auto p3 = poligon[next(next(i))];

				float value = determinant(x, y, p2.x, p2.y, p3.x, p3.y);

				if (value == 0)
				{
					//also check if point is on the line by checking aabb
					float minX = std::min(p2.x, p3.x);
					float maxX = std::max(p2.x, p3.x);
					float minY = std::min(p2.y, p3.y);
					float maxY = std::max(p2.y, p3.y);
					
					if (x >= minX && x <= maxX && y >= minY && y <= maxY)
					{
						edge = true;
						break;
					}
			
					//we don't alter the prevSemn
					continue;
				}
			}

			if (edge)
			{
				std::cout << "BOUNDARY\n";
			}
			else
			{
				std::cout << "INSIDE\n";
			}
		}
		else
		{
			std::cout << "INSIDE\n";
		}

		//bool prevSemn = 0;
		//bool inside = true;
		//bool edge = false;
		//bool semnFound = false;
		//for (int i = 0; i < poligon.size(); i++)
		//{
		//	auto next = [&](int p) { return (p + 1) % poligon.size(); };
		//	
		//	auto p2 = poligon[next(i)];
		//	auto p3 = poligon[next(next(i))];
		//
		//	float value = determinant(x, y, p2.x, p2.y, p3.x, p3.y);
		//
		//	if (value == 0)
		//	{
		//		//also check if point is on the line by checking aabb
		//		float minX = std::min(p2.x, p3.x);
		//		float maxX = std::max(p2.x, p3.x);
		//		float minY = std::min(p2.y, p3.y);
		//		float maxY = std::max(p2.y, p3.y);
		//		
		//		if (x >= minX && x <= maxX && y >= minY && y <= maxY)
		//		{
		//			edge = true;
		//			break;
		//		}
		//
		//		//we don't alter the prevSemn
		//		continue;
		//	}
		//
		//	bool semn = value > 0;
		//
		//	if (semnFound)
		//	{
		//		if (semn != prevSemn)
		//		{
		//			inside = false;
		//			break;
		//		}
		//	}
		//	semnFound = true;
		//	prevSemn = semn;
		//}
		//
		//if (edge)
		//{
		//	std::cout << "BOUNDARY\n";
		//}
		//else if (inside)
		//{
		//	std::cout << "INSIDE\n";
		//}
		//else
		//{
		//	std::cout << "OUTSIDE\n";
		//}

	}


	
	return 0;
}