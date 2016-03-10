#ifndef SOCKET_H
#define SOCKET_H

namespace libnet
{

class InetAddress;

class Socket
{
public:
    explicit Socket(int socketfd);

    ~Socket();

    void listen();

    void accept(InetAddress *peerAddr);

    int fd() const
    { return socketfd_; }

    void setReusePort(bool on);

private:
    int socketfd_;
};

}

#endif
