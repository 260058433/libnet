#include "TcpConnection.h"
#include "Channel.h"

#include <unistd.h>

namespace libnet
{

TcpConnection::TcpConnection(EventLoop *loop, int sockfd) :
    loop_(loop),
    channel_(new Channel(loop, sockfd))
{
    channel_->start();
    channel_->setReadHandler(std::bind(&TcpConnection::handleRead, this));
    channel_->enableReading();
}


void TcpConnection::handleRead()
{
    char buf[65536];
    ssize_t n = ::read(channel_->fd(), buf, sizeof(buf));
    messageHandler_(this, buf, n);
}

}
