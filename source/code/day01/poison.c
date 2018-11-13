
#include <stdio.h>
#pragma GCC poison goto

int main()
{
		goto failed;
		printf("helloworld\n");
		return 0;
failed:
		printf("aaaaa\n");
		return -1;
}


