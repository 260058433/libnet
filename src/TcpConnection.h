#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <functional>
#include <memory>
#include <sys/types.h>

namespace libnet
{

class EventLoop;
class Channel;

class TcpConnection
{
public:
    typedef std::function<void (TcpConnection *)> ConnectionHandler;
    typedef std::function<void (TcpConnection *, const char *, ssize_t)> MessageHandler;

    TcpConnection(EventLoop *loop, int sockfd);
    ~TcpConnection();

    void setConnectionHandler(const ConnectionHandler &ch)
    { connectionHandler_ = ch; }

    void setMessageHandler(const MessageHandler &mh)
    { messageHandler_ = mh; }

private:
    void handleRead();
    
    EventLoop *loop_;
    std::unique_ptr<Channel> channel_;
    ConnectionHandler connectionHandler_;
    MessageHandler messageHandler_;
};

}

#endif
