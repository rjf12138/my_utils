#include "config_manager.h"

ConfigManager::ConfigManager(const std::string &p_json_path)
{
    d_json_file_path = p_json_path;
    d_json_file.open(d_json_file_path);
    if(d_json_file.good()){
        d_json_file >> d_js;
    }else{
        throw std::runtime_error("Unable to open json path");
    }
}

ConfigManager::~ConfigManager()
{
    d_json_file.close();
}

short
ConfigManager::get_short_config(const short p_config_key)
{
    short l_value;
    switch (p_config_key) {
        case R_SHORT:
            l_value = d_js["type_short"];
            break;
        default:
            l_value = d_js["unknown type"];
            break;
    }
    return l_value;
}

int
ConfigManager::get_integer_config(const short p_config_key)
{
    int l_value;
    switch (p_config_key) {
        case R_INT:
            l_value = d_js["type_int"];
            break;
        default:
            l_value = d_js["unknown type"];
            break;
    }
    return l_value;
}

double
ConfigManager::get_double_config(const short p_config_key)
{
    double l_value;
    switch (p_config_key) {
        case R_DOUBLE:
            l_value = d_js["type_double"];
            break;
        default:
            l_value = d_js["unknown type"];
            break;
    }
    return l_value;
}

bool
ConfigManager::get_bool_config(const short p_config_key)
{
    bool l_value;
    switch (p_config_key) {
        case R_BOOL_FALSE:
            l_value = d_js["type_bool_false"];
            break;
        case R_BOOL_TRUE:
            l_value = d_js["type_bool_true"];
            break;
        default:
            l_value = d_js["unknown type"];
            break;
    }
}

std::string 
ConfigManager::get_string_config(const short p_config_key)
{
    std::string l_value;
    switch (p_config_key) {
        case R_STRING:
            l_value = d_js["type_string"];
            break;
        default:
            l_value = d_js["unknown type"];
            break;
    }
    return l_value;
}
