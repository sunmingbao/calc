#include <stdint.h>
#include <assert.h>

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

uint64_t calc_expr_binary_core(const char *operator, uint64_t operand1, uint64_t operand2)
{
	uint64_t ret;

	if (strcmp(operator, "+")==0) {
		ret = operand1+operand2;
		goto EXIT;
	}


	if (strcmp(operator, "-")==0) {
		ret = operand1-operand2;
		goto EXIT;
	}

	if (strcmp(operator, "*")==0) {
		ret = operand1*operand2;
		goto EXIT;
	}


	if (strcmp(operator, "/")==0) {
		if (0==operand2)
			TRACE_PARAM_WRONG_QUIT("operand1 divided by 0");
		ret = operand1/operand2;
		goto EXIT;
	}

	if (strcmp(operator, "==")==0) {
		ret = (operand1==operand2);
		goto EXIT;
	}

	if (strcmp(operator, "!=")==0) {
		ret = (operand1!=operand2);
		goto EXIT;
	}

	if (strcmp(operator, ">")==0) {
		ret = (operand1>operand2);
		goto EXIT;
	}

	if (strcmp(operator, ">=")==0) {
		ret = (operand1>=operand2);
		goto EXIT;
	}

	if (strcmp(operator, "<")==0) {
		ret = (operand1<operand2);
		goto EXIT;
	}

	if (strcmp(operator, "<=")==0) {
		ret = (operand1<=operand2);
		goto EXIT;
	}

	if (strcmp(operator, "&")==0) {
		ret = (operand1&operand2);
		goto EXIT;
	}

	if (strcmp(operator, "|")==0) {
		ret = (operand1|operand2);
		goto EXIT;
	}

	if (strcmp(operator, "^")==0) {
		ret = (operand1^operand2);
		goto EXIT;
	}

	if (strcmp(operator, "<<")==0) {
		ret = (operand1<<operand2);
		goto EXIT;
	}

	if (strcmp(operator, ">>")==0) {
		ret = (operand1>>operand2);
		goto EXIT;
	}
EXIT:
	return ret;
}

uint64_t calc_expr_unary_core(const char *operator, uint64_t operand1)
{
	uint64_t ret;


	if (strcmp(operator, "++")==0) {
		ret = ++operand1;
		goto EXIT;
	}


	if (strcmp(operator, "--")==0) {
		ret = --operand1;
		goto EXIT;
	}

	if (strcmp(operator, "~")==0) {
		ret = ~operand1;
		goto EXIT;
	}


EXIT:
	return ret;
}


uint64_t calc_expr_binary(const char *operator, const char *operand1, const char *operand2)
{
	uint64_t result, operand1_uint, operand2_uint;

	str2int(operand1, &operand1_uint, NULL);
	str2int(operand2, &operand2_uint, NULL);

	return calc_expr_binary_core(operator, operand1_uint, operand2_uint);

}

uint64_t calc_expr_unary(const char *operator, const char *operand1)
{
	uint64_t result, operand1_uint;

	str2int(operand1, &operand1_uint, NULL);

	return calc_expr_unary_core(operator, operand1_uint);

}

void test_calc_expr_binary_core(void)
{
	assert(calc_expr_binary_core("+", 1, 2)==3);
	assert(calc_expr_binary_core("-", 5, 1)==4);
	assert(calc_expr_binary_core("*", 4, 2)==8);
	assert(calc_expr_binary_core("/", 100, 2)==50);
	assert(calc_expr_binary_core("==", 100, 2)==0);
	assert(calc_expr_binary_core("!=", 100, 2)==1);
	assert(calc_expr_binary_core("==", 100, 100)==1);
	assert(calc_expr_binary_core("!=", 100, 100)==0);
}

void test_calc_expr_binary(void)
{
	assert(calc_expr_binary("+",  "1", "2")==3);
	assert(calc_expr_binary("-",  "5", "1")==4);
	assert(calc_expr_binary("*",  "4", "2")==8);
	assert(calc_expr_binary("/",  "100", "2")==50);
	assert(calc_expr_binary("==", "100", "2")==0);
	assert(calc_expr_binary("!=", "100", "2")==1);
	assert(calc_expr_binary("==", "100", "100")==1);
	assert(calc_expr_binary("!=", "100", "100")==0);
}


void test_calc_expr_unary(void)
{
	assert(calc_expr_unary("++",  "2")==3);
	assert(calc_expr_unary("--",  "2")==1);
	assert(calc_expr_unary("~",  "-1")==0);
}

void output_result(uint64_t result)
{
	printf("%llu\n", result);
}

void calc_expr(void)
{
	struct work_params * the_work_params = get_work_params();
	uint64_t result;

	test_calc_expr_binary_core();
	test_calc_expr_binary();
	test_calc_expr_unary();

	if (the_work_params->arg_num==2) {
		verbose_print("unary calculate\n");
		verbose_print("operator is %s\n", the_work_params->operator);
		verbose_print("operand1 = %s\n", the_work_params->operand1);
		result = calc_expr_unary(the_work_params->operator, the_work_params->operand1);

	} else {
		verbose_print("binary calculate\n");
		verbose_print("operator is %s\n", the_work_params->operator);
		verbose_print("operand1 = %s\n", the_work_params->operand1);
		verbose_print("operand2 = %s\n", the_work_params->operand2);
		result = calc_expr_binary(the_work_params->operator, the_work_params->operand1, the_work_params->operand2);

	}

	output_result(result);
}
