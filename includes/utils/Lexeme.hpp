/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexeme.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 20:15:57 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/25 20:15:59 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace Lexer
{
	namespace Instruction
	{
	    enum ListOfInstructions
	    {
	    	PUSH = 0xfeed,
	    	POP,
	    	DUMP,
	    	ASSERT,
	    	ADD,
	    	SUB,
	    	MUL,
	    	DIV,
	    	MOD,
	    	PRINT,
	    	EXIT
	    };
	}
	namespace Operand
	{
		enum ListOfOperands
		{
			INT8 = 0xbeef,
    		INT16,
    		INT32,
    		FLOAT,
    		DOUBLE,
		};
	}

	class Lexeme
	{
	public:
		Lexeme();
		~Lexeme();
		Lexeme(const Lexeme &copy);
		Lexeme &operator=(const Lexeme &rvalue);

		Lexeme(const std::string &type, const std::string &rawValue="");
		int type() const;
		auto value() const;
	private:
		/*
		* Type of lexeme, i.e. Instruction, Operand
		*/
		int m_type;
		/*
		* Contain supportng data of that lexeme
		* Instruction and Operand types contain corr enum value,
		* Value type contain raw value
		*/
	    union {
	        int8_t 	m_int8;
	        int16_t m_int16;
	        int32_t m_int32;
	        float 	m_float;
	        double  m_double;
	    } m_raw;
	};
}
