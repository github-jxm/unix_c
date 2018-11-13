
#include <stdio.h>

#define R  8

int main()
{
		int x = 0;
		int y = 0;
		for(x=-R; x<=R; x++)
		{
				for(y=-R; y<=R; y++)
				{
						if(abs(x) + abs(y) < R)
						{
								printf("*");
						}
						else
						{
								printf(" ");
						}
				}
				printf("\n");
		}
}

