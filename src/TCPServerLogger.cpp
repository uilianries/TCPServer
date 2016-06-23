/**
 * \file
 * \brief Implement TCP Server logger
 */

#include "TCPServerLogger.hpp"
#include "FormattedSizeValidation.hpp"


TCPServerLogger::TCPServerLogger(const Poco::Path& file_path, const std::string& formatted_size)
{
    if (!file_path.isFile()) {
        throw std::invalid_argument("ERROR: Invalid log file path");
    }

    auto size = FormattedSizeValidation::toUInt(formatted_size);
    if (!size) {
        throw std::invalid_argument("ERROR: Invalid size format - Only kilo and Mega are supported");
    }

    // TODO (uilian.ries) - Create Boost Logger instance
}

void TCPServerLogger::writeFile(const std::ostringstream& oss)
{
    std::ignore = oss;
    // TODO (uilian.ries) - Write on file
}

TCPServerLogger::Ptr& TCPServerLogger::create(const Poco::Path& file_path, const std::string& formatted_size)
{
    static TCPServerLogger::Ptr singleton;
    if (!singleton) {
        singleton.reset(new TCPServerLogger(file_path, formatted_size));
    }
    return singleton;
}