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
		return *this;
	}

	Lexeme::Lexeme(const std::string &typestr, const std::string &rawValue="")
	{
		int type = 0
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
	    if (typestr == "print")  type = Instruction::PRINT;
	    if (typestr == "exit")   type = Instruction::EXIT;
	    // ops
        if (typestr == "int8")   type = OperandType::Int8;
	    if (typestr == "in16")   type = OperandType::Int16;
	    if (typestr == "int32")  type = OperandType::Int32;
	    if (typestr == "float")  type = OperandType::Float;
	    if (typestr == "double") type = OperandType::Double;

	    if (type == 0)
	    	// Throw
	    else
	    	m_type = type;
	    	// LEFT HERE
	    // U WANTED TO COMPLETE SWICTH AND ADD LEXEMS TO Lexer
	    switch(type)
	    {
	    	case OperandType::Int8:    m_raw.m_int8 =
	    	case OperandType::Int16:   m_raw.m_int16 = 
	    	case OperandType::Int32:   m_raw.m_int32 = 
	    	case OperandType::Float:   m_raw.m_float = 
	    	case OperandType::Double:  m_raw.m_double = 
	    }
	}

	int Lexeme::type() const
	{
		return m_type;
	}

	auto Lexeme::value() const
	{
		return m_raw;
	}

}
