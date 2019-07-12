#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include <string>
#include <memory>
#include <cstdarg>

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include <log4cxx/propertyconfigurator.h>

#define LOG_PROPERTY_PATH       "./log_property"        // log 配置文件的目录
#define LOG_PATH                "./log"                 // log 文件输出目录
#define LOG_MSG_BUFFER          256                     // log 消息最大长度

enum log_serverity {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
    LOG_CONSOLE
};


class Log{
public:
    static void log_msg(Log& p_log, int p_log_severity,int p_line_num, const char *p_file_name, const char *p_format, ...); // 打印日志消息

    // Log 日志构造函数
    Log(const std::string& p_logger);
    // 返回一个 logger
    log4cxx::LoggerPtr get_logger(void) const {return d_logger;}
    // 返回 logger name
    std::string get_logger_name(void) const {return d_logger_name;}
    ~Log();
private:
    Log() = default;
private:
    log4cxx::LoggerPtr d_logger;
    std::string d_logger_name;
};

#define LOG_DEBUG(p_log, ...)      Log::log_msg(p_log, LOG_DEBUG, __LINE__, __FILE__, __VA_ARGS__)
#define LOG_INFO(p_log, ...)       Log::log_msg(p_log, LOG_INFO, __LINE__, __FILE__,  __VA_ARGS__)
#define LOG_WARN(p_log, ...)       Log::log_msg(p_log, LOG_WARN, __LINE__, __FILE__, __VA_ARGS__)
#define LOG_ERROR(p_log, ...)      Log::log_msg(p_log, LOG_ERROR, __LINE__, __FILE__, __VA_ARGS__)
#define LOG_FATAL(p_log, ...)      Log::log_msg(p_log, LOG_FATAL, __LINE__, __FILE__, __VA_ARGS__)

#endif