/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexeme.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 20:44:03 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/25 20:44:04 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Lexeme.hpp>
#include <sstream>
#include <cstdint>
#include <cfloat>
#include <AVMException.hpp>
#include <functional>

namespace Lexer
{
    Lexeme::Lexeme() {}
    Lexeme::~Lexeme() {}
    Lexeme::Lexeme(const Lexeme &copy)
    {
        *this = copy;
    }
    Lexeme &Lexeme::operator=(const Lexeme &rvalue)
    {
        m_type = rvalue.m_type;
        m_raw = rvalue.m_raw;
        return *this;
    }

    Lexeme::Lexeme(const std::string &typestr, const std::string &rawValue)
    {
        int type = -1;
        // instr
        if (typestr == "push")   type = Instruction::PUSH;
        if (typestr == "pop")    type = Instruction::POP;
        if (typestr == "dump")   type = Instruction::DUMP;
        if (typestr == "assert") type = Instruction::ASSERT;
        if (typestr == "add")    type = Instruction::ADD;
        if (typestr == "sub")    type = Instruction::SUB;
        if (typestr == "mul")    type = Instruction::MUL;
        if (typestr == "div")    type = Instruction::DIV;
        if (typestr == "mod")    type = Instruction::MOD;
        if (typestr == "square") type = Instruction::SQUARE;
        if (typestr == "sqrt")   type = Instruction::SQRT;
        if (typestr == "log")    type = Instruction::LOG;
        if (typestr == "log10")  type = Instruction::LOG10;
        if (typestr == "abs")    type = Instruction::ABS;
        if (typestr == "print")  type = Instruction::PRINT;
        if (typestr == "exit")   type = Instruction::EXIT;
        // ops
        if (typestr == "int8")   type = Operand::INT8;
        if (typestr == "int16")   type = Operand::INT16;
        if (typestr == "int32")  type = Operand::INT32;
        if (typestr == "float")  type = Operand::FLOAT;
        if (typestr == "double") type = Operand::DOUBLE;

        if (type == -1){
            throw AVMException(Reason::LEXER_ERROR, "Invalid instruction");
        } else {
            m_type = type;
        }

        initValue(rawValue);
    }

    void Lexeme::initValue(const std::string &rawValue)
    {
        auto from = [](auto &c, auto ub, auto lb, auto ovr, auto unr) {
            auto cValue = c();
            if (cValue > ub) {
                throw AVMException(ovr, "Assign: " + std::to_string(cValue));
            } 
            if (cValue < lb) {
                throw AVMException(unr, "Assign: " + std::to_string(cValue));
            }
            return cValue;
        };

        auto dcFunc = std::bind([&rawValue]() {
            try {
                return stoll(rawValue);
            } catch (const std::out_of_range& e) {
                throw AVMException(Reason::LEXER_ERROR, "Out of range error");
            }
        });

        auto fpFunc = std::bind([&rawValue]() {
            try {
                return stold(rawValue);
            } catch (const std::out_of_range& e) {
                throw AVMException(Reason::LEXER_ERROR, "Out of range error");
            }
        });

        switch(m_type)
        {
            case Operand::INT8:
            {
                m_raw.m_int8 = from(dcFunc, INT8_MAX, INT8_MIN, Reason::OVERFLOW_INT8_ERROR, Reason::UNDERFLOW_INT8_ERROR);
                break;
            }
            case Operand::INT16:
            {
                m_raw.m_int16 = from(dcFunc, INT16_MAX, INT16_MIN, Reason::OVERFLOW_INT16_ERROR, Reason::UNDERFLOW_INT16_ERROR);
                break;
            }
            case Operand::INT32:
            {
                m_raw.m_int32 = from(dcFunc, INT32_MAX, INT32_MIN, Reason::OVERFLOW_INT32_ERROR, Reason::UNDERFLOW_INT32_ERROR);
                break;
            }
            case Operand::FLOAT:
            {
                m_raw.m_float = from(fpFunc, FLT_MAX, -FLT_MAX, Reason::OVERFLOW_FLT_ERROR, Reason::UNDERFLOW_FLT_ERROR);
                break;
            }
            case Operand::DOUBLE:
            {
                m_raw.m_double = from(fpFunc, DBL_MAX, -DBL_MAX, Reason::OVERFLOW_DBL_ERROR, Reason::UNDERFLOW_DBL_ERROR);
                break;
            }
        }
    }

    int Lexeme::type() const
    {
        return m_type;
    }

    u_rawBuff Lexeme::value() const
    {
        return m_raw;
    }

    std::ostream &operator<<(std::ostream &os, const Lexeme &lexeme)
    {
        std::string res;

        res += "Lexeme type: ";
        switch(lexeme.type()) {
            case Instruction::PUSH:   res += "push"; break;
            case Instruction::POP:    res += "pop"; break;
            case Instruction::DUMP:   res += "dump"; break;
            case Instruction::ASSERT: res += "assert"; break;
            case Instruction::ADD:    res += "add"; break;
            case Instruction::SUB:    res += "sub"; break;
            case Instruction::MUL:    res += "mul"; break;
            case Instruction::DIV:    res += "div"; break;
            case Instruction::MOD:    res += "mod"; break;
            case Instruction::PRINT:  res += "print"; break;
            case Instruction::EXIT:   res += "exit"; break;
            case Operand::INT8:       res += "int8"; break;
            case Operand::INT16:      res += "int16"; break;
            case Operand::INT32:      res += "int32"; break;
            case Operand::FLOAT:      res += "float"; break;
            case Operand::DOUBLE:     res += "double"; break;
        }

        auto printValue = [&](auto value) {
            res += " value: " + std::to_string(value);
        };

        switch(lexeme.type()) {
            case Operand::INT8:   printValue(lexeme.value().m_int8); break;
            case Operand::INT16:  printValue(lexeme.value().m_int16); break;
            case Operand::INT32:  printValue(lexeme.value().m_int32); break;
            case Operand::FLOAT:  printValue(lexeme.value().m_float); break;
            case Operand::DOUBLE: printValue(lexeme.value().m_double); break;
        }   

        os << res;
        return os;
    }
}
