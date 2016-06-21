/**
 * \file
 * \brief Declare TCP Server application
 */
#ifndef TCPSERVER_TCPSERVERAPP_HPP
#define TCPSERVER_TCPSERVERAPP_HPP

#include <Poco/Util/ServerApplication.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FileChannel.h>
#include <Poco/AutoPtr.h>
#include <Poco/Path.h>

/**
 * \brief Execute Server application
 */
class TCPServerApp : public Poco::Util::ServerApplication
{
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
     * \brief Get app configuration file path
     */
    Poco::Path configurationPath() const;

    Poco::AutoPtr<Poco::PatternFormatter> pattern_formatter_; /**< Pattern for log */
    Poco::AutoPtr<Poco::FormattingChannel> formatting_channel_; /**< Formatting Channel */
    Poco::AutoPtr<Poco::FileChannel> file_channel_; /**< File Channel */
};


#endif //TCPSERVER_TCPSERVERAPP_HPP
