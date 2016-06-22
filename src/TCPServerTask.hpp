/**
 * \file
 * \brief Declare TCP Server task
 */

#ifndef TCPSERVER_TCPSERVERTASK_HPP
#define TCPSERVER_TCPSERVERTASK_HPP

#include <Poco/Task.h>
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
     */
    TCPServerTask(unsigned socket_port, const std::string& formatted_log_size);

    /**
     * \brief Start TCP Server
     */
    void runTask() override;

    /**
     * \brief Cancel TCP Server execution
     */
    void cancel() override;

private:
    unsigned server_port_; /**< TCP Server port */
    std::string formatted_log_size_; /**< Formatted max log size */
};

#endif //TCPSERVER_TCPSERVERTASK_HPP
