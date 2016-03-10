#include "EpollPoller.h"
#include "Channel.h"

#include <stdexcept>
#include <unistd.h>
#include <errno.h>
#include <strings.h>

namespace libnet {

EpollPoller::EpollPoller(EventLoop *loop) :
    Poller(loop), 
    epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
    events_(initEventsSize)
{
    if (epollfd_ == -1)
        throw std::runtime_error("epoll_create1");
}

EpollPoller::~EpollPoller()
{
    ::close(epollfd_);
}

void EpollPoller::poll(int timeoutMs, std::vector<Channel *> &channels)
{
    int numEvents = ::epoll_wait(epollfd_, &events_.front(), static_cast<int>(events_.size()), timeoutMs);
    if (numEvents > 0)
    {
        for (int i = 0; i < numEvents; ++i)
        {
            Channel *channel = static_cast<Channel *>(events_[i].data.ptr);
            channel->setRevents(events_[i].events);
            channels.push_back(channel);
        }

        if (numEvents == static_cast<int>(events_.size()))
            events_.resize(events_.size() * 2);
    }
    else if (numEvents == -1 && errno != EINTR)
    {
        throw std::runtime_error("epoll_wait");
    }
}

void EpollPoller::addChannel(Channel *channel)
{
    update(EPOLL_CTL_ADD, channel);
}

void EpollPoller::updateChannel(Channel *channel)
{
    update(EPOLL_CTL_MOD, channel);
}

void EpollPoller::removeChannel(Channel *channel)
{
    update(EPOLL_CTL_DEL, channel);
}

void EpollPoller::update(int operation, Channel *channel)
{
    struct epoll_event event;
    bzero(&event, sizeof(event));
    event.events = channel->events();
    event.data.ptr = channel;
    if (::epoll_ctl(epollfd_, operation, channel->fd(), &event) == -1)
        throw std::runtime_error("epoll_ctl");
}

}
