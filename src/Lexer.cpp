/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:50:43 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/24 14:50:44 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Lexer.hpp>
#include <fstream>
#include <AVMException.hpp>

Lexer::Lexer() {}
Lexer::~Lexer() {}
Lexer::Lexer(const Lexer &copy) { *this = copy; }

Lexer &Lexer::operator=(const Lexer &rvalue)
{
    // Do assign
    (void)rvalue;
    return *this;
}

void Lexer::analyzeFileImpl(const std::ifstream &file)
{
    (void)file;
    throw AVMException(Reason::LEXER_ERROR, "Test error");
}

void Lexer::analyzeFile(const int &ac, const char *av[])
{
    if (ac != 2) {
        throw AVMException(Reason::INPUT_ERROR, "Bad input o_o");
    }
    std::ifstream infile(av[1]);

    if (!infile.is_open()) {
        throw AVMException(Reason::INPUT_ERROR, "Bad filename *_*");
    }

    analyzeFileImpl(infile);
}
