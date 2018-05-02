// #include <typeinfo>
#include <iostream>
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
	// int val = 42;
	// int val2 = INT32_MIN;
	(void)ac;
	(void)av;

	auto *a = OperandFactory::createOperand<double>(OperandType::DOUBLE, DBL_MAX);
	auto *b = OperandFactory::createOperand<double>(OperandType::DOUBLE, DBL_MAX);
	try {
		auto *c = (*a + *b);
		std::cout << c->getType() << std::endl;
	} catch (AVMException &e) {
		std::cout << e.what() << std::endl;
	}
}
