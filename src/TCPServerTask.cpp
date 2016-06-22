/**
 * \file
 * \brief Implements TCP Server task
 */

#include "TCPServerTask.hpp"

TCPServerTask::TCPServerTask(unsigned socket_port, const std::string& formatted_log_size)
    : Poco::Task("TCPServerTask")
    , server_port_{ socket_port }
    , formatted_log_size_{ formatted_log_size }
{
}

void TCPServerTask::runTask()
{
    // TODO (uilian.ries) - Create TCP Server
}

void TCPServerTask::cancel()
{
    // TODO (uilian.ries) - Cancel TCP Server
}