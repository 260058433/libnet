#include "Socket.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>

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

void Socket::setReusePort(bool on)
{
    int optval = on ? 1 : 0;
    if (::setsockopt(socketfd_, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof(optval))) == -1)
        throw std::runtime_error("setsockopt");
}

}
