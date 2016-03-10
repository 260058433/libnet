#ifndef EVENT_H
#define EVENT_H

enum class EventType {
    EPOLLIN = 1,
    EPOLLOUT = 2,
    EPOLLRDHUP = 4,
    EPOLLPRI = 8,
    EPOLLERR = 16,
    EPOLLHUP = 32,
    EPOLLET = 64,
    EPOLLONESHOT = 128,
};

struct epoll_event;

class Event {
public:
    Event();

    void add(EventType);

private:
    epoll_event *ev;
};

#endif
