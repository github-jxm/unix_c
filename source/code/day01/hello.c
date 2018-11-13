#include <stdio.h>
#include <stdlib.h>
#include "hello.h"
//#include "/home/tarena/uc/hello.h"
void abc(void)
{
		int i =0;
		i++;
}
int main()
{
		struct test test1;
		test1.a = 123;
		test1.b = 456;
		abc();
		printf("helloworld!\n");
		return 0;
}
