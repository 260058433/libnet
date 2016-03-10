#include "Socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>
#include <unistd.h>

using std::runtime_error;

Socket::Socket(int socketFd) : fd(socketFd) {
}

int Socket::send(const char *buf, size_t len, int flags) {
    int res = static_cast<int>(::send(fd, buf, len, flags));
    if (res == -1)
        throw runtime_error("send");
    return res;
}

void Socket::close() {
    if (::close(fd) == -1)
        throw runtime_error("close");
}
