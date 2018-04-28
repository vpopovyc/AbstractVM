#include <typeinfo>
#include <iostream>
#include <cfloat>
#include <sstream>
#include <exception>
#include <string>
#include <Lexeme.hpp>
#include <AVMException.hpp>
#include <functional>

int main(int ac, char *av[])
{

	try {
		Lexer::Lexeme a(av[1], av[2]);
		std::cout << a << std::endl;
	} catch (AVMException &e) {
		std::cout << e.what() << std::endl;
	}
}
