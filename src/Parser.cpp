/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:18:58 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/05/02 18:18:59 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser.hpp>
#include <AVMException.hpp>
#include <OperandFactory.hpp>

Parser::Parser() {}
Parser::~Parser() {}
Parser::Parser(const Parser &copy) { *this = copy; }
Parser &Parser::operator=(const Parser &rvalue)
{
	m_operands = rvalue.m_operands;
	return *this;
}

std::vector<std::function<void()>> const &Parser::abs() const { return m_abs; }

Parser::Parser(std::vector<Lexer::Lexeme> lexemes)
{
	static const std::vector<std::function<void()>> instructions
	{
		std::bind([&](){ for (auto &op : m_operands) { std::cout << op->toString() << std::endl; } }),
		std::bind([&]() {
			if (m_operands.size() > 0) {
				m_operands.pop_back();
			} else {
				throw AVMException(Reason::POP_OF_EMPTY_STACK, "To pop you need to have values in stack");
			}
		})
	};

	auto createOperand = [&](int type, auto value) {
		switch (type)
		{
			case Lexer::Operand::INT8:   return OperandFactory::createOperand<int8_t>((OperandType)type, value.m_int8);
			case Lexer::Operand::INT16:  return OperandFactory::createOperand<int16_t>((OperandType)type, value.m_int16);
			case Lexer::Operand::INT32:  return OperandFactory::createOperand<int32_t>((OperandType)type, value.m_int32);
			case Lexer::Operand::FLOAT:  return OperandFactory::createOperand<float>((OperandType)type, value.m_float);
			case Lexer::Operand::DOUBLE: return OperandFactory::createOperand<double>((OperandType)type, value.m_double);
			default: throw AVMException(Reason::UNKNOWN_OPERAND, "Attemp to create unknown operand");
		}
	};

	for (size_t i = 0; i < lexemes.size(); i++)
	{
		if (lexemes[i].type() == Lexer::Instruction::PUSH) {
			m_operands.push_back(createOperand(lexemes[i+1].type(), lexemes[i+1].value()));
			lexemes.erase(lexemes.begin() + i, lexemes.begin() + i+1);
		}
	}

	for (size_t i = 0; i < lexemes.size(); i++)
	{
		int idx = Lexer::Instruction::POP % Lexer::Instruction::PUSH;

		m_abs.emplace_back(instructions[idx]);
	}	

}
