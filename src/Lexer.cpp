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

using Instruction=Instructions::ListOfInstructions;

Lexer::Lexer() {}
Lexer::~Lexer() {}
Lexer::Lexer(const Lexer &copy) { *this = copy; }
Lexer &Lexer::operator=(const Lexer &rvalue)
{
    // Do assign
    (void)rvalue;
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Lexer& instr)
{
    instr.dump();
    os << std::endl;
    return os;
}

const std::regex Lexer::m_noValueRegex("\\s*(pop|dump|add|sub|mul|div|mod|print|exit)\\s*(?:;.*)?");

void Lexer::analyzeFileImpl(std::ifstream &file)
{
    std::string line;

    auto matchRegex = [&line](const std::regex &exp) -> Instruction {
        if (std::regex_match(line, exp)) {
            std::string instructionstr = std::regex_replace(line, exp, "$1");
            return Instructions::stringToEnum(instructionstr);
        }
        return Instruction::NONE;
    };

    bool errorHit = false;
    while(std::getline(file, line))
    {
        Instruction wInstr;
        wInstr = matchRegex(m_noValueRegex);
        if (Instructions::isInstrValid(wInstr)) {
            m_instructions.push_back(wInstr);
        } else {
            errorHit = true;
        }
    }
    if (errorHit) {
        // TODO: More meaningfull err msg
        throw AVMException(Reason::LEXER_ERROR, "Multiple errors :(");
    }
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

void Lexer::dump() const
{
    std::cout << "~~~~ Lexemes Dump ~~~~" << std::endl;  
    for (auto &instruction : m_instructions) {
            std::cout << instruction << std::endl;
    }
    std::cout << "~~~~ Lexemes Dump ~~~~" << std::endl;  
}

