#include <algorithm>
#include "str_util.h"

void print_strings(const std::string p_prompt, std::vector<std::string> p_strings, bool p_is_print);

bool StrUtil_split_str_test(const std::string& p_test_str, const std::string& p_sperator, const std::vector<std::string>& p_right_result, bool p_is_print);
void split_str_test(void);

bool StrUtil_remove_str1_from_str2_test(const std::string& p_str1, const std::string& p_st2, const std::string& p_result);
void remove_str1_from_str2_test(void);

int main(void)
{
    remove_str1_from_str2_test();

    return 0;
}

void split_str_test(void)
{
    // 测试单个字符， 以 ' ' 空格作为分隔符, 出现次数 3 次
    // 出现位置： 第一个在字符串开头， 其余两个在中间
    std::cout << StrUtil_split_str_test(" hjkd &HJJ )jkl", " ", {"hjkd", "&HJJ", ")jkl"}, false) << std::endl;

    // 出现位置： 三个字符全在字符串的中间
    std::cout << StrUtil_split_str_test("h jkd &HJJ )jkl", " ", {"h", "jkd", "&HJJ", ")jkl"}, false) << std::endl;

    // 出现位置： 2个字符在字符串的中间, 一个在末尾
    std::cout << StrUtil_split_str_test("h jkd &HJJ)jkl ", " ", {"h", "jkd", "&HJJ)jkl"}, false) << std::endl;

    // 出现位置： 一个在中间，其余两个在字符串两边
    std::cout << StrUtil_split_str_test(" hjkd &HJJ)jkl ", " ", {"hjkd", "&HJJ)jkl"}, false) << std::endl;

    // 出现位置： 不存在分隔符
    std::cout << StrUtil_split_str_test("hjkd&HJJ)jkl", " ", {"hjkd&HJJ)jkl"}, false) << std::endl;

    // 出现位置： 只有分隔符
    std::cout << StrUtil_split_str_test("   ", " ", {}, false) << std::endl;

    // 测试多个字符， 以 "abc" 作为分隔符， 出现次数 3 次
    // 出现位置： 第一个在字符串开头， 其余两个在中间
    std::cout << StrUtil_split_str_test("abchjkdabc&HJJabc)jkl", "abc", {"hjkd", "&HJJ", ")jkl"}, false) << std::endl;

    // 出现位置： 三个字符全在字符串的中间
    std::cout << StrUtil_split_str_test("habcjkdabc&HJJabc)jkl", "abc", {"h", "jkd", "&HJJ", ")jkl"}, false) << std::endl;

    // 出现位置： 2个字符在字符串的中间, 一个在末尾
    std::cout << StrUtil_split_str_test("habcjkdabc&HJJ)jklabc", "abc", {"h", "jkd", "&HJJ)jkl"}, false) << std::endl;

    // 出现位置： 一个在中间，其余两个在字符串两边
    std::cout << StrUtil_split_str_test("abchjkdabc&HJJ)jklabc", "abc", {"hjkd", "&HJJ)jkl"}, false) << std::endl;

    // 出现位置： 不存在分隔符
    std::cout << StrUtil_split_str_test("hjkd&HJJ)jkl", "abc", {"hjkd&HJJ)jkl"}, false) << std::endl;

    // 出现位置： 只有分隔符
    std::cout << StrUtil_split_str_test("abcabcabc", "abc", {}, false) << std::endl;
}

bool StrUtil_split_str_test(const std::string& p_test_str, const std::string& p_sperator, const std::vector<std::string>& p_right_result, bool p_is_print)
{
    std::vector<std::string> l_ret_split_result = StrUtil::split_str(p_test_str, p_sperator);       // 对 p_test_str 按 p_sperator 进行分割

    print_strings("p_right_result", p_right_result, p_is_print);                                    // 打印正确结果和返回的结果
    print_strings("l_ret_split_result", l_ret_split_result, p_is_print);

    if (p_right_result.size() != l_ret_split_result.size()) {                                       // 测试长度是否相同
        std::cout << "The length of l_ret_split_result and p_right_result is different." << std::endl;
        return false;
    }

    for (auto t_ret_str : p_right_result) {                                                         // 测试 p_right_result 是否与 l_ret_split_result 是否相同
        auto t_search_ret = std::find(l_ret_split_result.begin(), l_ret_split_result.end(), t_ret_str);
        if (t_search_ret == l_ret_split_result.end()) {
            std::cout << "can't find "<< t_ret_str << "in p_right_reslult." << std::endl;
            return false;
        }
        l_ret_split_result.erase(t_search_ret);
    }
    return true;
}

bool StrUtil_remove_str1_from_str2_test(const std::string& p_str1, const std::string& p_str2, const std::string& p_result)
{
    if (StrUtil::remove_str1_from_str2(p_str1, p_str2).compare(p_result) == 0) {
        return true;
    }
    return false;
}

void remove_str1_from_str2_test(void)
{
    // 测试： 去除 /home/ruanjian/pdf 中的 pdf
    std::cout << StrUtil_remove_str1_from_str2_test("/home/ruanjian/pdf","pdf", "/home/ruanjian/") << std::endl;
}

void print_strings(const std::string p_prompt, std::vector<std::string> p_strings, bool p_is_print)
{
    if (p_is_print) {
        std::cout << p_prompt << " size: " << p_strings.size() << std::endl;
        for (auto t_str : p_strings) {
            std::cout << t_str << std::endl;
        }
    } else {
        return ;
    }
    std::cout << std::endl;
}