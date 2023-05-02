#include <stdio.h>

int main()
{
	int a = 5;
	char b = 1;
	char c = 99;
	while(b!=0)
	{
		
		b=b<<1;
		printf("%c : %d\n",c,b);
		printf("c : %d (decimal)\n",c);
	}

	return 0;
}
