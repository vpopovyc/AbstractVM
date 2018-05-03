/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:19:10 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/05/02 18:19:12 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <deque>
#include <Lexer.hpp>
#include <IOperand.hpp>

class Parser 
{
public:
	~Parser();
	Parser(const Parser &copy);
	Parser &operator=(const Parser &rvalue);
	
	Parser(const std::vector<Lexer::Lexeme> lexemes);

	std::vector<std::function<void()>> const &abs() const;

private:
	Parser();
	std::deque<IOperand const *> m_operands;
	std::deque<IOperand const *> m_execution_stack;
	std::vector<std::function<void(void)>> m_abs;
};
