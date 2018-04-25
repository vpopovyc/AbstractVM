/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instructions.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 19:57:20 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/25 19:57:21 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

struct Instructions
{
    static ListOfInstructions stringToEnum(const std::string &typestr);
    static bool isValid(const ListOfInstructions &instr);
    friend std::ostream& operator<<(std::ostream& os, const ListOfInstructions& instr);
};