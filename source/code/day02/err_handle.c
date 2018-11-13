
#include <stdio.h>
#include <string.h>
#include <time.h>

int random(void)
{
		srand(time(0));
		int res = rand() % 10;
		if(res == 5)
		{
				return -1;
		}
		return res;
}

char *strcopy(char *dest, char *src, int len)
{
		if(dest == NULL || src == NULL)
		{
				return NULL;
		}
		if((strlen(src)+1) > len)
		{
				return NULL;
		}
		char *tmp = dest;
		while((*tmp++ = *src++) != 0);
		return dest;
}
int judge(char *str)
{
		if(strcmp(str, "error") == 0)
		{
				return -1;
		}
		return 0;
}
void average(int a, int b, int *av)
{
		*av = (a+b) /2;
}
int main(void)
{
	int ret = random();
	if(ret != -1)
	{
			printf("random() return val = %d\n", ret);
	}
	char *str1 = "helloworld!";
	char buf[20] = {0};
	if(strcopy(buf, str1, sizeof(buf)))
	{
			printf("buf=%s\n", buf);
	}
	else
	{
			printf("strcopy failed!\n");
	}
	if(judge(str1) == 0)
	{
			printf("str1 != error\n");
	}

	average(20, 30, &ret);
	printf("ret = %d\n", ret);

}

