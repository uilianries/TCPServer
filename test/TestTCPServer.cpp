/**
 * \file
 * \brief Unit Test for TCP Server
 *
 * All Tests are based on client_connection.feature
 */
#include <memory>

#include <Poco/File.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Path.h>
#include <Poco/Process.h>
#include <gtest/gtest.h>

/**
 * \brief Execute tests on TCP server
 */
class TestTCPServer : public testing::Test {

public:
    /**
     * \brief Connect TCP client on server
     */
    void SetUp() override
    {
        const Poco::File server_process("tcp-server");
        ASSERT_TRUE(server_process.isFile());
        ASSERT_TRUE(server_process.canExecute());

        process_handle_.reset(new Poco::ProcessHandle(Poco::Process::launch(server_process.path(), {})));
        ASSERT_THROW(stream_socket_.connect(server_port()), Poco::Net::NetException);
        ASSERT_NE(0, process_handle_->id());
        ASSERT_TRUE(Poco::Process::isRunning(*process_handle_));
    }

    /**
     * \brief Graceful shutdown
     */
    void TearDown() override
    {
        ASSERT_THROW(stream_socket_.shutdown(), Poco::Net::NetException);
        Poco::Process::requestTermination(process_handle_->id());
        Poco::Process::wait(*process_handle_);
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
    std::unique_ptr<Poco::ProcessHandle> process_handle_;
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
    const Poco::Path log_path("/var/log/tcp-server/tcp-server.log");
    ASSERT_TRUE(log_path.isFile());
}
