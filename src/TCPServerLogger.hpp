/**
 * \file
 * \brief Declare TCP Server logger
 */

#ifndef TCPSERVER_TCPSERVERLOGGER_HPP
#define TCPSERVER_TCPSERVERLOGGER_HPP

#include <string>
#include <memory>
#include <Poco/Path.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

#include "VariadicLogger.hpp"

namespace trivial = boost::log::v2s_mt_posix::trivial;
namespace sources = boost::log::v2s_mt_posix::sources;

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
     * \brief Get unique instance
     * \return Unique logger instance
     */
    static Ptr& instance();

    /**
     * \brief Create unique logger instance
     * \param directory_path absolute directory path to be wrote
     * \param formatted_size Max file size. I.e. "1 M" is 1 Megabyte
     */
    static void create(const Poco::Path& directory_path, const std::string& formatted_size);

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

    sources::severity_logger<trivial::severity_level> logger_; /**< Logger handler */
    static Ptr self_; /** singleton */

    /**
     * \brief Retrieve log file name
     * \return File name
     */
    static constexpr const char * getLogName() noexcept
    {
        return "tcp-server-message";
    }

    /**
     * \brief Create a stream logger
     * \param directory_path absolute directory path to be wrote
     * \param formatted_size Max file size. I.e. "1 M" is 1 Megabyte
     */
    TCPServerLogger(const Poco::Path& directory_path, const std::string& formatted_size);

    /**
     * \brief Write message on log file
     * \param oss stream to be wrote
     */
    void writeFile(const std::ostringstream& oss);

    /**
     * \brief Initialize boost log
     * \param root_directory Where the log will be created
     * \param rotation_size Max file sie
     */
    void initLog(const Poco::Path& root_directory, unsigned rotation_size);

};


#endif //TCPSERVER_TCPSERVERLOGGER_HPP
