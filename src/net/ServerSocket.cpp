#include "ServerSocket.h"
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <cstdint>
#include <unistd.h>
#include <fcntl.h>

using std::runtime_error;

ServerSocket::ServerSocket() : fd(-1) {
}

void ServerSocket::init(int port, int backlog) {
    fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        throw runtime_error("socket");

    int optval = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, static_cast<const void *>(&optval), sizeof(optval)) < 0)
        throw runtime_error("setsockopt");

    sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(static_cast<uint16_t>(port));
    if (bind(fd, (sockaddr *)&addr, sizeof(addr)) < 0)
        throw runtime_error("bind");

    if (listen(fd, backlog) < 0)
        throw runtime_error("listen");
}

void ServerSocket::setNonblock() {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        throw runtime_error("get fcntl");

    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1)
        throw runtime_error("set fcntl");
}

Socket ServerSocket::accept() {
    sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    int client = ::accept(fd, (sockaddr *)&clientAddr, &clientLen);
    if (client == -1)
        throw runtime_error("accept");
    return Socket(client);
}

void ServerSocket::close() {
    if (::close(fd) == -1)
        throw runtime_error("close");
}
