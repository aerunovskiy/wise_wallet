#include "session.h"

Session::Session(tcp::socket socket)
: _socket(std::move(socket))
{}

void Session::start()
{
    do_read();
}

void Session::do_read()
{
    auto self(shared_from_this());

    _socket.async_read_some(
        boost::asio::buffer(_data, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::cout << "Receive " << length << "=" << std::string(_data, length) << std::endl;
                do_write(length);
            }
        });
}

void Session::do_write(std::size_t length)
{
    auto self(shared_from_this());

    boost::asio::async_write(
        _socket,
        boost::asio::buffer(_data, length),
        [this, self](boost::system::error_code ec, size_t)
        {
            if (!ec)
                do_read();
        });
}
