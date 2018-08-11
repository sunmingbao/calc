#ifndef  __CMD_LINE_PROC_H__
#define  __CMD_LINE_PROC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define    FLAG_OUTPUT_NO_PREFIX    0x1

struct work_params {
	const char *operator;
	const char *operand1;
	const char *operand2;
	int output_base;
	uint32_t flags;
};


struct work_params *get_work_params(void);

void parse_cmd_line_args(int argc, char *argv[]);


#ifdef __cplusplus
}
#endif

#endif /* __CMD_LINE_PROC_H__ */

