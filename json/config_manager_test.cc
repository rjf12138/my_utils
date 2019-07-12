#include "config_manager.h"

int main(void) 
{
    ConfigManager l_json_read("./test_read.json");

    int l_int_value;
    double l_double_value;
    std::string l_string_value;
    bool l_bool_value;
    short l_short_value;

    std::cout << "int: " << l_json_read.get_integer_config(ConfigManager::R_INT) << std::endl;

    std::cout << "double: " << l_json_read.get_double_config(ConfigManager::R_DOUBLE) << std::endl;

    std::cout << "string: " << l_json_read.get_string_config(ConfigManager::R_STRING) << std::endl;

    std::cout << "bool_true: " << l_json_read.get_bool_config(ConfigManager::R_BOOL_TRUE) << std::endl;

    std::cout << "bool_false: " << l_json_read.get_bool_config(ConfigManager::R_BOOL_FALSE) << std::endl;

    std::cout << "short: " << l_json_read.get_short_config(ConfigManager::R_SHORT) << std::endl;

//    std::cout << "short: " << l_json_read.get_integer_config(ConfigManager::R_SHORT) << std::endl;        // 传入错误的参数

    return 0;
}