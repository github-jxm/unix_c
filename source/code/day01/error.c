
#include <stdio.h>
#if(VERSION < 3)
	#error "版本过低"
#elif (VERSION > 3)
	#warning "版本过高"
#endif
int main()
{
		int n = 1;
		printf("版本=%d\n", VERSION);
}

