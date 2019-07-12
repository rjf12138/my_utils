#include "str_util.h"

std::vector<std::string> 
StrUtil::split_str(const std::string& p_str, const std::string& p_separator)
{
    std::vector<std::string> l_split_strs;
    std::string l_store_str(p_str);

    std::string::size_type l_pos;
    uint32_t l_next_search_start_pos = 0;
    while ((l_pos = l_store_str.find(p_separator)) != std::string::npos) {      // 在 l_store_str 中找 p_separator 首次出现的位置
        std::string t_str = std::string(l_store_str, 0, l_pos);                 // 获取 l_store_str 开始位置到 p_separator 首次出现中间的字符串
        if (t_str.size() > 0) {                                                 // 排除 p_separator 出现在 l_store_str 开始位置的情况
            l_split_strs.push_back(t_str);
        }
        l_next_search_start_pos = l_pos + p_separator.size();
        // 去除已经获取的中间字符串和上次查找的 p_separator
        if (l_next_search_start_pos < l_store_str.size()) {
            l_store_str = std::string(l_store_str, l_next_search_start_pos, l_store_str.size() - l_next_search_start_pos);
        } else {
            // 当 l_next_search_start_pos 大于 l_store_str 的长度时， 说明 l_store_str 中已经没有可以用的字符串了，所以将它设为空， 防止触发之后的赋值
            l_store_str = "";
            break;
        }
    }

    if (l_store_str.size() > 0) {   // 将最后剩余的字符串放入返回结果
        l_split_strs.push_back(l_store_str);
    }

    return l_split_strs;
}

std::string 
StrUtil::remove_str1_from_str2(const std::string& p_str1, const std::string& p_str2)
{
    auto l_pos = p_str1.find(p_str2);
    if (l_pos == std::string::npos) {
        throw std::runtime_error("Can't find " + p_str2 + " in " + p_str1);
    }

    return std::string(p_str1, 0, l_pos);
}