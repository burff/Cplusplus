#ifndef LST_TIMER_H_
#define LST_TIMER_H_

#include <netinet/in.h>
#include <time.h>
#define BUFFER_SIZE 64
class Util_timer;

struct client_data
{
    sockaddr_in address;
    int sockfd;
    char buf[BUFFER_SIZE];
    Util_timer* timer;
};

class Util_timer
{
 public:
    Util_timer():prev_(NULL), next_(NULL){}
 public:
    time_t expire_;
    void (*cb_func)(client_data*);
    client_data* user_data_;
    Util_timer* prev_;
    Util_timer* next_;
};

class Sort_timer_lst
{
 public:
    Sort_timer_lst(): head(NULL), tail(NULL){}
    ~Sort_timer_lst();
    void add_timer(Util_timer* timer);
    void adjust_timer(Util_timer* timer);
    void del_timer(Util_timer* timer);
    void tick();
    
 private: 
    void add_timer(Util_timer* timer, Util_timer* lst_head);
    Util_timer* head;
    Util_timer* tail;   
};

#endif