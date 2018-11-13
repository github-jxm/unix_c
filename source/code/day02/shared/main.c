
#include "calc.h"
#include "show.h"

int test;

int main()
{
		int res = add(30, 20);
		show(30, '+', 20, res);
		res = sub(30, 20);
fail:
		show(30, '+', 20, res);
}

