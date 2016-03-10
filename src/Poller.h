#ifndef POLLER_H
#define POLLER_H

#include <vector>

namespace libnet
{

class EventLoop;
class Channel;

class Poller
{
public:
    Poller(EventLoop *loop);
    virtual ~Poller();

    virtual void poll(int timeoutMs, std::vector<Channel *> &channels) = 0;

    virtual void addChannel(Channel *channel) = 0;

    virtual void updateChannel(Channel *channel) = 0;

    virtual void removeChannel(Channel *channel) = 0;

private:
    EventLoop *ownerLoop_;
};

};

#endif
