#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "Poller.h"

#include <vector>
#include <memory>

namespace libnet
{

class Channel;
class Poller;

class EventLoop
{
public:
    EventLoop();
    ~EventLoop();

    EventLoop(const EventLoop &) = delete;
    EventLoop &operator=(const EventLoop &) = delete;

    void loop();

    void updateChannel(Channel *channel);

    void addChannel(Channel *channel);

    void quit();

private:
    bool quit_;
    std::vector<Channel *> activeChannels_;
    std::unique_ptr<Poller> poller_;
};

}

#endif
