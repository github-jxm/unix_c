
#include <stdio.h>
#include <string.h>

int main()
{

		extern char **environ;
		char **p = environ;
#if 0
		while(*p != NULL)
		{
			printf("%s\n", *p);	
      p++;
			/* 第一 p++ (0x100 下次变为0x104)
				 第二 *p(取地址0x100中的内容) 
				 (*p)++;//实验效果不对 段错误
				 *(p++)//实验效果对，多做了无用工
			 */
			//*p++; //实验效果对，多做了无用工
			//**p++;//实验效果对，多做了两次无用工
	}
#endif
#if 1
		char buf[100] = {0};
		p = environ;
		while(*p)
		{
				if(strncmp(*p , "LANG=", 5) == 0)
				{
						//重点
						strcpy(buf, *p+5);
						break;
				}
				//重点
				p++;
		}
		printf("buf = %s\n", buf);
#endif
}

