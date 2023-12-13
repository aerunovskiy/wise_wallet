#pragma once

#include <boost/asio.hpp>
#include <iostream>

#include "session.h"

using boost::asio::ip::tcp;

class TcpServer
{
public:
    TcpServer(boost::asio::io_context& io_context, unsigned int port);

private:
    void do_accept();

private:
    boost::asio::ip::tcp::acceptor _acceptor;
};