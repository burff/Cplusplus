#include "sort_timer_list.h"
#include <cstddef>
#include <stdio.h>

Sort_timer_lst::~Sort_timer_lst()
{
    Util_timer* tmp = head;
    while(tmp)
    {
        head = tmp->next_;
        delete tmp;
        tmp = head;
    }
}

void Sort_timer_lst::add_timer(Util_timer* timer)
{
    if(!timer)
    {
        return;
    }
    if(!head)
    {
        head = tail = timer;
        return;
    }

    if(timer->expire_ < head->expire_)
    {
        timer->next_ = head;
        head->prev_ = timer;
        head = timer;
        return;
    }
    add_timer(timer, head);
}

void Sort_timer_lst::adjust_timer(Util_timer* timer)
{
    if(!timer)
    {
        return;
    }
    Util_timer* tmp = timer->next_;
    if(!tmp || (timer->expire_))
    {
        return;
    }
    if(timer == head)
    {
        head = head->next_;
        head->prev_ = NULL;
        timer->next_ = NULL;
    }
    else
    {
        timer->prev_->next_ = timer->next_;
        timer->next_->prev_ = timer->prev_;
        add_timer(timer, timer->next_);
    }
}

void Sort_timer_lst::del_timer(Util_timer* timer)
{
    if(!timer)
    {
        return;
    }
    if(timer == head && timer == tail)
    {
        delete timer;
        head = NULL;
        tail = NULL;
        return;
    }

    if(timer == head) // timer == head && timer!= tail
    {
        head = head->next_;
        head->prev_ = NULL;
        delete timer;
        return;
    }

    if(timer == tail)
    {
        tail = tail->prev_;
        tail->next_ = NULL;
        delete timer;
        return;
    }

    timer->prev_->next_ = timer->next_;
    timer->next_->prev_ = timer->prev_;
    delete timer;
}

void Sort_timer_lst::tick()
{
    if(!head)
    {
        return;
    }
    printf("timer tick\n");
    time_t cur = time(NULL);
    Util_timer* tmp = head;
    while(tmp)
    {
        if(cur < tmp->expire_)
        {
            break;
        }
        head = tmp->next_;
        if(head)
        {
            head->prev_ = NULL;
        }
        delete tmp;
        tmp = head;
    }
}

void Sort_timer_lst::add_timer(Util_timer* timer, Util_timer* lst_head)
{
    Util_timer* tmp_prev = lst_head;
    Util_timer* tmp = tmp_prev->next_;
    while(tmp)
    {
        if(timer->expire_ < tmp->expire_)
        {
            tmp->prev_->next_ = timer;
            timer->prev_ = tmp->prev_;
            timer->next_ = tmp;
            tmp->prev_ = timer;
            break;
        }
        tmp_prev = tmp;
        tmp = tmp->next_;
    }

    if(!tmp)
    {
        tmp_prev ->next_ = timer;
        timer->next_ = NULL;
        timer->prev_ = tmp_prev;
        tail = timer;//记录结尾
    }
}