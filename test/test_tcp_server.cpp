/**
 * \file
 * \brief Unit Test for TCP Server
 *
 * All Tests are based on client_connection.feature
 */
#include <gtest/gtest.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/Net/NetException.h>
#include <Poco/File.h>

/**
 * \brief Execute tests on TCP server
 */
class TestTCPServer : public testing::Test
{
public:
    /**
     * \brief Connect TCP client on server
     */
    void SetUp() override
    {
        ASSERT_THROW(stream_socket_.connect(server_port()), Poco::Net::NetException);
    }

    /**
     * \brief Graceful shutdown
     */
    void TearDown() override
    {
        ASSERT_THROW(stream_socket_.shutdown(), Poco::Net::NetException);
    }

    /**
     * \brief Retrieve TCP Server socket port
     * \return port number
     */
    inline unsigned server_port() const
    {
        return 30000u;
    }

    /**
     * \brief Retrieve stream message
     * \return stream message
     */
    inline std::string message() const
    {
        return "foobar";
    }

    /**
     * \brief Retrieve Stream channel to socket
     * \return socket stream
     */
    Poco::Net::StreamSocket& stream()
    {
        return stream_socket_;
    }

private:
    /** TCP client */
    Poco::Net::StreamSocket stream_socket_;
};

/**
 * \brief Send data message to server
 *          and expect read the same
 *          same at log file
 */
TEST_F(TestTCPServer, Loopback)
{
    Poco::Net::SocketStream ss(stream());
    // FIXME(uilian.ries): Not working yet
    //ss << message();

    // TODO(uilian.ries) - Find message in log file
}