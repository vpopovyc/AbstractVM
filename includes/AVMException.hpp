/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVMException.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 15:14:45 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/24 15:14:46 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <exception>

enum class Reason
{
    INPUT_ERROR,
    LEXER_ERROR,
    UNKNOWN_OPERAND,
    DIVISION_BY_ZERO,
    MODULO_BY_ZERO,
    POP_OF_EMPTY_STACK,
    OVERFLOW_INT8_ERROR,
    UNDERFLOW_INT8_ERROR,
    OVERFLOW_INT16_ERROR,
    UNDERFLOW_INT16_ERROR,
    OVERFLOW_INT32_ERROR,
    UNDERFLOW_INT32_ERROR,
    OVERFLOW_FLT_ERROR,
    UNDERFLOW_FLT_ERROR,
    OVERFLOW_DBL_ERROR,
    UNDERFLOW_DBL_ERROR
};

class AVMException : public std::exception
{
public:
    AVMException(const Reason &reason, const std::string &details);
    ~AVMException();
    AVMException(const AVMException &copy);
    AVMException &operator=(const AVMException &rvalue);

    const char *what() const noexcept;
private:
    AVMException();
    Reason m_reason;
    std::string m_details;
};
