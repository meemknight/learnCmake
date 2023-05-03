#include <limits.h>
#include <stdio.h>

#ifdef _MSC_VER
#pragma warning(disable : 6031)
#endif

int max(int a, int b)
{
	if (a >= b) { return a; }
	else { return b; }
}

int min(int a, int b)
{
	if (a <= b) { return a; }
	else { return b; }
}

int main(void)
{

	int topLine = INT_MAX;
	int bottomLine = INT_MIN;
	int rightLine = INT_MAX;
	int leftLine = INT_MIN;
	
	int n = 0;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{

		int a=0, b=0, c=0;

		scanf("%d %d %d", &a, &b, &c);

		if (b == 0) //vertical
		{
			if (a > 0)
			{
				//ax - c <= 0
				//x <= c/a
				leftLine = max(leftLine, c / a);
			}
			else
			{
				//ax - c <= 0
				//x >= c/a
				rightLine = min(rightLine, c / -a);
			}
		}
		else
		{
			if (b > 0)
			{
				bottomLine = max(bottomLine, c / b);
			}
			else
			{
				topLine = min(topLine, c / -b);
			}
		}
	}
	
	if (bottomLine >= topLine && leftLine >= rightLine)
	{
		printf("BOUNDED");
	}
	else if (
			(bottomLine >= topLine && (leftLine == INT_MIN || rightLine == INT_MAX))
		||
			(leftLine >= rightLine && (bottomLine == INT_MIN || topLine == INT_MAX))
		|| ((bottomLine == INT_MIN || topLine == INT_MAX) && (leftLine == INT_MIN || rightLine == INT_MAX))
		)
	{
		printf("UNBOUNDED");
	}
	else
	{
		printf("VOID");
	}

	return 0;
}