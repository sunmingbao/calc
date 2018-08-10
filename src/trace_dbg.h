/* 
 * �����Ϊ��ѡ���Դ�����
 * ������İ�Ȩ(����Դ�뼰�����Ʒ����汾)��һ�й������С�
 * ����������ʹ�á������������
 * ��Ҳ�������κ���ʽ���κ�Ŀ��ʹ�ñ����(����Դ�뼰�����Ʒ����汾)���������κΰ�Ȩ���ơ�
 * =====================
 * ����: ������
 * ����: sunmingbao@126.com
 */

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

#define    TRACE_DBG(fmt, args...) \
    do \
    { \
        printf("DBG:%s(%d)-%s:\n"fmt"\n", PURE_FILE_NAME(__FILE__),__LINE__,__FUNCTION__,##args); \
        fflush(stdout); \
    } while (0)



#define    TRACE_ERR(fmt, args...) \
    do \
    { \
        printf("error:%s(%d)-%s:\n"fmt": %s\n", PURE_FILE_NAME(__FILE__),__LINE__,__FUNCTION__,##args, strerror(errno)); \
        fflush(stderr); \
    } while (0)

#define    TRACE_PARAM_WRONG(fmt, args...) \
    do \
    { \
        printf("param wrong:\n"fmt"\n", ##args); \
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

void print_mem(void *start_addr, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif /* __TRACE_H__ */

