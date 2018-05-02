/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:57:52 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/05/01 16:57:53 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Lexeme.hpp>

using OperandType=Lexer::Operand::ListOfOperands;

class IOperand {
public:
	virtual int getPrecision(void) const = 0;
	virtual OperandType getType(void) const = 0;
	virtual IOperand const *operator+(IOperand const &rhs) const = 0;
	// virtual IOperand const *operator-(IOperand const &rhs) const = 0;
	// virtual IOperand const *operator*(IOperand const &rhs) const = 0;
	// virtual IOperand const *operator/(IOperand const &rhs) const = 0;
	// virtual IOperand const *operator%(IOperand const &rhs) const = 0;
	// virtual std::string const & toString( void ) const = 0;
	virtual ~IOperand( void ) {}
};