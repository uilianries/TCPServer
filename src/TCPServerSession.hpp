/**
 * \file
 * \brief Declare TCP Server Session
 */

#ifndef TCPSERVER_TCPSERVERSESSION_HPP
#define TCPSERVER_TCPSERVERSESSION_HPP

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

/**
 * \brief TCP Connection
 */
class TCPServerSession : public boost::enable_shared_from_this<TCPServerSession> {
public:
    /** Connection pointer */
    using Ptr = boost::shared_ptr<TCPServerSession>;

    /**
     * \brief Create a new connection
     */
    static Ptr create(boost::asio::io_service& io_service);
    /**
     * \brief Retrieve member socket
     * \return Connection socket
     */
    boost::asio::ip::tcp::socket& getSocket();

    /**
     * \brief Bind to the socket
     */
    void bind();

    /**
     * \brief New session
     * \param io_service connection socket
     */
    explicit TCPServerSession(boost::asio::io_service& io_service);

private:
    static constexpr auto buffer_size = 1024;
    boost::asio::ip::tcp::socket socket_; /** Connection socket */
    boost::array<char, buffer_size> message_; /** Buffer message */

    /**
     * \brief Treat read event
     * \param error read status
     * \param bytes_transferred bytes transferred
     */
    void onRead(const boost::system::error_code& error, std::size_t bytes_transferred);
};

#endif //TCPSERVER_TCPSERVERSESSION_HPP
