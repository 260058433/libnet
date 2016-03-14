#include "TcpServer.h"
#include "Acceptor.h"
#include "TcpConnection.h"

#include <functional>

namespace libnet
{

TcpServer::TcpServer(EventLoop *loop, const InetAddress &listenAddr) :
    loop_(loop),
    acceptor_(new Acceptor(loop, listenAddr))
{
    acceptor_->setNewConnectionHandler(std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2));
}

TcpServer::~TcpServer()
{
}

void TcpServer::start()
{
    acceptor_->listen();
}

void TcpServer::newConnection(int sockfd, const InetAddress &peerAddr)
{
    TcpConnection *conn = new TcpConnection(loop_, sockfd);
    conn->setConnectionHandler(connectionHandler_);
    conn->setMessageHandler(messageHandler_);
}

}
