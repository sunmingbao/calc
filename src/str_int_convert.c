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

static int char_is_bin_digit(char c)
{
	return ((c>='0') && (c<='1'));
}

static int char_is_oct_digit(char c)
{
	return ((c>='0') && (c<='7'));
}

static int char_is_decimal_digit(char c)
{
	return ((c>='0') && (c<='9'));
}

static int char_is_hex_digit(char c)
{
	if ((c>='0') && (c<='9'))
		return 1;

	if ((c>='a') && (c<='f'))
		return 1;

	if ((c>='A') && (c<='F'))
		return 1;

	return 0;
}

static int char_is_digit_of_base(char c, int base)
{
	if (base==2) return char_is_bin_digit(c);
	if (base==8) return char_is_oct_digit(c);
	if (base==10) return char_is_decimal_digit(c);
	if (base==16) return char_is_hex_digit(c);


	return 0;
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

static int str2digits(const char *str, int str_len, uint8_t digits[], int base)
{
	int size = 0;
	int i;
	uint8_t digit;

	for (i=0; i<str_len; i++) {
		if (!char_is_digit_of_base(str[i],base))
			continue;

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

uint64_t str2decimal(const char *str)
{
	int str_len = strlen(str);
	uint8_t digits[str_len];
	int size = 0;
	int is_neg = (str[0]=='-'?1:0);
	uint64_t ret;

	size = str2digits(str, str_len, digits, 10);
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

	size = str2digits(str, str_len, digits, base);
	ret = str2uint_core(digits, size, base);

	return ret;
}

int every_char_in_range(const char *str, char min, char max)
{
	char c;
	while (c=(*str)) {
		if ((c<min) || (c>max))
			return 0;
		str++;
	}

	return 1;
}

int every_char_is_hex(const char *str)
{
	char c;
	while (c=(*str)) {

		if (char_is_hex_digit(c))
			goto NEXT_LOOP;

		return 0;
NEXT_LOOP:
		str++;
	}

	return 1;
}

static int get_base_sign(const char *str, int *is_neg)
{
	char c = str[0];
	const char *first_digit = str;

	if (is_neg)
		*is_neg = (c=='-')?1:0;

	/* decimal or exeptinal base */

	if (c!='0') {
		if ((c!='+')  && (c!='-') && ((c<'1') || (c>'9')))
			goto ERR_EXIT;

		if (c=='+'  || c=='-') 	first_digit+=1;
		if (!strlen(first_digit))
			goto ERR_EXIT;

		if (every_char_in_range(first_digit, '0', '9'))
			return 10;

		goto ERR_EXIT;
	}

	c = str[1];
	if (c==0) return 10;

	if (c=='x' || c=='X') {
		first_digit+=2;
		if (!strlen(first_digit))
			goto ERR_EXIT;

		if (every_char_is_hex(first_digit))
			return 16;

		goto ERR_EXIT;
	}

	if (c=='b' || c=='B') {
		first_digit+=2;
		TRACE_DBG("%s", first_digit);
		if (!strlen(first_digit))
			goto ERR_EXIT;

		if (every_char_in_range(first_digit, '0', '1'))
			return 2;

		goto ERR_EXIT;
	}

	first_digit+=1;
	if (!strlen(first_digit))
		goto ERR_EXIT;

	if (every_char_in_range(first_digit, '0', '7'))
		return 8;

ERR_EXIT:
	return -1;
}

int str2int(const char *str, uint64_t *result, int *is_neg)
{
	int base;

	base = get_base_sign(str, is_neg);
	TRACE_DBG("base=%d", base);
	if (base==10)
		*result = str2decimal(str);
	else
		*result = str2uint(str, base);
	return 0;
}

/**** test code ****/
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

