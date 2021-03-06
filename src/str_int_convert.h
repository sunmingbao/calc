#ifndef  __STR_INT_CONVERT_H__
#define  __STR_INT_CONVERT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int check_operand(const char *str);
int str2int(const char *str, uint64_t *result, int *is_neg);
uint64_t str2decimal(const char *str);
void str2int_test(void);

#ifdef __cplusplus
}
#endif

#endif /* __STR_INT_CONVERT_H__ */

