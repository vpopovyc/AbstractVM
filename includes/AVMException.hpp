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
    LEXER_ERROR
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
