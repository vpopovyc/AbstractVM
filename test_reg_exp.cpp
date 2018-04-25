/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reg_exp.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 17:38:37 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/24 20:24:20 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex>
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	string input;
	//regex integer("[[:space:]]*(push)[[:space:]]+(int8)\\([[:space:]]*([-]?[[:digit:]]+.[[:digit:]]+)[[:space:]]*\\)[[:space:]]*");
	
	// regex integer("\\s*(push)\\s+(int8|int16|int32)\\(\\s*([-]?\\d+\\.\\d+)\\s*\\)\\s*(?:;.*)?");
	//regex integer("[[:space:]]*(push)[[:space:]]+(int8|int16|int32)\\([[:space:]]*([-]?[[:digit:]]+.[[:digit:]]+)[[:space:]]*\\)[[:space:]]*");

	regex integer("\\s*(pop|dump|add|sub|mul|div|mod|print|exit)\\s*(?:;.*)?");

	while (true)
	{
		getline(cin, input);
		if (regex_match(input, integer))
		{
			cout << "match" << endl;
			cout << regex_replace(input, integer, "$1");
		}
		else
			cout << "no match" << endl;
	}

}

