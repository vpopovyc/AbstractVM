/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandType.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 19:47:05 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/25 19:47:06 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

struct OperandType
{
    enum ListOfOperandTypes
    {
    	Int8,
    	Int16,
    	Int32,
    	Float,
    	Double,
    	NONE
    };

    ListOfOperandTypes toEnum(const std::string &typestr);
    bool isValid(const ListOfOperandTypes &instr);
    friend std::ostream& operator<<(std::ostream& os, const ListOfOperandTypes& instr);
};
