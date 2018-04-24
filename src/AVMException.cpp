/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVMException.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 15:14:54 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/24 15:14:55 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <AVMException.hpp>

AVMException::AVMException() {}
AVMException::~AVMException() {}
AVMException::AVMException(const AVMException &copy) { *this = copy; }

AVMException &AVMException::operator=(const AVMException &rvalue)
{
    m_reason = rvalue.m_reason;
    m_details = rvalue.m_details;
    return *this;
}

AVMException::AVMException(const Reason &reason, const std::string &details)
{
    m_reason = reason;
    m_details = details;
}

const char *AVMException::what() const noexcept
{
    std::string what;
    auto addToWhat = [&](const std::string &text){ what += text; };

    switch(m_reason)
    {
        case Reason::LEXER_ERROR: addToWhat("Lexer error: "); break;
        case Reason::INPUT_ERROR: addToWhat("Input error: "); break;
        default: addToWhat("Unknown error: ");
    }

    what += m_details;
    return what.c_str();
}
