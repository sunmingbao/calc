#include <stdint.h>

#include "trace_dbg.h"
#include "calc_expr.h"
#include "cmd_line_proc.h"
#include "str_int_convert.h"

struct operand {
	union {
		uint64_t u64;
		int64_t  s64;
	};
};

void calc_expr(void)
{
	struct work_params * the_work_params = get_work_params();

	TRACE_DBG("==arg_num %d", the_work_params->arg_num);
str2int_test();
	if (the_work_params->arg_num==2) {

	} else {

	}


}
