#ifndef __STR_UTIL_H__
#define __STR_UTIL_H__

#include <iostream>
#include <string>
#include <vector>

class StrUtil {
public:
    static std::vector<std::string> split_str(const std::string& p_str, const std::string& p_separator);
    static std::string remove_str1_from_str2(const std::string& p_str1, const std::string& p_str2);
};

#endif