#include <stdio.h>


int main(void)
{
	int a = 74835634;
	int b = 10;
	while (a != 0) {
		a /= b;
		printf("%d\n", a);
	}
	return 0;
}