#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "Socket.h"
#include "Channel.h"

#include <functional>

namespace libnet
{

class InetAddress;
class EventLoop;

class Acceptor
{
public:
    typedef std::function<void (int, const InetAddress &)> NewConnectionHandler;

    Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reusePort = true);
    ~Acceptor();

    void listen();

    void setNewConnectionHandler(const NewConnectionHandler &nch)
    { newConnectionHandler_ = nch; }

private:
    int createNonblockSocket();
    void handlerRead();

    EventLoop *loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    NewConnectionHandler newConnectionHandler_;
};

}

#endif
