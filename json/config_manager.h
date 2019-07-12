#ifndef __SERVER_JSON__
#define __SERVER_JSON__

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

class ConfigManager{
public:
    enum d_read_config {
        R_STRING = 0,
        R_INT,
        R_SHORT,
        R_DOUBLE,
        R_BOOL_TRUE,
        R_BOOL_FALSE,
    };

    ConfigManager(const std::string &p_json_path); // 参数: p_json_path: 要打开 json 文件的路径

    short       get_short_config(const short p_config_key);
    int         get_integer_config(const short p_config_key);
    double      get_double_config(const short p_config_key);
    bool        get_bool_config(const short p_config_key);
    std::string get_string_config(const short p_config_key);

    ~ConfigManager();
private:
    ConfigManager() = default;
private:
    std::fstream    d_json_file;
    std::string     d_json_file_path;
    nlohmann::json  d_js;
};

#endif