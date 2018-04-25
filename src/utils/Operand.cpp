/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandType.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 19:55:30 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/25 19:55:31 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Operand.hpp>

using OperandType=OperandTypes::ListOfOperandTypes;

OperandType OperandTypes::toEnum(const std::string &typestr)
{
    if (typestr == "int8")   return OperandType::Int8;
    if (typestr == "in16")   return OperandType::Int16;
    if (typestr == "int32")  return OperandType::Int32;
    if (typestr == "float")  return OperandType::Float;
    if (typestr == "double") return OperandType::Double;
    return OperandType::NONE;
}

std::ostream& operator<<(std::ostream& os, const OperandType& instr)  
{
    switch(instr)
    {
        case OperandType::Int8:   os << ""; break;
        case OperandType::Int16:  os << ""; break;
        case OperandType::Int32:  os << ""; break;
        case OperandType::Float:  os << ""; break;
        case OperandType::Double: os << ""; break;
        default:                  os << "";
    }
    return os;
}  

bool OperandTypes::isValid(const OperandType &instr)
{
    return instr != OperandType::NONE;
}