#include "Event.h"
#include <sys/epoll.h>
#include <strings.h>

Event::Event() {
    ev = new epoll_event();
    bzero(&ev, sizeof(ev));
}

void Event::add(EventType et) {
    switch (et) {
        case EventType::EPOLLIN : ev->events |= EPOLLIN; break;
        case EventType::EPOLLOUT : ev->events |= EPOLLOUT; break;
        case EventType::EPOLLRDHUP: ev->events |= EPOLLRDHUP; break;
        case EventType::EPOLLPRI: ev->events |= EPOLLPRI; break;
        case EventType::EPOLLERR: ev->events |= EPOLLERR; break;
        case EventType::EPOLLHUP: ev->events |= EPOLLHUP; break;
        case EventType::EPOLLET: ev->events |= EPOLLET; break;
        case EventType::EPOLLONESHOT: ev->events |= EPOLLONESHOT; break;
    }
}
