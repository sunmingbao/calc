#include <config.h>
#include <stdio.h>
#include "trace_dbg.h"
int main(int argc, char *argv[])
{
	TRACE_DBG("hello, this is %s.\n", PACKAGE_STRING);
	print_mem("hello, welcome!", 15);
	return 0;
}
