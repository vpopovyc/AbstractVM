#include <typeinfo>
#include <iostream>

class A
{
public:
		union {
			int ivalue;
			float fvalue;
			double dvalue;		
		} m_raw;

};

auto foo()
{
	A a;
	a.m_raw.ivalue = 1;
	return a.m_raw;
}

int main()
{
	auto raw = foo();
	std::cout << raw.ivalue << std::endl;
}
