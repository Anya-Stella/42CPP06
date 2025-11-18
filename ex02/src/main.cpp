#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Identify.hpp"

int main()
{
	// 一回だけ初期化
    std::srand(std::time(0));

    for (int i = 0; i < 10; ++i) {
        Base* p = generate();

        std::cout << "identify(Base*): ";
        identify(p);

        std::cout << "identify(Base&): ";
        identify(*p);

        delete p;
        std::cout << "------------------\n";
    }
}
