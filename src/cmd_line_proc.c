#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

#include "trace_dbg.h"
#include "cmd_line_proc.h"



static struct work_params the_work_params = {

};

struct work_params *get_work_params(void)
{
	return  &the_work_params;
}


void parse_cmd_line_args(int argc, char *argv[])
{
	TRACE_DBG("==");

}
