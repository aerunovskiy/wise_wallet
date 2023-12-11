#include "tcp_server.h"

TcpServer::TcpServer(boost::asio::io_context &io_context, unsigned int port)
: _io_context(io_context),
  _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    _start_accept();
}

void TcpServer::_start_accept()
{
    std::shared_ptr<boost::asio::ip::tcp::socket> socket = std::make_shared<boost::asio::ip::tcp::socket>(_io_context);

    _acceptor.async_accept(*socket, [socket, this](const boost::system::error_code& error) {
        if (!error)
        {
            std::cout << "Client connected" << std::endl;

            std::array<char, 4096> buffer{};

            _start_read(socket, buffer);
        }
        else
        {
            std::cerr << "Error when connecting the client: " << error.message() << std::endl;
        }

        _start_accept();
    });
}

void TcpServer::_start_read(const std::shared_ptr<boost::asio::ip::tcp::socket>& socket, std::array<char, 4096> &buffer)
{
    socket->async_read_some(boost::asio::buffer(buffer), [socket, &buffer, this](const boost::system::error_code& error, std::size_t bytes_transferred) {
        if (!error)
        {
            std::cout << "Message received: " << std::string(buffer.data(), bytes_transferred);

            boost::asio::write(*socket, boost::asio::buffer("Message received\n"));

            _start_read(socket, buffer);
        }
        else
        {
            socket->close();
        }
    });
}
