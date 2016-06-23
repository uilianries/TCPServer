/**
 * \file
 * \brief Unit Test for TCP Server
 *
 * All Tests are based on client_connection.feature
 */
#include <memory>
#include <fstream>

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

        process_handle_.reset(
            new Poco::ProcessHandle(Poco::Process::launch(server_process.path(), {})));
        ASSERT_NE(0, process_handle_->id());
        ASSERT_TRUE(Poco::Process::isRunning(*process_handle_));
    }

    /**
     * \brief Graceful shutdown
     */
    void TearDown() override
    {
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

   private:
    std::unique_ptr<Poco::ProcessHandle> process_handle_; /**< Process handle */
};

/**
 * \brief Send data message to server
 *          and expect read the same
 *          same at log file
 */
TEST_F(TestTCPServer, Loopback)
{
/**
 * XXX (uilian.ries) - Travis CI Blocks all ports
 */
#ifndef TRAVIS_CI
    Poco::Net::SocketAddress socket_address(server_port());
    Poco::Net::StreamSocket stream_socket(socket_address);
    Poco::Net::SocketStream socket_stream(stream_socket);

    socket_stream << message();
    socket_stream.flush();

    const Poco::File log_file("/tmp/tcp-server-message_0.log");
    ASSERT_TRUE(log_file.isFile());
    ASSERT_TRUE(log_file.canRead());

    std::ifstream ifs(log_file.path());
    std::string line;
    bool found = false;
    while (std::getline(ifs, line)) {
        if (line.find(message(), 0) != std::string::npos) {
            found = true;
            break;
        }
    }

    ASSERT_TRUE(found);
#endif
}
