/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:51:01 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/24 14:51:03 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>

class Lexer
{
    public:
        Lexer();
        ~Lexer();
        Lexer(const Lexer &copy);
        Lexer &operator=(const Lexer &rvalue);

        void analyzeFile(const int &ac, const char *av[]);
    private:
        void analyzeFileImpl(const std::ifstream &file);
};
