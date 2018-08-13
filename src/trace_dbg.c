#include <stdarg.h>

#include "trace_dbg.h"
#include "cmd_line_proc.h"

#ifdef __DEBUG_PRINT
void print_mem(void *start_addr, uint32_t length)
{
    char str_addr[32];
    char str_data[64];
    char str_readable[32];
    unsigned char *cur_pos = start_addr;
    int i;

    while (length >= 16)
    {
        sprintf(str_addr, "%-16lx", (unsigned long)(void *)cur_pos);
        for (i = 0; i < 16; i++)
        {
            sprintf(str_data + i*3, "%02hhx ", cur_pos[i]);
            if (cur_pos[i] > 31 &&  cur_pos[i] < 127)
            sprintf(str_readable + i, "%c", (char)(cur_pos[i]));
            else
            sprintf(str_readable + i, "%c", '.');
        }
        length -= 16;
        cur_pos += 16;
        printf("%s: %s: %s\n", str_addr, str_data, str_readable);
		fflush(stdout);
    }

    if (length > 0)
    {
        sprintf(str_addr, "%-16lx", (unsigned long)(void *)cur_pos);
        for (i = 0; i < length; i++)
        {
            sprintf(str_data + i*3, "%02hhx ", cur_pos[i]);
            if (cur_pos[i] > 31 &&  cur_pos[i] < 127)
            sprintf(str_readable + i, "%c", (char)(cur_pos[i]));
            else
            sprintf(str_readable + i, "%c", '.');
        }
        for (i = length; i < 16; i++)
        {
            sprintf(str_data + i*3, "%s", "   ");
            sprintf(str_readable + i, "%c", ' ');
        }
        printf("%s: %s: %s\n", str_addr, str_data, str_readable);
		fflush(stdout);
    }


}
#endif

void verbose_print(const char *fmt, ...)
{
	int len;
	char buf[512];
	va_list ap;

	static struct work_params * the_work_params;

	if (!the_work_params)  
		the_work_params	= get_work_params();

	if (!the_work_params->verbose)
		return;

	va_start(ap, fmt);
	len = vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	fprintf(stdout, "%s", buf);
	fflush(stdout);
}

