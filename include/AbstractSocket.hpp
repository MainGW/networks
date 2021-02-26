//
// Created by 玩奥i on 2021/2/26.
//

#ifndef NETWORKS_ABSTRACTSOCKET_HPP
#define NETWORKS_ABSTRACTSOCKET_HPP

namespace networks {
    typedef struct {
        char *addr;
        int port;
    }NetWorkAddress;
    class AbstractSocket {
    protected:
        AbstractSocket() = default;

        ~AbstractSocket() = default;

        virtual void bind(NetWorkAddress) = 0;

        virtual void conn(NetWorkAddress) = 0;

        virtual void listen(NetWorkAddress) = 0;

        virtual void waitForRequest(void (*doGet)(AbstractSocket *, int)) = 0;

        virtual void recv(char *, int, int) = 0;

        virtual void send(char *, int, int) = 0;
    };
}

#endif //NETWORKS_ABSTRACTSOCKET_HPP
