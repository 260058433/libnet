#include "Socket.h"
#include "InetAddress.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>
#include <strings.h>

namespace libnet
{

Socket::Socket(int socketfd) :
    socketfd_(socketfd)
{
}

Socket::~Socket()
{
    ::close(socketfd_);
}

void Socket::bindAddress(const InetAddress &localAddr)
{
    if (::bind(socketfd_, reinterpret_cast<const struct sockaddr *>(localAddr.getSockAddr()), sizeof(sockaddr_in)) == -1)
        throw std::runtime_error("bind");
}

void Socket::listen()
{
    if (::listen(socketfd_, 20) == -1)
        throw std::runtime_error("listen");
}

int Socket::accept(InetAddress *peerAddr)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    bzero(&addr, sizeof(addr));
    int connfd = ::accept(socketfd_, reinterpret_cast<struct sockaddr *>(&addr), &len);
    if (connfd == -1)
        throw std::runtime_error("accrpt");
    peerAddr->setSockAddr(addr);
    return connfd;
}

void Socket::setReusePort(bool on)
{
    int optval = on ? 1 : 0;
    if (::setsockopt(socketfd_, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof(optval))) == -1)
        throw std::runtime_error("setsockopt");
}

}
