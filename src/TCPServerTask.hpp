/**
 * \file
 * \brief Declare TCP Server task
 */

#ifndef TCPSERVER_TCPSERVERTASK_HPP
#define TCPSERVER_TCPSERVERTASK_HPP

#include <Poco/Task.h>
#include <Poco/Path.h>

#include <string>

/**
 * \brief Execute TCP server under async task
 */
class TCPServerTask : public Poco::Task {
public:
    /**
     * \brief Create TCPServer task
     * \param socket_port TCP Server port
     * \param formatted_log_size Max log size
     * \param log_directory Log root directory
     */
    TCPServerTask(unsigned socket_port, const std::string& formatted_log_size, const Poco::Path& log_directory);

    /**
     * \brief Start TCP Server
     */
    void runTask() override;

private:
    unsigned server_port_; /**< TCP Server port */
    std::string formatted_log_size_; /**< Formatted max log size */
    Poco::Path root_directory_; /**< Root directory */
};

#endif //TCPSERVER_TCPSERVERTASK_HPP
