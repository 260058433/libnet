#ifndef EPOLL_H
#define EPOLL_H

class Event;

class Epoll {
public:
    Epoll();

    void init();

    void addEvent(Event &event);

    void deleteEvent(Event &event);

    void modifyEvent(Event &event);

private:
    int fd;
};

#endif
