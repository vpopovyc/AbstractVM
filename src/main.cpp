/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 15:42:40 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/24 15:42:42 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Lexer.hpp>
#include <AVMException.hpp>
#include <iostream>

int main(const int ac, const char *av[])
{
    Lexer lexer;

    try {
        lexer.analyzeFile(ac, av);
    } catch (AVMException &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
