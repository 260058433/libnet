#ifndef SOCKET_H
#define SOCKET_H

#include <cstddef>

class Socket {
public:
    explicit Socket(int socketFd);

    int send(const char *buf, size_t len, int flags);

    void close();

private:
    int fd;
};

#endif
