/**
 * \file
 * \brief Variadic logger
 *
 *        A modern printf, with embedded type deduction
 */

#ifndef TCPSERVER_VARIADICLOGGER_HPP
#define TCPSERVER_VARIADICLOGGER_HPP

#include <sstream>
#include <utility>

/**
 * \brief Fill the output stream with T value
 * \param oss Output stream
 * \param t Any value
 */
template <typename T>
void log(std::ostringstream& oss, T&& t)
{
    oss << t;
}

/**
 * \brief Unpack variadic template to pop the head
 * \param oss Output stream
 * \param first Head
 * \param rest Body
 */
template <typename First, typename... Rest>
void log(std::ostringstream& oss, First&& first, Rest&&... rest)
{
    log(oss, std::forward<First>(first));
    log(oss, std::forward<Rest>(rest)...);
}

/**
 * \brief Process variadic template as argument list to logger
 */
template <typename... Args>
void VariadicLogger(std::ostringstream& oss, Args&&... args)
{
    log(oss, std::forward<Args>(args)...);
}

#endif //TCPSERVER_VARIADICLOGGER_HPP
