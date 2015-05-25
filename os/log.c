#include <string.h>

/**
 * 简单打印调试信息
 */
#define DEBUG_SWITCH        1
#ifdef    DEBUG_SWITCH
#define pr_debug(fmt,args...) printf(fmt, ##args)
#else
#define pr_debug(fmt,args...) /*do nothing */
#endif

/**
 * 错误信息打印
 * 自动打印发生错误时代码所在的位置
 */
#define     ERR_DEBUG_SWITCH        1
#ifdef    ERR_DEBUG_SWITCH
#define pr_err(fmt,args...) printf("\nFile:<%s> Fun:[%s] Line:%d\n "fmt, __FILE__, __FUNCTION__, __LINE__, ##args)
#else
#define pr_err(fmt,args...) /*do nothing */
#endif

/**
 * 断言
 * 对某种假设条件进行检查(若条件成立则无动作，否则报告错误信息)
 */
#define _EXAM_ASSERT_TEST_        1
#define _EXAM_ASSERT_EXIT_        1
#ifdef _EXAM_ASSERT_TEST_ // 若使用断言测试
void exam_assert(int condition, const char * file_name, const char *fun, unsigned int line_no, const char *fmt, ...)
{
    char sBuf[1024];
    va_list va;

    if (!condition)
    {
        bzero(sBuf, sizeof(sBuf));
        va_start(va, fmt);
        vsprintf(sBuf, fmt, va);

        printf("\n[EXAM]Assert failed: File:<%s> Fun:[%s] Line:%d\n %s", file_name, fun, line_no, sBuf);
#ifdef _EXAM_ASSERT_EXIT_
        abort();
#endif
    }
}

#define EXAM_ASSERT(condition, fmt, args...)    exam_assert(condition, __FILE__, __FUNCTION__, __LINE__,fmt, ##args)

#else // 若不使用断言测试
#define EXAM_ASSERT(condition, fmt, args...) NULL
#endif /* end of ASSERT */