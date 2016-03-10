#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "Socket.h"

class ServerSocket {
public:
    ServerSocket();

    void init(int port = 8080, int backlog = 20);

    void setNonblock();

    Socket accept();

    void close();

private:
    int fd;
};

#endif
