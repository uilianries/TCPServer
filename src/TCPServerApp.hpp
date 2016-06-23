/**
 * \file
 * \brief Declare TCP Server application
 */
#ifndef TCPSERVER_TCPSERVERAPP_HPP
#define TCPSERVER_TCPSERVERAPP_HPP

#include <Poco/AutoPtr.h>
#include <Poco/FileChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/Path.h>
#include <Poco/PatternFormatter.h>
#include <Poco/Util/ServerApplication.h>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>

#include "TCPServerTask.hpp"

/**
 * \brief Execute Server application
 */
class TCPServerApp : public Poco::Util::ServerApplication {
public:
    /**
     * \brief virtual destructor
     */
    ~TCPServerApp() override = default;

private:
    /**
   * \brief Execute main function
   * \param args arguments from stdin
   * \return process code error
   */
    int main(const ArgVec& args) override;

    /**
    * \brief Load config file
    * \param self ownership
    */
    void initialize(Application& self) override;

    /**
     * \brief Configure internal log to use formatted pattern
     */
    void configureLogger();

    /**
     * \brief Retrieve max log size
     * \return Formatted log size. "1 M" is 1 Megabyte
     */
    boost::optional<std::string> getLogSize() const noexcept;

    /**
     * \brief Retrieve TCP Server port
     * \return Socket port from config file
     */
    boost::optional<unsigned> getPort() const noexcept;

    /**
     * \brief Retrieve log root directory
     * \return Log file directory
     */
    boost::optional<std::string> getLogRootDir() const noexcept;

    /**
     * \brief Get app configuration file path
     * \return Config path
     */
    Poco::Path configurationPath() const noexcept;

    /**
     * \brief Crete TCP Server Task based on configuration
     * \return Created task ready to be started
     */
    TCPServerTask* createTCPTask();

    Poco::AutoPtr<Poco::PatternFormatter> pattern_formatter_; /**< Pattern for log */
    Poco::AutoPtr<Poco::FormattingChannel> formatting_channel_; /**< Formatting Channel */
    Poco::AutoPtr<Poco::FileChannel> file_channel_; /**< File Channel */

    /**
     * \brief Retrieve some option from the configuration file
     * \param option Option name
     * \return Option value
     */
    template <typename T>
    boost::optional<T> getLexicalOption(const std::string& option) const
    {
        boost::optional<T> result;

        if (config().hasOption(option)) {
            result = boost::lexical_cast<T>(config().getString(option));
        }

        return result;
    }
};

#endif //TCPSERVER_TCPSERVERAPP_HPP
