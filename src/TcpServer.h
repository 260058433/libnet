#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <functional>
#include <memory>
#include <sys/types.h>

namespace libnet
{

class Acceptor;
class EventLoop;
class InetAddress;
class TcpConnection;

class TcpServer
{
public:
    typedef std::function<void (TcpConnection *)> ConnectionHandler;
    typedef std::function<void (TcpConnection *, const char *, ssize_t)> MessageHandler;

    TcpServer(EventLoop *loop, const InetAddress &listenAddr);
    ~TcpServer();

    void start();

    void setConnectionHandler(const ConnectionHandler &ch)
    { connectionHandler_ = ch; }

    void setMessageHandler(const MessageHandler &mh)
    { messageHandler_ = mh; }

private:
    void newConnection(int sockfd, const InetAddress &peerAddr);

    EventLoop *loop_;
    std::unique_ptr<Acceptor> acceptor_;
    ConnectionHandler connectionHandler_;
    MessageHandler messageHandler_;
};

}

#endif
