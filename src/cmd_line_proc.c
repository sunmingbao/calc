#include <config.h>

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

#include "trace_dbg.h"
#include "cmd_line_proc.h"
#include "string_utils.h"


static struct work_params the_work_params = {
	.output_base = 10,
};

struct work_params *get_work_params(void)
{
	return  &the_work_params;
}

static void show_version(void)
{
	printf("%s version %s\n"
		"(Author's Email : %s)\n"
		, PACKAGE_NAME, PACKAGE_VERSION
		, PACKAGE_BUGREPORT);

}


#define    OPT_HELP       (1000)
#define    OPT_VERSION    (1001)
#define    OPT_VERBOSE    (1002)

#define    OPT_OUTPUT_BASE_2    (1101)
#define    OPT_OUTPUT_BASE_8    (1102)
#define    OPT_OUTPUT_BASE_16   (1103)

#define    OPT_OUTPUT_NO_PREFIX    (1201)
#define    OPT_OUTPUT_US_DECIMAL   (1202)


static struct option cmd_line_options[] =
    {
        {"help",       no_argument, NULL, OPT_HELP},
        {"version",    no_argument, NULL, OPT_VERSION},
        {"verbose",    no_argument, NULL, OPT_VERBOSE},


        {"output-base-2",    no_argument, NULL, OPT_OUTPUT_BASE_2},
        {"output-base-8",    no_argument, NULL, OPT_OUTPUT_BASE_8},
        {"output-base-16",   no_argument, NULL, OPT_OUTPUT_BASE_16},

        {"output-base-bin",    no_argument, NULL, OPT_OUTPUT_BASE_2},
        {"output-base-oct",    no_argument, NULL, OPT_OUTPUT_BASE_8},
        {"output-base-hex",    no_argument, NULL, OPT_OUTPUT_BASE_16},


        {"output-no-prefix",           no_argument, NULL, OPT_OUTPUT_NO_PREFIX},
        {"output-unsigned-decimal",    no_argument, NULL, OPT_OUTPUT_US_DECIMAL},
        {NULL},
    };


static void print_opt_list(const char *description[])
{
	struct option *cur_opt = cmd_line_options;
	int idx = 0;
	while (cur_opt->name) {
		printf("--%s: %s argument\n"
			"    %s\n"
			, cur_opt->name, (cur_opt->has_arg==no_argument)?"no":"has"
			, description ? description[idx] : "");
		cur_opt++;
		idx++;
	}
}

static void show_usage(const char *exe_file_name)
{
	printf("%s  [options]  OPu  operand1\n", exe_file_name);
	printf("%s  [options]  operand1  OPb  operand2\n", exe_file_name);

	printf("[options]\n");
	print_opt_list(NULL);

}

void parse_cmd_line_args(int argc, char *argv[])
{
	int opt;

	int orig_optind = optind;
	int new_optind;
	int args_left;

	while ((opt = getopt_long(argc, argv, "vHh", cmd_line_options, NULL)) != -1){
		switch (opt)  {
			case 'v':
			case OPT_VERSION:
				show_version();
				exit(0);



			case OPT_VERBOSE:
				the_work_params.verbose = 1;
				TRACE_DBG("verbose enabled");
				break;


			case OPT_OUTPUT_BASE_2:
				the_work_params.output_base = 2;
				break;

			case OPT_OUTPUT_BASE_8:
				the_work_params.output_base = 8;
				break;

			case OPT_OUTPUT_BASE_16:
				the_work_params.output_base = 16;
				break;

			case OPT_OUTPUT_US_DECIMAL:
				the_work_params.output_base = 10;
				the_work_params.flags |= FLAG_OUTPUT_UNSIGNED_DECIMAL;
				break;

			case OPT_OUTPUT_NO_PREFIX:
				the_work_params.flags |= FLAG_OUTPUT_NO_PREFIX;
				break;

			case 'h':
			case 'H':
			case OPT_HELP:
			default: /* '?' */

				show_usage(PURE_FILE_NAME(argv[0]));
				exit(0);


		}
	}

	new_optind = optind;
	args_left = argc - new_optind;

	printf("optind %d %d\n", orig_optind, new_optind);
           if (new_optind < argc) {
		int optind_tmp = new_optind;
               printf("non-option ARGV-elements: \n");
               while (optind_tmp < argc)
                   printf("%s \n", argv[optind_tmp++]);

           }

	if (args_left<2 || args_left>3) {
		show_usage(PURE_FILE_NAME(argv[0]));
		exit(0);
	}

	if (args_left==2) {
		the_work_params.arg_num = 2;
		str_trim_all(the_work_params.operator, argv[new_optind++]);
		str_trim_all(the_work_params.operand1, argv[new_optind++]);

	} else {
		the_work_params.arg_num = 3;
		str_trim_all(the_work_params.operand1, argv[new_optind++]);
		str_trim_all(the_work_params.operator, argv[new_optind++]);
		str_trim_all(the_work_params.operand2, argv[new_optind++]);

	}

}
