#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <literal>" << std::endl;
        std::cerr << "Examples:\n"
                  << "  ./convert 0\n"
                  << "  ./convert a\n"
                  << "  ./convert 'a'\n"
                  << "  ./convert 42\n"
                  << "  ./convert 42.0f\n"
                  << "  ./convert 42.0\n"
                  << "  ./convert nan\n"
                  << "  ./convert nanf\n"
                  << "  ./convert +inff\n"
                  << "  ./convert -inf\n";
        return 1;
    }

    try
    {
        ScalarConverter::convert(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
