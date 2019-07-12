#include <fstream>
#include <memory>
#include <cstring>
#include <cerrno>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include "log.h"

Log::Log(const std::string& p_logger_name)
{
    if (opendir(LOG_PATH) == NULL) {        // 检查 LOG_PATH 所指的目录是否存在， 如果不存在则创建目录
        if (errno == ENOENT) {
            int ret = mkdir(LOG_PATH, S_IRUSR | S_IWUSR | S_IXUSR);     // 创建 LOG_PATH 所指的目录
            if (ret == -1) {
                fprintf(stderr, "Log:: Log mkdir calls failed: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Log:: opendir calls failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    log4cxx::PropertyConfigurator::configure(LOG_PROPERTY_PATH);            // 获取配置文件
    d_logger = log4cxx::Logger::getLogger(p_logger_name.c_str());           // 获取 logger
    d_logger_name = p_logger_name;
}

Log::~Log()
{

}

void
Log::log_msg(Log& p_log, int p_log_severity,int p_line_num, const char *p_file_name, const char *p_format, ...)
{
    char log_msg_buffer[LOG_MSG_BUFFER];
    memset(log_msg_buffer,'\0',sizeof(log_msg_buffer));

    // 在配置文件信息中加入使用文件名和所调用的行信息
    sprintf(log_msg_buffer, "[%s(%d)]: ", basename(p_file_name), p_line_num);
    std::string log_msg = std::string(log_msg_buffer);
    memset(log_msg_buffer,'\0',sizeof(log_msg_buffer));

    va_list arg_ptr;
    va_start(arg_ptr,p_format);

    vsprintf(log_msg_buffer, p_format, arg_ptr);
    log_msg = log_msg + log_msg_buffer;
    va_end(arg_ptr);

    switch(p_log_severity){
        case LOG_DEBUG:
            LOG4CXX_DEBUG(p_log.get_logger(), log_msg);
            break;
        case LOG_INFO :
            LOG4CXX_INFO(p_log.get_logger(), log_msg);
            break;
        case LOG_WARN :
            LOG4CXX_WARN(p_log.get_logger(), log_msg);
            break;
        case LOG_ERROR :
            LOG4CXX_ERROR(p_log.get_logger(), log_msg);
            break;
        case LOG_FATAL :
            LOG4CXX_FATAL(p_log.get_logger(), log_msg);
            break;
        default:
            break;
    }
}