#include "EventLoop.h"
#include "Channel.h"
#include "Poller.h"
#include "EpollPoller.h"

namespace libnet
{

EventLoop::EventLoop() :
    quit_(false),
    activeChannels_(),
    poller_(new EpollPoller(this))
{
}

EventLoop::~EventLoop()
{
}

const int kPollTimeMs = 1000;
void EventLoop::loop()
{
    while (!quit_)
    {
        activeChannels_.clear();
        poller_->poll(kPollTimeMs, activeChannels_);
        for (auto p = activeChannels_.begin(); p != activeChannels_.end(); ++p)
            (*p)->handleEvent();
    }
}

void EventLoop::updateChannel(Channel *channel)
{
    poller_->updateChannel(channel);
}

void EventLoop::addChannel(Channel *channel)
{
    poller_->addChannel(channel);
}

void EventLoop::quit()
{
    quit_ = true;
}

}
