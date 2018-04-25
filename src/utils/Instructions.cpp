/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instructions.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 19:58:04 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/25 19:58:05 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Instructions.hpp>

using Instruction=Instructions::ListOfInstructions;

Instruction Instructions::stringToEnum(const std::string &typestr)
{
    if (typestr == "push")   return Instruction::PUSH;
    if (typestr == "pop")    return Instruction::POP;
    if (typestr == "dump")   return Instruction::DUMP;
    if (typestr == "assert") return Instruction::ASSERT;
    if (typestr == "add")    return Instruction::ADD;
    if (typestr == "sub")    return Instruction::SUB;
    if (typestr == "mul")    return Instruction::MUL;
    if (typestr == "div")    return Instruction::DIV;
    if (typestr == "mod")    return Instruction::MOD;
    if (typestr == "print")  return Instruction::PRINT;
    if (typestr == "exit")   return Instruction::EXIT;
    return Instruction::NONE;
}

std::ostream& operator<<(std::ostream& os, const Instruction& instr)  
{
    switch(instr) {
        case Instruction::PUSH:   os << "push"; break;
        case Instruction::POP:    os << "pop"; break;
        case Instruction::DUMP:   os << "dump"; break;
        case Instruction::ASSERT: os << "assert"; break;
        case Instruction::ADD:    os << "add"; break;
        case Instruction::SUB:    os << "sub"; break;
        case Instruction::MUL:    os << "mul"; break;
        case Instruction::DIV:    os << "div"; break;
        case Instruction::MOD:    os << "mod"; break;
        case Instruction::PRINT:  os << "print"; break;
        case Instruction::EXIT:   os << "exit"; break;
        default:                  os << "None";
    }
    return os;  
}  

bool Instructions::isValid(const Instruction &instr)
{
    return instr != Instruction::NONE;
}