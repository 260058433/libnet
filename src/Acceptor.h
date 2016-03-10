#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "Socket.h"
#include "Channel.h"

namespace libnet
{

class InetAddress;
class EventLoop;

class Acceptor
{
public:
    typedef void (*NewConnectionHandler)(int sockfd, const InetAddress &);

    Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reusePort);
    ~Acceptor();

    void setNewConnectionHandler(const NewConnectionHandler &nch)
    { newConnectionHandler_ = nch; }

private:
    int createNonblockSocket();

    EventLoop *loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    NewConnectionHandler newConnectionHandler_;
};

}

#endif
