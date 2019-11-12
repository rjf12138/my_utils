#ifndef __FILE_OPERATE_H__
#define __FILE_OPERATE_H__

#include "basic_header.h"

enum {
    FILE_SEEK_SET,  // 距离开始处
    FILE_SEEK_CUR,  // 距离当前位置
    FILE_SEEK_END,  // 距离文件结束
};

class FileOperate {
public:
    FileOperate(void);
    ~FileOperate(void);

    int open(const char *file_path);
    int fileinfo(struct stat &file_info);
    void print_errno(void);

    // 设置文件偏移
    off_t seek(off_t offset, int whence);
    off_t curr_pos(void);
    off_t goto_next_line(void);

    // 从当前位置读取任意数据
    ssize_t read(void *buf, size_t buf_size);
    // 从某一位置读取数据
    ssize_t read_from(void *buf, size_t buf_size, off_t pos, int whence);

    // 读取当前行字符串（读完后位置不变）
    ssize_t get_curr_line(string &line);
    // 读取指定行字符串（读完后位置不变）
    ssize_t get_spec_line(string &line, size_t line_num);
    // 读取下一行字符穿
    ssize_t get_next_line(string &line);

    // 写数据
    ssize_t write(const void *buf, size_t buf_size);
    // 从某一位置写数据
    ssize_t write_to(const void *buf, size_t buf_size ,off_t pos, int whence);

private:
private:
    int errno_;
    int fd_;
    bool file_open_flag_;
    unsigned max_lines_;
    struct stat file_info_;
};

#endif