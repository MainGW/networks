//
// Created by 玩奥i on 2021/2/26.
//

#ifndef NETWORKS_TCPSOCKET_HPP
#define NETWORKS_TCPSOCKET_HPP

#include "AbstractSocket.hpp"
#include <vector>

#define BUFSIZE 1024

namespace networks {
    class TCPSocket : public AbstractSocket{
    public:
        TCPSocket() = default;
        TCPSocket(NetWorkAddress addr);
        ~TCPSocket();

        void bind(NetWorkAddress addr);
        void conn(NetWorkAddress addr);
        void listen(NetWorkAddress addr);
        void waitForRequest(void (*doGet)(AbstractSocket *, int));

        void recv(char *buf, int maxsize, int fromSocket);

        void send(char *buf, int size, int toSocket);

    protected:
        int SelfSocket;
        sockaddr_in MyAddr;
        NetWorkAddress SelfAddr;
        char *SelfBuf;
    };
}

#endif //NETWORKS_TCPSOCKET_HPP
