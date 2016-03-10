#include "Channel.h"
#include "EventLoop.h"

#include <sys/epoll.h>

namespace libnet
{

Channel::Channel(EventLoop *loop, int fd) :
    loop_(loop),
    fd_(fd),
    events_(0),
    revents_(0),
    readHandler_(nullptr),
    writeHandler_(nullptr),
    errorHandler_(nullptr)
{
}

Channel::~Channel()
{
}

void Channel::handleEvent()
{
    if (revents_ & EPOLLERR)
        if (errorHandler_)
            errorHandler_();

    if (revents_ & EPOLLIN)
        if (readHandler_)
            readHandler_();

    if (revents_ & EPOLLOUT)
        if (writeHandler_)
            writeHandler_();
}

void Channel::update()
{
    loop_->updateChannel(this);
}

void Channel::start()
{
    loop_->addChannel(this);
}

}
