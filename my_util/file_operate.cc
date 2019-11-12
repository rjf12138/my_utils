#include "file_operate.h"

FileOperate::FileOperate(void) { }
FileOperate::~FileOperate(void)
{
    close(fd_);
}

int FileOperate::fileinfo(struct stat &file_info)
{
    int ret = fstat(fd_, &file_info);
    if (ret == -1) {
        errno_ = errno_;
    }
    return ret;
}

void FileOperate::print_errno(void)
{
    fprintf(stderr, "%s\n", );
}