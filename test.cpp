// #include <typeinfo>
#include <iostream>
#include <cmath>
// #include <cfloat>
// #include <sstream>
// #include <exception>
// #include <string>
// #include <Lexeme.hpp>
// #include <AVMException.hpp>
// #include <functional>

#include <Operand.hpp>
#include <OperandFactory.hpp>

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;

	auto *a = OperandFactory::createOperand<float>(OperandType::FLOAT, 2.05);
	auto *b = OperandFactory::createOperand<float>(OperandType::FLOAT, 2.05);
	try {
		{
			auto *c = (*a + *b);
			std::cout << c->toString() << std::endl;
		}
		{
			auto *c = (*a - *b);
			std::cout << c->toString() << std::endl;
		}
		{
			auto *c = (*a * *b);
			std::cout << c->toString() << std::endl;
		}
		{
			auto *c = (*a / *b);
			std::cout << c->toString() << std::endl;
		}
	} catch (AVMException &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		{
			auto *c = (*a % *b);
			std::cout << c->toString() << std::endl;
		}
	} catch (AVMException &e) {
		std::cout << e.what() << std::endl;
	}

	// double a = 2.05;
	// double b = 2.0;

	// std::cout << a/b << std::endl;
}
