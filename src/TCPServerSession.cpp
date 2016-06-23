/**
 * \file
 * \brief Implement TCP Server Session
 */

#include "TCPServerSession.hpp"

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include "TCPServerLogger.hpp"

TCPServerSession::Ptr TCPServerSession::create(boost::asio::io_service& io_service)
{
    return boost::make_shared<TCPServerSession>(io_service);
}

boost::asio::ip::tcp::socket& TCPServerSession::getSocket()
{
    return socket_;
}

void TCPServerSession::bind()
{
    socket_.async_read_some(boost::asio::buffer(message_, buffer_size),
        boost::bind(&TCPServerSession::onRead, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));
}

TCPServerSession::TCPServerSession(boost::asio::io_service& io_service)
    : socket_{ io_service }
{
}

void TCPServerSession::onRead(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error) {
        TCPServerLogger::instance().log(bytes_transferred, " - ", message_.data());
    }
}