#include <config.h>
#include <stdio.h>

#include "trace_dbg.h"
#include "cmd_line_proc.h"
#include "calc_expr.h"


int main(int argc, char *argv[])
{
	parse_cmd_line_args(argc, argv);
	calc_expr();

	return 0;
}
