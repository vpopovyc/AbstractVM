/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:51:01 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/24 14:51:03 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <regex>
# include <string>
# include <fstream>
# include <Lexeme.hpp>


namespace Lexer
{

    class Lexer
    {
    public:
        Lexer();
        ~Lexer();
        Lexer(const Lexer &copy);
        Lexer &operator=(const Lexer &rvalue);
        friend std::ostream& operator<<(std::ostream& os, const Lexer& instr);

        void analyze(const int &ac, const char *av[]);
        std::vector<Lexeme> &lexemes();
    private:
        void analyzeImpl(std::function<bool (std::string&)> get_next_line);
        void matchType(const std::string &file);
        void dump() const;
    private:
        static const std::regex m_unaryRegex;
        static const std::regex m_binaryIntRegex;
        static const std::regex m_binaryFltRegex;
        static const std::regex m_skipLineRegex;
        static const std::regex m_EOIRegex;
        std::vector<Lexeme> m_lexemes;
    };
}