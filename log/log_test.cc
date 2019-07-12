#include <pthread.h>

#include "log.h"

#define __MULTI_THREAD__

void Log_single_thread_write_test(Log& p_log);
void* thread_func(void* p_arg);

int main(void)
{
#ifdef __SINGLE_THREAD__
    Log log_test_1("log_1");    // log_1 是在配置文件中
    Log log_test_2("log_2");
    Log log_test_3("log_3");

    Log_single_thread_write_test(log_test_1);
    Log_single_thread_write_test(log_test_2);
    Log_single_thread_write_test(log_test_3);
#elif defined __MULTI_THREAD__
    pthread_t l_thread[3];
    Log l_log("log_1");

    for (int i = 0; i < 3; ++i) {
        pthread_create(&l_thread[i], NULL, thread_func, (void*)&l_log);
    }

    for (int i = 0; i < 3; ++i) {
        pthread_join(l_thread[i], NULL);
    }
#endif

    return 0;
}

void Log_single_thread_write_test(Log& p_log)
{
    LOG_DEBUG(p_log, "%s_LOG_DEBUG", p_log.get_logger_name().c_str());
    LOG_INFO(p_log, "%s_LOG_INFO", p_log.get_logger_name().c_str());
    LOG_WARN(p_log, "%s_LOG_WARN", p_log.get_logger_name().c_str());
    LOG_ERROR(p_log, "%s_LOG_ERROR", p_log.get_logger_name().c_str());
    LOG_FATAL(p_log, "%s_LOG_FATAL", p_log.get_logger_name().c_str());
}

void* thread_func(void* p_arg)
{
    Log* l_log = (Log*)p_arg;

    for (int i = 0; i < 30; ++i) {
        Log_single_thread_write_test(*l_log);
    }
}