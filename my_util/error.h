#ifndef __ERROR_H__
#define __ERROR_H__

#include "basic_header.h"

class Error {
public:
    void print_error_msg(std::string function_name, int error_num) {
        printf("%s-%d: %s\n", function_name.c_str(), error_num, strerror(error_num));
    }
private:
    int errno_;
    std::string function_name_;
    std::string error_msg;
};

#endif