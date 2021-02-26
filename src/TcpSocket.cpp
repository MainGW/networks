//
// Created by 玩奥i on 2021/2/26.
//

#include "TcpSocket.hpp"
#include "SocketException.hpp"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <wait.h>
namespace networks{
    TCPSocket::TCPSocket(NetWorkAddress addr)
    {
        SelfSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(SelfSocket < 0)
        {
            throw SocketException();
        }
        buf = new char[BUFSIZE];
        memset(buf, 0, BUFSIZE * sizeof(char));
        memset(&MyAddr, 0 ,sizeof(MyAddr));
        MyAddr.sin_family = AF_INET;
        MyAddr.sin_port = htons(addr.port);
        if(inet_pton(AF_INET, addr.addr, &MyAddr) < 0) {
            throw SocketException();
        }
    }
    TCPSocket::~TCPSocket() {
        delete [] buf;
        close(SelfSocket);
    }
    void TCPSocket::bind(NetWorkAddress addr) {
        memset(&MyAddr, 0 ,sizeof(MyAddr));
        MyAddr.sin_family = AF_INET;
        MyAddr.sin_port = htons(addr.port);
        if(inet_pton(AF_INET, addr.addr, &MyAddr) < 0) {
            throw SocketException();
        }
        if(bind(SelfSocket, (struct sockaddr *)&MyAddr, sizeof(MyAddr)) == -1){
            throw SocketException();
        }
    }
    void TCPSocket::conn(NetWorkAddress addr) {
        struct sockaddr_in TAddr;
        memset(&TAddr, 0 ,sizeof(MyAddr));
        TAddr.sin_family = AF_INET;
        TAddr.sin_port = htons(addr.port);
        if(inet_pton(AF_INET, addr.addr, &TAddr) < 0) {
            throw SocketException();
        }
        if(connect(SelfSocket, (struct sockaddr *)&TAddr, sizeof(TAddr)) < 0)
        {
            throw SocketException();
        }
    }
    void TCPSocket::listen(NetWorkAddress addr) {
        memset(&MyAddr, 0 ,sizeof(MyAddr));
        MyAddr.sin_family = AF_INET;
        MyAddr.sin_port = htons(addr.port);
        if(inet_pton(AF_INET, addr.addr, &MyAddr) < 0) {
            throw SocketException();
        }
        if(listen(SelfSocket, 10) == -1){
            throw SocketException();
        }
    }
    void TCPSocket::waitForRequest(void (*doGet)(AbstractSocket *, int)) {
        pid_t NewResponseProcessId;
        int zFD;
        while(1){
            if((zFD = accept(SelfSocket, (struct sockaddr *)NULL, NULL)) == -1)
            {
                continue;
            }
            NewResponseProcessId = fork();
            if(NewResponseProcessId == 0)
            {
                *(doGet)(this, zFD);
                close(zFD);
            }else{
                waitpid(-1, WNOHANG | WUNTRACED);
            }
        }
    }
    void TCPSocket::recv(char *buf, int maxsize, int fromSocket) {
        int t = recv(fromSocket, buf, maxsize, 0);
        buf[t] = '\0';
    }
    void TCPSocket::send(char *buf, int size, int toSocket) {
        send(toSocket, buf, size, 0);
    }

}
