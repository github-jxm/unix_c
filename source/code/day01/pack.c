
#include <stdio.h>
#pragma pack(1)

struct s1
{
		char a;
		short e;
		int b;
		char c;
		double d;
};
int main()
{
		printf("struct s1 size = %d\n", 
						sizeof(struct s1));
}




