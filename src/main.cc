#include "EventLoop.h"
#include "Channel.h"
#include "Poller.h"
#include "Acceptor.h"
#include "InetAddress.h"
#include "Socket.h"
#include "TcpServer.h"
#include "TcpConnection.h"

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <sys/epoll.h>

using namespace libnet;
using namespace std;

void onConnection(const TcpConnection *conn)
{
    cout << "connection" << endl;
}

void onMessage(const TcpConnection *conn, const char *data, ssize_t len)
{
    cout << "message" << endl;
    cout << data << endl;
}

int main()
{
    EventLoop loop;

    InetAddress addr(8080);

    TcpServer server(&loop, addr);
    server.setConnectionHandler(onConnection);
    server.setMessageHandler(onMessage);

    server.start();

    loop.loop();
}
