/**
 * \file
 * \brief Implements TCP Server task
 */

#include "TCPServerTask.hpp"
#include "TCPServerLogger.hpp"

TCPServerTask::TCPServerTask(unsigned socket_port, const std::string& formatted_log_size, const Poco::Path& log_directory)
    : Poco::Task("TCPServerTask")
    , server_port_{ socket_port }
    , formatted_log_size_{ formatted_log_size }
    , root_directory_{ log_directory }
{
}

void TCPServerTask::runTask()
{
    TCPServerLogger::create(root_directory_, formatted_log_size_);
    TCPServerLogger::instance()->log("Task Created");
    // TODO (uilian.ries) - Create TCP Server
}