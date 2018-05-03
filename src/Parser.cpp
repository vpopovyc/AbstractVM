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
#include <cstdlib>
#include <AVMException.hpp>
#include <OperandFactory.hpp>

Parser::Parser() {}
Parser::~Parser() {}
Parser::Parser(const Parser &copy) { *this = copy; }
Parser &Parser::operator=(const Parser &rvalue)
{
	m_operands = rvalue.m_operands;
	m_execution_stack = rvalue.m_execution_stack;
	return *this;
}

std::vector<std::function<void()>> const &Parser::abs() const { return m_abs; }

Parser::Parser(std::vector<Lexer::Lexeme> lexemes)
{
	static const std::vector<std::function<void()>> instructions
	{
		std::bind([&]() {
			m_execution_stack.push_front(m_operands[0]);
			m_operands.pop_front();
		}),
		std::bind([&]() {
			if (m_execution_stack.size() > 0) {
				m_execution_stack.pop_front();
			} else {
				throw AVMException(Reason::POP_OF_EMPTY_STACK,
								   "To pop you need to have values in stack");
			}
		}),
		std::bind([&]() {
			for (auto &op : m_execution_stack) {
				std::cout << op->toString() << std::endl;
			}
		}),
		std::bind([&]() {
			auto *op = m_operands[0];
			
			if (*m_execution_stack[0] == *op) {
				m_operands.pop_front();
			} else {
				throw AVMException(Reason::ASSERTION_FAILLURE,
								   op->toString() + " and " + m_execution_stack[0]->toString());
			}
		}),
		std::bind([&]() {
			if (m_execution_stack.size() < 2) {
				throw AVMException(Reason::NO_ARGS_FOR_BIN_EXPR,
					               "Current stack size: " + std::to_string(m_execution_stack.size()));
			}

			auto *op1 = m_execution_stack[0];
			auto *op2 = m_execution_stack[1];
			m_execution_stack.pop_front();
			m_execution_stack.pop_front();
			m_execution_stack.push_front(*op1 + *op2);
		}),
		std::bind([&]() {
			if (m_execution_stack.size() < 2) {
				throw AVMException(Reason::NO_ARGS_FOR_BIN_EXPR,
					               "Current stack size: " + std::to_string(m_execution_stack.size()));
			}

			auto *op1 = m_execution_stack[0];
			auto *op2 = m_execution_stack[1];
			m_execution_stack.pop_front();
			m_execution_stack.pop_front();
			m_execution_stack.push_front(*op1 - *op2);
		}),
		std::bind([&]() {
			if (m_execution_stack.size() < 2) {
				throw AVMException(Reason::NO_ARGS_FOR_BIN_EXPR,
					               "Current stack size: " + std::to_string(m_execution_stack.size()));
			}

			auto *op1 = m_execution_stack[0];
			auto *op2 = m_execution_stack[1];
			m_execution_stack.pop_front();
			m_execution_stack.pop_front();
			m_execution_stack.push_front(*op1 * *op2);
		}),
		std::bind([&]() {
			if (m_execution_stack.size() < 2) {
				throw AVMException(Reason::NO_ARGS_FOR_BIN_EXPR,
					               "Current stack size: " + std::to_string(m_execution_stack.size()));
			}

			auto *op1 = m_execution_stack[0];
			auto *op2 = m_execution_stack[1];
			m_execution_stack.pop_front();
			m_execution_stack.pop_front();
			m_execution_stack.push_front(*op1 / *op2);
		}),
		std::bind([&]() {
			if (m_execution_stack.size() < 2) {
				throw AVMException(Reason::NO_ARGS_FOR_BIN_EXPR,
					               "Current stack size: " + std::to_string(m_execution_stack.size()));
			}

			auto *op1 = m_execution_stack[0];
			auto *op2 = m_execution_stack[1];
			m_execution_stack.pop_front();
			m_execution_stack.pop_front();
			m_execution_stack.push_front(*op1 % *op2);
		}),
		std::bind([&]() {
			if (m_execution_stack.size() == 0) {
				throw AVMException(Reason::EMPTY_STACK,
					               "No value to print");
			}

			auto *op = m_execution_stack[0];
			if (op->getType() != Lexer::Operand::INT8) {
				throw AVMException(Reason::PRINT_OF_NOT_CHAR,
					               "Value may exceed US-ASCII bounds");
			}
			std::cout << (dynamic_cast<const Operand<int8_t> *>(op)->getData()) << std::endl;
		}),
		std::bind([&]() {
			exit(EXIT_SUCCESS);
		}),
	};

	auto createOperand = [&](int type, auto value) {
		switch (type)
		{
			case Lexer::Operand::INT8:   return OperandFactory::createOperand<int8_t>((OperandType)type, value.m_int8);
			case Lexer::Operand::INT16:  return OperandFactory::createOperand<int16_t>((OperandType)type, value.m_int16);
			case Lexer::Operand::INT32:  return OperandFactory::createOperand<int32_t>((OperandType)type, value.m_int32);
			case Lexer::Operand::FLOAT:  return OperandFactory::createOperand<float>((OperandType)type, value.m_float);
			case Lexer::Operand::DOUBLE: return OperandFactory::createOperand<double>((OperandType)type, value.m_double);
			default: throw AVMException(Reason::UNKNOWN_OPERAND,
				                        "Attemp to create unknown operand");
		}
	};

	if (lexemes.back().type() != Lexer::Instruction::EXIT) {
		throw AVMException(Reason::EXIT_MISSING,
			               "You should provide exit instruction as last instruction");
	}

	for (size_t i = 0; i < lexemes.size(); i++)
	{
		if (lexemes[i].type() == Lexer::Instruction::PUSH) {
			m_operands.push_back(createOperand(lexemes[i+1].type(), lexemes[i+1].value()));
			lexemes.erase(lexemes.begin() + i+1);
		} else if (lexemes[i].type() == Lexer::Instruction::ASSERT) {
			m_operands.push_back(createOperand(lexemes[i+1].type(), lexemes[i+1].value()));
			lexemes.erase(lexemes.begin() + i+1);
		}
	}

	for (size_t i = 0; i < lexemes.size(); i++)
	{
		int idx = lexemes[i].type() % Lexer::Instruction::PUSH;

		m_abs.emplace_back(instructions[idx]);
	}	

}
