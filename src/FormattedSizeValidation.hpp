/**
 * \file
 * \brief Declare Size Formatted Validation
 */

#ifndef TCPSERVER_FORMATTEDSIZEVALIDATION_HPP
#define TCPSERVER_FORMATTEDSIZEVALIDATION_HPP

#include <unordered_map>
#include <boost/regex.hpp>
#include <boost/optional.hpp>

/**
 * \brief Validates formatted size
 *        If the validation is refused,
 *        a exception is throwed
 * \param formatted_size Max file size
 */
class FormattedSizeValidation
{
    /**
    * \brief Expression to be matched
    * \return regex expression
    */
    static constexpr const char* group_expression() noexcept
    {
        return R"(^(\d{1,4})\s([M|k])$)";
    }

public:
    /**
     * \brief Convert to unsigned int
     * \param formatted_size String to be converted
     * \return If is valid, the converted value. Otherwise; None.
     */
    static boost::optional<unsigned> toUInt(const std::string& formatted_size) noexcept
    {
        boost::optional<unsigned> result;

        boost::smatch what;
        boost::regex regex(group_expression());
        if (boost::regex_search(formatted_size, what, regex)) {
            using binary_prefix = std::unordered_map<std::string, unsigned>;
            static const binary_prefix prefix = {{"k", 1} , {"M", 2}};
            constexpr auto multiplier = 1024u;

            result = std::stoul(what[0]) * prefix.at(what[1]) * multiplier;
        }

        return result;
    }

};

#endif //TCPSERVER_FORMATTEDSIZEVALIDATION_HPP
