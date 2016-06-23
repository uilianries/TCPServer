/**
 * \file
 * \brief Implement TCP Server logger
 */

#include "TCPServerLogger.hpp"

#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include "FormattedSizeValidation.hpp"

TCPServerLogger::Ptr TCPServerLogger::self_;

TCPServerLogger::TCPServerLogger(const Poco::Path& directory_path, const std::string& formatted_size)
{
    if (!directory_path.isDirectory()) {
        std::cerr << "ERROR: Invalid root directory";
        std::terminate();
    }

    auto size = FormattedSizeValidation::toUInt(formatted_size);
    if (!size) {
        std::cerr << "ERROR: Invalid size format" << std::endl;
        std::terminate();
    }

    initLog(directory_path, size.get());
    boost::log::add_common_attributes();
}

void TCPServerLogger::writeFile(const std::ostringstream& oss)
{
    BOOST_LOG_SEV(logger_, trivial::info) << oss.str();
}

void TCPServerLogger::create(const Poco::Path& file_path, const std::string& formatted_size)
{
    if (!TCPServerLogger::self_) {
        TCPServerLogger::self_.reset(new TCPServerLogger(file_path, formatted_size));
    }
}

TCPServerLogger::Ptr& TCPServerLogger::instance()
{
    return TCPServerLogger::self_;
}

void TCPServerLogger::initLog(const Poco::Path& root_directory, unsigned rotation_size)
{
    Poco::Path log_path = root_directory;
    log_path.append(std::string(getLogName()) + "_%N.log");

    boost::log::add_file_log
    (
            boost::log::keywords::file_name = log_path.toString(),
            boost::log::keywords::rotation_size = rotation_size,
            boost::log::keywords::format = "[%TimeStamp%]: %Message%"
    );

    boost::log::core::get()->set_filter
    (
            trivial::severity >= trivial::info
    );
}
