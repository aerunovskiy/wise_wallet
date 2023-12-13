#include "tcp_server.h"

TcpServer::TcpServer(boost::asio::io_context &io_context, unsigned int port)
: _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    do_accept();
}

void TcpServer::do_accept()
{
    _acceptor.async_accept(
        [this](const boost::system::error_code& ec, tcp::socket socket)
        {
            if (!ec)
            {
                std::cout << "Client connected" << std::endl;
                std::make_shared<Session>(std::move(socket))->start();
            }
            else
            {
                std::cerr << "Error when connecting the client: " << ec.message() << std::endl;
            }

            do_accept();
    });
}
