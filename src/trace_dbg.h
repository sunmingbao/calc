#ifndef  __TRACE_DBG_H__
#define  __TRACE_DBG_H__

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

#define    PURE_FILE_NAME(file_path) ({const char *ret = strrchr(file_path, '/'); \
                                  ret = ((ret==NULL)?file_path:ret+1); \
                                  ret;})

void verbose_print(const char *fmt, ...);

/*
 * for debugging, pass CFLAGS=-D__DEBUG_PRINT to configure
 */

//#define    __DEBUG_PRINT

#ifdef __DEBUG_PRINT
#define    TRACE_DBG(fmt, args...) \
    do \
    { \
        fprintf(stdout, "DBG:%s(%d)-%s:\n"fmt"\n", PURE_FILE_NAME(__FILE__),__LINE__,__FUNCTION__,##args); \
        fflush(stdout); \
    } while (0)

void print_mem(void *start_addr, uint32_t length);
	
#else

#define    TRACE_DBG(fmt, args...) /* */

static inline void print_mem(void *start_addr, uint32_t length)
{
    return;
}

#endif

#define    TRACE_ERR(fmt, args...) \
    do \
    { \
        fprintf(stderr, "error:%s(%d)-%s:\n"fmt": %s\n", PURE_FILE_NAME(__FILE__),__LINE__,__FUNCTION__,##args, strerror(errno)); \
        fflush(stderr); \
    } while (0)

#define    TRACE_PARAM_WRONG(fmt, args...) \
    do \
    { \
        fprintf(stderr, "param wrong:\n"fmt"\n", ##args); \
        fflush(stderr); \
    } while (0)

#define    TRACE_ERR_QUIT(fmt, args...) \
    do \
    { \
        TRACE_ERR(fmt, ##args); \
        exit(1); \
    } while (0)

#define    TRACE_PARAM_WRONG_QUIT(fmt, args...) \
    do \
    { \
        TRACE_PARAM_WRONG(fmt, ##args); \
        exit(1); \
    } while (0)


#ifdef __cplusplus
}
#endif

#endif /* __TRACE_DBG_H__ */

