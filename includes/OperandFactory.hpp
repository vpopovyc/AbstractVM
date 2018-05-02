/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:13:37 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/05/01 18:13:38 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Operand.hpp>
#include <vector>
#include <iostream>

namespace OperandFactory
{
	template <typename T>
	IOperand const *createOperand(OperandType type, T const &value)
	{
		static const std::vector<std::function<IOperand const *(T const &)>> factory
		{
			std::bind([](T const &value){ return new Operand<int8_t>(value, OperandType::INT8);   }, std::placeholders::_1),
			std::bind([](T const &value){ return new Operand<int16_t>(value, OperandType::INT16); }, std::placeholders::_1),
			std::bind([](T const &value){ return new Operand<int32_t>(value, OperandType::INT32); }, std::placeholders::_1),
			std::bind([](T const &value){ return new Operand<float>(value, OperandType::FLOAT);   }, std::placeholders::_1),
			std::bind([](T const &value){ return new Operand<double>(value, OperandType::DOUBLE); }, std::placeholders::_1)
		};
		return factory[type](value);
	}
}
