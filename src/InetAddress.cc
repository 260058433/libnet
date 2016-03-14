#include "InetAddress.h"

#include <strings.h>
#include <stdexcept>
#include <arpa/inet.h>

namespace libnet
{
    
InetAddress::InetAddress(uint16_t port)
{
    bzero(&addr_, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_.sin_port = htons(port);
}

InetAddress::InetAddress(const std::string &ip, uint16_t port)
{
    bzero(&addr_, sizeof(addr_));
    addr_.sin_family = AF_INET;
    if (::inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr) == -1)
        throw std::runtime_error("inet_pton");
    addr_.sin_port = htons(port);
}

InetAddress::InetAddress(const struct sockaddr_in &addr) :
    addr_(addr)
{
}

}
