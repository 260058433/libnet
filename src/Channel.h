#ifndef CHANNEL_H
#define CHANNEL_H

#include <cstdint>
#include <sys/epoll.h>

namespace libnet
{

class EventLoop;

class Channel {
public:
    typedef void (*EventHandler)(void);

    Channel(EventLoop *loop, int fd);
    ~Channel();

    Channel(const Channel &) = delete;
    Channel &operator=(const Channel &) = delete;

    void handleEvent();

    EventLoop *loop()
    { return loop_; }

    int fd() const
    { return fd_; }

    uint32_t events() const
    { return events_; }

    void setRevents(uint32_t revent)
    { revents_ = revent;}

    int index() const
    { return index_; }

    void setIndex(int index)
    { index_ = index;}

    void setReadHandler(const EventHandler &eh)
    { readHandler_ = eh; }
    void setWriteHandler(const EventHandler &eh)
    { writeHandler_ = eh; }
    void setErrorHandler(const EventHandler &eh)
    { errorHandler_ = eh; }

    void start();
    void enableReading()
    { events_ |= EPOLLIN; update(); }
    void disableReading()
    { events_ &= ~EPOLLIN; update(); }
    void enableWriting()
    { events_ |= EPOLLOUT; update(); }
    void disableWriting()
    { events_ &= ~EPOLLOUT; update(); }

private:
    void update();

    EventLoop *loop_;
    const int fd_;
    uint32_t events_;
    uint32_t revents_;
    int index_;
    EventHandler readHandler_;
    EventHandler writeHandler_;
    EventHandler errorHandler_;
};
}

#endif
