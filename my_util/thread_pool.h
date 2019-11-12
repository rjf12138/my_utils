#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "basic_header.h"

enum thread_state{
    THREAD_BUSY,
    THREAD_IDLE,
    THREAD_EXIT,
};
struct thread_attr {
    pthread_t thread_id;
    thread_state state;
    static void* (*func)(void*);
};
class ResoManager {
public:
    ResoManager(std::vector<AvInfo> avinfos): avinfo_(avinfos)
    {
        pthread_mutex_init(&mutex_, NULL);
    }
    ~ResoManager(){
        pthread_mutex_destroy(&mutex_);
    }
    int get_next_info(AvInfo &next)
    {
        if (count_ == avinfo_.size())
            return -1;
        pthread_mutex_lock(&mutex_);
        next = avinfo_[count_];
        count_++;
        pthread_mutex_unlock(&mutex_);
    }
    std::vector<AvInfo> avinfo_;
    int count_ = 0;
    pthread_mutex_t mutex_;
};
ResoManager *res_manager_;

class MutilThread {
public:
    MutilThread(std::vector<AvInfo> avinfos)
    {
        res_manager_ = new ResoManager(avinfos);
    }
    ~MutilThread()
    {
        delete res_manager_;
    }
    int create_threads(int thread_num)
    {
        for (int i = 0; i < thread_num; ++i) {
            thread_attr tmp;
            int erro = pthread_create(&tmp.thread_id, NULL, MutilThread::func, NULL);
            threads_.push_back(tmp);
        }
    }
    int wait()
    {
        for (int i = 0; i < threads_.size(); ++i)
            pthread_join(threads_[i].thread_id, NULL);
    }
    static void* func(void*)
    {
        bool exit_ = false;
        AvInfo tmp;
        while(!exit_)
        {
            if (res_manager_->get_next_info(tmp) == -1)
                exit_ = true;
        
        char buf[512];
        for (int j = 0;j < tmp.image_path.size(); ++j){
            memset(buf, 0, 512);
            snprintf(buf, 512, "curl -v \"%s\" -o %s%s%d", tmp.image_path[j].c_str(), picture.c_str(), tmp.info_index.c_str(), j);
      //       std::cout << buf << std::endl;
           system(buf);
        }
        std::string torrent_cmd("curl -v \"" + web_addr + tmp.torrent_path + "\" -o " + torrent + tmp.info_index);
    //    std::cout << torrent_cmd << std::endl;
        system(torrent_cmd.c_str());
        }
    }
//    int handle_task(void);
private:
    std::vector<thread_attr> threads_;
};

#endif