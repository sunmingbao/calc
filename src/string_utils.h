#ifndef  __STRING_UTILS_H__
#define  __STRING_UTILS_H__

#include <string.h>

int str_trim(char *output, char * input);
int str_trim_len(char *output, char * input, int len);
int str_trim_all_len(char *output, char * input, int len);
int str_trim_all(char *output, char * input);
int str_replace_substr(char *output, char *input, char *from, char *to);
void trim_new_line(char *str);

static inline void insert_char(char *str, char c, int idx, int len)
{
    memmove(str+idx+1, str+idx, len-idx);
	str[idx] = c;
	str[len+1] = 0;
}

static inline void delete_char(char *str, int idx, int len)
{
    memmove(str+idx, str+idx+1, len-idx-1);
	str[len-1] = 0;
}

#endif

