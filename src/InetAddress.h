#ifndef INETADDRESS_H
#define INETADDRESS_H

#include <cstdint>
#include <string>
#include <netinet/in.h>

namespace libnet
{

class InetAddress
{
public:
    explicit InetAddress(uint16_t port = 0);

    InetAddress(const std::string &ip, uint16_t port);

    explicit InetAddress(const struct sockaddr_in &addr);

    const struct sockaddr_in* getSockAddr() const
    { return &addr_; }

    void setSockAddr(const struct sockaddr_in &addr)
    { addr_ = addr; }

private:
    struct sockaddr_in addr_;
};

}

#endif
