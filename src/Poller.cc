#include "Poller.h"

namespace libnet
{

Poller::Poller(EventLoop *loop) :
    ownerLoop_(loop)
{
}

Poller::~Poller()
{
}

}
