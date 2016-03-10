#include "Acceptor.h"
#include "Socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <fcntl.h>

namespace libnet
{

Acceptor::Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reusePort) :
    loop_(loop),
    acceptSocket_(createNonblockSocket()),
    acceptChannel_(loop, acceptSocket_.fd()),
    newConnectionHandler_(nullptr)
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

}
