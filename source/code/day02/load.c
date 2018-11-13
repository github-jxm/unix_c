
#include <stdio.h>
#include <dlfcn.h>
typedef int (*PFUNC_CALC) (int, int);
typedef void (*PFUNC_SHOW)(int, char, int, int);
int main()
{
		/*显示将libmy.so放入内存*/
		void *handle = dlopen("shared/libmy.so", RTLD_NOW);

		PFUNC_CALC func_add = (PFUNC_CALC)dlsym(handle, "add");
		PFUNC_SHOW func_show = (PFUNC_SHOW)dlsym(handle,"show");
		int res = func_add(30, 20);
		func_show(30, '+', 20, res);

		dlclose(handle);
 

}


