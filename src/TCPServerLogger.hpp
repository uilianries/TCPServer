/**
 * \file
 * \brief Declare TCP Server logger
 */

#ifndef TCPSERVER_TCPSERVERLOGGER_HPP
#define TCPSERVER_TCPSERVERLOGGER_HPP

#include <string>
#include <memory>
#include <Poco/Path.h>

#include "VariadicLogger.hpp"

/**
 * \brief Create a log file with rotation support
 */
class TCPServerLogger
{
public:

    /** Logger pointer */
    using Ptr = std::unique_ptr<TCPServerLogger>;

    /** Not allowed */
    TCPServerLogger(const TCPServerLogger&) = delete;
    /** Not allowed */
    TCPServerLogger(TCPServerLogger&&) = delete;
    /** Not allowed */
    TCPServerLogger& operator=(const TCPServerLogger&) = delete;
    /** Not allowed */
    TCPServerLogger& operator=(TCPServerLogger&&) = delete;

    /**
     * \brief Create unique logger instance
     * \param file_path absolute file path to be wrote
     * \param formatted_size Max file size. I.e. "1 M" is 1 Megabyte
     */
    Ptr& create(const Poco::Path& file_path, const std::string& formatted_size);

    /**
     * \brief Variadic message log
     * \param args Anything supported by streams
     */
    template<typename ...Args>
    void log(Args&& ...args)
    {
        std::ostringstream oss;
        VariadicLogger(oss, std::forward<Args>(args)...);
        writeFile(oss);
    }

private:

    /**
     * \brief Create a stream logger
     * \param file_path absolute file path to be wrote
     * \param formatted_size Max file size. I.e. "1 M" is 1 Megabyte
     */
    TCPServerLogger(const Poco::Path& file_path, const std::string& formatted_size);

    /**
     * \brief Write message on log file
     * \param oss stream to be wrote
     */
    void writeFile(const std::ostringstream& oss);

};


#endif //TCPSERVER_TCPSERVERLOGGER_HPP
