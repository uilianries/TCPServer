/**
 * \file
 * \brief Implements TCP Server
 */

#include "TCPServer.hpp"

#include <boost/bind.hpp>

#include "TCPServerLogger.hpp"

TCPServer::Ptr TCPServer::create(unsigned port)
{
    return TCPServer::Ptr(new TCPServer(port));
}

void TCPServer::run()
{
    try {
        io_service_.run();
    } catch (const std::exception& except) {
        TCPServerLogger::instance().log(except.what());
        std::terminate();
    }
}

TCPServer::TCPServer(unsigned port)
    : acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    start();
}

void TCPServer::start()
{
    auto session = TCPServerSession::create(io_service_);
    acceptor_.async_accept(session->getSocket(),
        boost::bind(&TCPServer::onAccept, this, session,
                               boost::asio::placeholders::error));
}

void TCPServer::onAccept(TCPServerSession::Ptr connection,
    const boost::system::error_code& error)
{
    if (!error) {
        connection->bind();
    }
    start();
}
