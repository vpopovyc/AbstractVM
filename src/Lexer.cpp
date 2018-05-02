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
#include <iostream>
#include <fstream>
#include <AVMException.hpp>

namespace Lexer
{
    Lexer::Lexer() {}
    Lexer::~Lexer() {}
    Lexer::Lexer(const Lexer &copy) { *this = copy; }
    Lexer &Lexer::operator=(const Lexer &rvalue)
    {
        m_lexemes = rvalue.m_lexemes;
        return *this;
    }
    std::ostream& operator<<(std::ostream& os, const Lexer& instr)
    {
        instr.dump();
        os << std::endl;
        return os;
    }

    const std::regex Lexer::m_unaryRegex("\\s*(pop|dump|add|sub|mul|div|mod|print|exit)\\s*(?:;.*)?");
    const std::regex Lexer::m_binaryIntRegex("\\s*(push|assert)\\s+(int8|int16|int32)\\(\\s*([-]?\\d+)\\s*\\)\\s*(?:;.*)?");
    const std::regex Lexer::m_binaryFltRegex("\\s*(push|assert)\\s+(float|double)\\(\\s*([-]?\\d+\\.\\d+)\\s*\\)\\s*(?:;.*)?");
    const std::regex Lexer::m_skipLineRegex("(?:(?:\\s*)?(?:;.*)?)?");
    const std::regex Lexer::m_EOIRegex("(?:\\s*)?(?:;;)+(?:\\s*)?");

    void Lexer::analyzeImpl(std::function<bool (std::string&)> get_next_line)
    {
        auto isUnaryInst =     [](auto &line) { return std::regex_match(line, m_unaryRegex); };
        auto isBinaryIntInst = [](auto &line) { return std::regex_match(line, m_binaryIntRegex); };
        auto isBinaryFltInst = [](auto &line) { return std::regex_match(line, m_binaryFltRegex); };
        auto isSkipLine =      [](auto &line) { return std::regex_match(line, m_skipLineRegex); };
        auto unaryInstFrom =   [](auto &line) { return std::regex_replace(line, m_unaryRegex, "$1"); };
        auto binaryIntInst =   [](auto &line) { return std::regex_replace(line, m_binaryIntRegex, "$1"); };
        auto binaryFltInst =   [](auto &line) { return std::regex_replace(line, m_binaryFltRegex, "$1"); };
        auto intArgs =         [](auto &line) { return std::make_pair(std::regex_replace(line, m_binaryIntRegex, "$2"),
                                                                      std::regex_replace(line, m_binaryIntRegex, "$3")); };
        auto fltArgs =         [](auto &line) { return std::make_pair(std::regex_replace(line, m_binaryFltRegex, "$2"),
                                                                      std::regex_replace(line, m_binaryFltRegex, "$3")); };

        size_t lineIdx = 0;
        std::string line;

        while(get_next_line(line))
        {
            ++lineIdx;
            try {
                if (isSkipLine(line)) {
                    continue ;
                } else if (isUnaryInst(line)) {
                    m_lexemes.emplace_back(unaryInstFrom(line));
                } else if (isBinaryIntInst(line)) {
                    m_lexemes.emplace_back(binaryIntInst(line));
                    auto &&args = intArgs(line);
                    m_lexemes.emplace_back(args.first, args.second);
                } else if (isBinaryFltInst(line)) {
                    m_lexemes.emplace_back(binaryFltInst(line));
                    auto &&args = fltArgs(line);
                    m_lexemes.emplace_back(args.first, args.second);
                } else {
                    throw AVMException(Reason::LEXER_ERROR, "Invalid syntax:\n\t" + line);
                }
            } catch (AVMException &e) {
                std::cout << "Line: " << lineIdx << ": " << e.what() << std::endl;
            }
        }
    }

    void Lexer::analyze(const int &ac, const char *av[])
    {
        if (ac == 1) {
            auto f = [](std::string &line) {
                if (std::getline(std::cin, line)) {
                    return !std::regex_match(line, m_EOIRegex);
                } else {
                    if (feof(stdin)) {
                        clearerr(stdin);
                        std::cin.clear();
                        return true;
                    }
                    return false;
                }
            };

            analyzeImpl(f);
        } else if (ac == 2) {
            std::ifstream infile(av[1]);

            if (!infile.is_open()) {
                throw AVMException(Reason::INPUT_ERROR, "Bad filename *_*");
            }
            auto f = [&infile](std::string &line) {
                if (std::getline(infile, line))
                    return true;
                else
                    return false;
            };

            analyzeImpl(f);
        } else {
            throw AVMException(Reason::INPUT_ERROR, "Bad input o_o");
        }
    }

    void Lexer::dump() const
    {
        std::cout << "~~~~ Lexemes Dump ~~~~" << std::endl;  
        for (auto &lexeme : m_lexemes) {
                std::cout << lexeme << std::endl;
        }
        std::cout << "~~~~ Lexemes Dump ~~~~";  
    }
}
