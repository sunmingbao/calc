#include <assert.h>
#include <string.h>
#include "trace_dbg.h"
#include "str_int_convert.h"


static uint64_t str2uint_core(uint8_t digits[], int size, uint8_t base)
{
	uint64_t ret = 0;
	int i;

	for (i=0; i<size; i++) {
		ret *= base;
		ret += digits[i];
	}

	return ret;

}

#define INVALID_DIG_VALUE    (255)
static uint8_t digit_char_to_u8(const char c)
{
	int ret = INVALID_DIG_VALUE;

	if (c>='0' && c<='9') {
		ret = c - '0';
		goto EXIT;
	}

	if (c>='a' && c<='f') {
		ret = c - 'a' + 10;
		goto EXIT;
	}

	if (c>='A' && c<='F') {
		ret = c - 'A' + 10;
		goto EXIT;
	}
EXIT:
	return (uint8_t)ret;
}

static int str2digits(const char *str, int str_len, uint8_t digits[])
{
	int size = 0;
	int i;
	uint8_t digit;

	for (i=0; i<str_len; i++) {
		digit = digit_char_to_u8(str[i]);
		if (digit != INVALID_DIG_VALUE) {
			digits[size] = digit;
			size++;
		}

	}

	return size;
}

static uint64_t neg_value(uint64_t orig)
{
	return (~orig) + 1;
}

static uint64_t str2decimal(const char *str)
{
	int str_len = strlen(str);
	uint8_t digits[str_len];
	int size = 0;
	int is_neg = (str[0]=='-'?1:0);
	uint64_t ret;

	size = str2digits(str, str_len, digits);
	ret = str2uint_core(digits, size, 10);

	if (is_neg)
		ret = neg_value(ret);

	return ret;

}

static uint64_t str2uint(const char *str, int base)
{
	int str_len = strlen(str);
	uint8_t digits[str_len];
	int size = 0;
	uint64_t ret;

	size = str2digits(str, str_len, digits);
	ret = str2uint_core(digits, size, base);

	return ret;
}

static void test_str2decimal(void)
{
	assert(str2decimal("1234")==1234);
	assert((int64_t)str2decimal("-1234")==-1234);
}

static void test_str2uint(void)
{
	assert(str2uint("1011", 2)==11);
	assert(str2uint("11", 8)==011);
	assert(str2uint("11", 8)==9);
	assert(str2uint("001F", 16)==31);
	assert(str2uint("1234", 10)==1234);
}
static void test_str2uint_core(void)
{
	uint8_t digits_bin[] = {1,0,1,1};
	uint8_t digits_oct[] = {1,4,4};
	uint8_t digits_decimal[] = {1,4,4};
	uint8_t digits_hex[] = {1,0,4};

	assert(11==str2uint_core(digits_bin, 4, 2));
	assert(100==str2uint_core(digits_oct, 3, 8));
	assert(144==str2uint_core(digits_decimal, 3, 10));
	assert(260==str2uint_core(digits_hex, 3, 16));
}

void str2int_test(void)
{
	test_str2uint_core();
	test_str2decimal();
	test_str2uint();
}

int str2int(const char *input, uint64_t *result)
{
	return 0;
}
