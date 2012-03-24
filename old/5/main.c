#include <stdio.h>

extern void mult(double, int);

extern void print(double f)
{
	printf("%lf", f);
}


int main()
{
	mult(123.321, 5);
	return 0;
}
