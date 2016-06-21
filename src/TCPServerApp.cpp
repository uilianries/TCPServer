/**
 * \file
 * \brief Implements TCP Server application
 */

#include "TCPServerApp.hpp"

#include <Poco/Format.h>
#include <Poco/File.h>
#include <Poco/TaskManager.h>

int TCPServerApp::main(const ArgVec& args)
{
    std::ignore = args;
    Poco::TaskManager task_manager;

    // TODO (uilian.rie): Add TCP Server Task

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

    Poco::Path log_path = config().getString("log.root_directory");
    log_path.append(Poco::Path::pathSeparator);
    log_path.append(app_name + ".log");
    
    file_channel_->setProperty("path", log_path.toString());
    file_channel_->setProperty("rotation", config().getString("log.max_file_size"));
    file_channel_->setProperty("archive", "timestamp");

    pattern_formatter_.assign(new Poco::PatternFormatter);
    pattern_formatter_->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
    formatting_channel_.assign(new Poco::FormattingChannel(pattern_formatter_, file_channel_));
    Poco::Logger::root().setChannel(formatting_channel_);
    logger().setChannel(formatting_channel_);
}

Poco::Path TCPServerApp::configurationPath() const
{
    const auto& app_name = config().getString("application.name");
    return Poco::format("/etc/%s/%s-config.json", app_name, app_name);
}