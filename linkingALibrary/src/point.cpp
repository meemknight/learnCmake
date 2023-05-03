#include <stdio.h>
#include <vector>
#include <utility>
#include <cmath>


inline float inverseSqrt(float x)
{

	return 1.f / std::sqrt(x);
}

struct vec2
{
	float x, y;
};

inline vec2 normalize(vec2 v)
{
	float magnitude = inverseSqrt(v.x * v.x + v.y * v.y);
	return {v.x * magnitude, v.y * magnitude};
}

inline vec2 operator-(vec2 a, vec2 b)
{
	return {a.x - b.x, a.y - b.y};
}

inline vec2 operator+(vec2 a, vec2 b)
{
	return {a.x + b.x, a.y + b.y};
}

inline vec2 operator-(vec2 a)
{
	return {-a.x, -a.y};
}

inline bool operator==(vec2 a, vec2 b) { return a.x == b.x && a.y == b.y; }

inline float dot(vec2 a, vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

struct Line
{
	vec2 point1 = {};
	vec2 point2 = {};

	Line() = default;
	Line(vec2 p1, vec2 p2):point1(p1), point2(p2) {}
};

enum Rezult
{
	NoIntersect = 0,
	Intersect,
	InvalidIntersect,
	Edge,
};

bool aabb(vec2 p1, vec2 p2, vec2 point)
{
	float minX = 0;
	float maxX = 0;
	if (p1.x < p2.x)
	{
		minX = p1.x;
		maxX = p2.x;
	}
	else
	{
		minX = p2.x;
		maxX = p1.x;
	}

	float minY = 0;
	float maxY = 0;
	if (p1.y < p2.y)
	{
		minY = p1.y;
		maxY = p2.y;
	}
	else
	{
		minY = p2.y;
		maxY = p1.y;
	}

	if (
		point.x >= minX && point.x <= maxX &&
		point.y >= minY && point.y <= maxY
		)
	{
		return true;
	}
	else
	{
		return false;
	}

}

int intersect2Lines(Line l1, Line l2)
{
	vec2 d1 = l1.point2 - l1.point1;
	vec2 d2 = l2.point2 - l2.point1;

	vec2 p1 = l1.point1;
	vec2 p2 = l2.point1;

	if (l1.point1 == l2.point1
		|| l1.point2 == l2.point2
		|| l1.point1 == l2.point2
		|| l1.point2 == l2.point1
		)
	{
		return InvalidIntersect;
	}

	float a = d1.x;
	float b = p1.x;
	float c = d2.x;
	float d = p2.x;

	float e = d1.y;
	float f = p1.y;
	float g = d2.y;
	float h = p2.y;

	float det = a * (-g) + (c * e);

	if (det == 0)
	{
		//liniile sunt paralele
		float d = dot(normalize(d1), normalize(p1 - p2));
		if (d == 1 || d == -1)
		{
			//liniile sunt coliniare
			if (aabb(l1.point1, l1.point2, l2.point1) || aabb(l1.point1, l1.point2, l2.point2))
			{
				return InvalidIntersect;
			}
			else
			{
				return NoIntersect;
			}
		}
		else
		{
			//linii paralele
			return NoIntersect;
		}
	}
	else
	{

		float s1 = (-g * (d - b) + c * (h - f)) / det;
		float s2 = (-e * (d - b) + a * (h - f)) / det;

		if (s1 == 1.f)
		{
			return Edge;
		}if (s1 == 0.f)
		{
			return InvalidIntersect;
		}
		else if (s2 == 1.f || s2 == 0.f)
		{
			return InvalidIntersect;
		}
		else if (aabb({0,0}, {1,1}, {s1,s2}))
		{
			return Intersect;
		}
		else
		{
			return NoIntersect;
		}
	}

}


int main()
{

	int count = 0;
	scanf("%d", &count);
	std::vector<vec2> poligon;
	poligon.reserve(count);
	for (int i = 0; i < count; i++)
	{
		float x = 0, y = 0;
		scanf("%f %f", &x, &y);
		poligon.push_back({x,y});
	}

	float minX = poligon[0].x;
	float minY = poligon[0].y;
	float maxX = poligon[0].x;
	float maxY = poligon[0].y;

	for (auto p : poligon)
	{
		if (p.x < minX) { minX = p.x; }
		if (p.y < minY) { minY = p.y; }
		if (p.x > maxX) { maxX = p.x; }
		if (p.y > maxY) { maxY = p.y; }
	}


	int m = 0; 
	scanf("%d", &m);

	for (int i = 0; i < m; i++)
	{
		float x = 0, y = 0;
		scanf("%f %f", &x, &y);
		const vec2 Q{x, y};

		float deltaX = 10;
		float deltaY = 10;

		//early aabb rejection

		if (!aabb({minX, minY}, {maxX, maxY}, Q))
		{
			printf("OUTSIDE\n");
		}else
		{
			while (true)
			{
				vec2 M{minX - deltaX, minY - deltaY};
				Line MQ = {M, Q};

				int intersectCount = 0;
				bool edge = 0;
				bool invalid = 0;
				for (int i = 0; i < poligon.size(); i++)
				{
					vec2 p1 = poligon[i % poligon.size()];
					vec2 p2 = poligon[(i + 1) % poligon.size()];

					if (Q == p1 || Q == p2)
					{
						edge = 1;
						break;
					}

					int intersect = intersect2Lines(MQ, {p1, p2});
					if (intersect == NoIntersect)
					{

					}
					else if (intersect == Intersect)
					{
						intersectCount++;
					}
					else if (intersect == Edge)
					{
						edge = 1;
						break;
					}
					else if (intersect == InvalidIntersect)
					{
						deltaX += 7;
						invalid = 1;
						break;
					}

				}

				if (invalid)
				{
					continue;
				}
				else
				{
					if (edge)
					{
						printf("BOUNDARY\n");
					}
					else if (intersectCount % 2 == 0)
					{
						printf("OUTSIDE\n");
					}
					else
					{
						printf("INSIDE\n");
					}

					break;
				}
			}
		};


	}


	return 0;

}