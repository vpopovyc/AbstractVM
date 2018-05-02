/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:13:26 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/05/01 18:13:27 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OperandFactory.hpp>
#include <vector>

namespace OperandFactory 
{
	static IOperand const *createInt8(std::string const &value)
	{
		return new Operand<int8_t>(stoi(value), OperandType::INT8);
	}

	static IOperand const *createInt16(std::string const &value)
	{
		return new Operand<int16_t>(stoi(value), OperandType::INT16);
	}

	static IOperand const *createInt32(std::string const &value)
	{
		return new Operand<int32_t>(stoi(value), OperandType::INT32);
	}

	static IOperand const *createFloat(std::string const &value)
	{
		return new Operand<float>(stof(value), OperandType::FLOAT);
	}

	static IOperand const *createDouble(std::string const &value)
	{
		return new Operand<double>(stod(value), OperandType::DOUBLE);
	}

	IOperand const *createOperand(OperandType type, std::string const &value)
	{
		static const std::vector<std::function<IOperand const *(rawValue const &)>> factory
		{
			std::bind(createInt8, std::placeholders::_1),
			std::bind(createInt16, std::placeholders::_1),
			std::bind(createInt32, std::placeholders::_1),
			std::bind(createFloat, std::placeholders::_1),
			std::bind(createDouble, std::placeholders::_1)
		};

		int idx = type % OperandType::INT8;

		return factory[idx](value);
	}

	// IOperand const *createOperand(OperandType oldType, OperandType newType, rawValue const &oldValue)
	// {
	// 	rawValue newValue;

	// 	auto conv = [&newValue](auto &value) {
	// 		switch (newType)
	// 		{
	// 			case Lexer::Operand::INT8: newValue.m_int8 = value; break ;
	// 			case Lexer::Operand::INT16: newValue.m_int16 = value; break ;
	// 			case Lexer::Operand::INT32: newValue.m_int32 = value; break ;
	// 			case Lexer::Operand::FLOAT: newValue.m_float = value; break ;
	// 			case Lexer::Operand::DOUBLE: newValue.m_double = value; break ;
	// 			default: {}
	// 		}
	// 	};

	// 	switch (oldType)
	// 	{
	// 		case Lexer::Operand::INT8: conv(oldValue.m_int8); break;
	// 		case Lexer::Operand::INT16: conv(oldValue.m_int16); break;
	// 		case Lexer::Operand::INT32: conv(oldValue.m_int32); break;
	// 		case Lexer::Operand::FLOAT: conv(oldValue.m_float); break;
	// 		case Lexer::Operand::DOUBLE: conv(oldValue.m_double); break;
	// 		default: {}
	// 	}

	// 	return createOperand(newType, newValue);
	// }
}