#include "trace_dbg.h"
#include "calc_expr.h"
#include "cmd_line_proc.h"


void calc_expr(void)
{
	struct work_params * the_work_params = get_work_params();

	TRACE_DBG("==arg_num %d", the_work_params->arg_num);

}
