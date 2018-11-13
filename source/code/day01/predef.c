
#include <stdio.h>

void abc(void)
{
		printf("__FUNCTION__:%s\n", __FUNCTION__);
}

int main()
{
		printf("__FUNCTION__:%s\n", __FUNCTION__);
		printf("__FILE__:%s\n", __FILE__);
		printf("__LINE__:%d\n", __LINE__);
		abc();
}


