/**
 * \file
 * \brief Declare TCP Server
 */

#ifndef TCPSERVER_TCPSERVER_HPP
#define TCPSERVER_TCPSERVER_HPP

#include "TCPServerSession.hpp"
#include <boost/asio.hpp>

/**
 * \brief TCP server based on boost asio
 */
class TCPServer {
public:
    /** TCPServer pointer */
    using Ptr = std::unique_ptr<TCPServer>;

    /**
     * \brief Create TCPServer instance
     * \param Server port
     */
    static Ptr create(unsigned port);

    /**
     * \brief Run server
     */
    void run();

private:
    boost::asio::io_service io_service_; /** Service */
    boost::asio::ip::tcp::acceptor acceptor_; /** Accept connection */

    /**
     * \brief Constructor
     * \param port Server TCP port
     */
    explicit TCPServer(unsigned port);

    /**
     * \brief Start to accept connections
     */
    void start();

    /**
     * \brief On accept new connection
     * \param connection client connection
     * \param error connectio status
     */
    void onAccept(TCPServerSession::Ptr connection,
        const boost::system::error_code& error);
};

#endif //TCPSERVER_TCPSERVER_HPP
