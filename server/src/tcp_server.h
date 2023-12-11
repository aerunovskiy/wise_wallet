#pragma once

#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

class TcpServer
{
public:
    TcpServer(boost::asio::io_context& io_context, unsigned int port);

private:
    void _start_accept();

    void _start_read(const std::shared_ptr<tcp::socket>& socket, std::array<char, 4096>& buffer);

private:
    boost::asio::io_context& _io_context;

    boost::asio::ip::tcp::acceptor _acceptor;
};