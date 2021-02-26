//
// Created by 玩奥i on 2021/2/26.
//

#ifndef NETWORKS_SOCKETEXCEPTION_HPP
#define NETWORKS_SOCKETEXCEPTION_HPP
#include <exception>
#include <cstring>
namespace networks{
    struct SocketException : public std::exception{
        const char *what() const throw();
    };
    const char *SocketException::what() const throw() {
        return "Socket error";
    }
}
#endif //NETWORKS_SOCKETEXCEPTION_HPP
