#include "Acceptor.h"
#include "Socket.h"
#include "Channel.h"
#include "InetAddress.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>

namespace libnet
{

Acceptor::Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reusePort) :
    loop_(loop),
    acceptSocket_(createNonblockSocket()),
    acceptChannel_(loop, acceptSocket_.fd()),
    newConnectionHandler_(nullptr)
{
    acceptSocket_.setReusePort(reusePort);
    acceptSocket_.bindAddress(listenAddr);
    acceptChannel_.setReadHandler(std::bind(&Acceptor::handlerRead, this));
}

Acceptor::~Acceptor()
{
}

int Acceptor::createNonblockSocket()
{
    int socketfd = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketfd == -1)
        throw std::runtime_error("socket");

    int flags = ::fcntl(socketfd, F_GETFL, 0);
    if (flags == -1)
        throw std::runtime_error("fcntl");
    flags |= O_NONBLOCK;
    flags |= FD_CLOEXEC;
    if (fcntl(socketfd, F_SETFL, flags) == -1)
        throw std::runtime_error("fcntl");

    return socketfd;
}

void Acceptor::listen()
{
    acceptChannel_.start();
    acceptChannel_.enableReading();
    acceptSocket_.listen();
}

void Acceptor::handlerRead()
{
    InetAddress peerAddr;
    int connfd = acceptSocket_.accept(&peerAddr);
    if (connfd >= 0)
    {
        if (newConnectionHandler_)
            newConnectionHandler_(connfd, peerAddr);
        else
            ::close(connfd);
    }
}

}
