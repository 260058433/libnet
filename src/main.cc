#include "EventLoop.h"
#include "Channel.h"
#include "Poller.h"

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <sys/epoll.h>

using namespace libnet;
using namespace std;

EventLoop *gloop;

void handler()
{
    char buf[128];
    while (read(STDIN_FILENO, buf, 128) >= 0)
        ;
    write(STDOUT_FILENO, buf, strlen(buf));
    gloop->quit();
}

int main()
{
    EventLoop loop;

    gloop = &loop;

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flags);

    Channel channel(&loop, STDIN_FILENO);
    channel.setReadHandler(handler);
    channel.start();
    channel.enableReading();

    loop.loop();
}
