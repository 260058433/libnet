#ifndef EPOLLPOLLER_H
#define EPOLLPOLLER_H

#include "Poller.h"

#include <vector>
#include <sys/epoll.h>

namespace libnet
{

class EventLoop;
    
class EpollPoller : public Poller
{
public:
    EpollPoller(EventLoop *loop);
    virtual ~EpollPoller();

    virtual void poll(int timeoutMS, std::vector<Channel *> &channels);

    virtual void addChannel(Channel *channel);

    virtual void updateChannel(Channel *channel);

    virtual void removeChannel(Channel *channel);

private:
    void update(int operation, Channel *channel);

    static const int initEventsSize = 16;
    int epollfd_;
    std::vector<struct epoll_event> events_;
};

}

#endif
