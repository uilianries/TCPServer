/**
 * \file
 * \brief Implements TCP Server application
 */

#include "TCPServerApp.hpp"

#include <Poco/File.h>
#include <Poco/Format.h>
#include <Poco/TaskManager.h>

int TCPServerApp::main(const ArgVec& args)
{
    std::ignore = args;
    Poco::TaskManager task_manager;

    task_manager.start(createTCPTask());

    waitForTerminationRequest();

    task_manager.cancelAll();
    task_manager.joinAll();

    return Poco::Util::Application::EXIT_OK;
}

void TCPServerApp::initialize(Application& self)
{
    loadConfiguration(configurationPath().toString());
    configureLogger();
    ServerApplication::initialize(self);
}

void TCPServerApp::configureLogger()
{
    logger().setLevel("debug");
    Poco::Logger::root().setLevel("debug");

    file_channel_.assign(new Poco::FileChannel);
    const auto& app_name = config().getString("application.name");

    Poco::Path log_path = getLogRootDir().get();
    log_path.append(app_name + "-app.log");

    file_channel_->setProperty("path", log_path.toString());
    file_channel_->setProperty("rotation", getLogSize().get());
    file_channel_->setProperty("archive", "timestamp");

    pattern_formatter_.assign(new Poco::PatternFormatter);
    pattern_formatter_->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
    formatting_channel_.assign(new Poco::FormattingChannel(pattern_formatter_, file_channel_));
    Poco::Logger::root().setChannel(formatting_channel_);
    logger().setChannel(formatting_channel_);
}

Poco::Path TCPServerApp::configurationPath() const noexcept
{
    const auto& app_name = config().getString("application.name");
    return Poco::format("/etc/%s/%s-config.json", app_name, app_name);
}

TCPServerTask* TCPServerApp::createTCPTask()
{
    const auto& log_size = getLogSize();
    if (!log_size) {
        throw std::invalid_argument("Could not load MAX LOG SIZE");
    }

    const auto& socket_port = getPort();
    if (!socket_port) {
        throw std::invalid_argument("Could not load TCP PORT");
    }

    const auto& log_directory = getLogRootDir();
    if (!log_directory) {
        throw std::invalid_argument("Could not load ROOT DIRECTORY");
    }

    return new TCPServerTask(socket_port.get(), log_size.get(), log_directory.get());
}

boost::optional<std::string> TCPServerApp::getLogSize() const noexcept
{
    return getLexicalOption<std::string>("log.max_file_size");
}

boost::optional<unsigned> TCPServerApp::getPort() const noexcept
{
    return getLexicalOption<unsigned>("server.port");
}

boost::optional<std::string> TCPServerApp::getLogRootDir() const noexcept
{
    return getLexicalOption<std::string>("log.root_directory");
}

