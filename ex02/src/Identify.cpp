#include "../include/Identify.hpp"
#include "../include/A.hpp"
#include "../include/B.hpp"
#include "../include/C.hpp"
#include <cstdlib>
#include <iostream>

Base	*generate(void)
{
	int	random = std::rand() % 3;

	switch (random)
	{
		case 0:
			std::cout << "generate(): A\n";
			return new A();
		case 1:
			std::cout << "generate(): B\n";
			return new B();
		default:
			std::cout << "generate(): C\n";
			return new C();
	}
}

void	identify(Base* p)
{
	if (p == 0)
	{
		std::cout << "identify(Base*): null pointer\n";
        return;
	}

	if (dynamic_cast<A *>(p))
		std::cout << "A\n";
	else if (dynamic_cast<B *>(p))
		std::cout << "B\n";
	else if (dynamic_cast<C *>(p))
		std::cout << "C\n";
	else
		std::cout << "Unknown" << std::endl;
}

void	identify(Base& p)
{
	try {
        (void)dynamic_cast<A &>(p);
        std::cout << "A\n";
        return;
    } catch (...) {}

	try {
        (void)dynamic_cast<B &>(p);
        std::cout << "B\n";
        return;
    } catch (...) {}

	try {
        (void)dynamic_cast<C &>(p);
        std::cout << "C\n";
        return;
    } catch (...) {}

	std::cout << "Unknown" << std::endl;
}