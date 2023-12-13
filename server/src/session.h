#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    explicit Session(tcp::socket socket);

    void start();

private:
    void do_read();

    void do_write(std::size_t length);

private:
    tcp::socket _socket;
    enum { max_length = 1024 };
    char _data[max_length];
};

