#ifndef  __CMD_LINE_PROC_H__
#define  __CMD_LINE_PROC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define    FLAG_OUTPUT_NO_PREFIX    0x1

struct work_params {
	int verbose;

	int arg_num;
	char operator[8];
	char operand1[128];
	char operand2[128];
	int output_base;
	uint32_t flags;
};


struct work_params *get_work_params(void);

void parse_cmd_line_args(int argc, char *argv[]);


#ifdef __cplusplus
}
#endif

#endif /* __CMD_LINE_PROC_H__ */

