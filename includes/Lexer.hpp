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

using Instruction=Instructions::ListOfInstructions;

class Lexer
{
public:
    Lexer();
    ~Lexer();
    Lexer(const Lexer &copy);
    Lexer &operator=(const Lexer &rvalue);
    friend std::ostream& operator<<(std::ostream& os, const Lexer& instr);

    void analyzeFile(const int &ac, const char *av[]);
private:
    void analyzeFileImpl(std::ifstream &file);
    void matchType(const std::string &file);
    void dump() const;
private:
    static const std::regex m_noValueRegex;
    std::vector<Instruction> m_lexemes;
};
