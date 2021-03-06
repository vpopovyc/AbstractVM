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
#include <Parser.hpp>
#include <AVMException.hpp>
#include <iostream>

int main(const int ac, const char *av[])
{
    Lexer::Lexer lexer;

    try {
        lexer.analyze(ac, av);
        Parser parser(lexer.lexemes());

        auto abs = parser.abs();
        for (auto &node : abs) {
        	node();
        }
    } catch (AVMException &e) {
        std::cout << e.what() << std::endl;
    }

    // std::cout << lexer;
    return 0;
}
