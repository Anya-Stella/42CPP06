#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter
{
private:
	/*.default static class */
	ScalarConverter();
	ScalarConverter(const ScalarConverter &other);
	ScalarConverter &operator=(const ScalarConverter &rhs);
	~ScalarConverter();

	/*.helper */
	static bool isCharLiteral(const std::string &s, char &out);
	static bool isIntLiteral(const std::string& s, long &out);
	static bool isFloatLiteral(const std::string& s, float &out, bool &isPseudo);
    static bool isDoubleLiteral(const std::string& s, double &out, bool &isPseudo);

	static void printFromChar(char c);
    static void printFromInt(long v);
    static void printFromFloat(float f, bool isPseudo);
    static void printFromDouble(double d, bool isPseudo);
	static void	Invalid();
public:
	static void	convert(const std::string &literal);
};
#endif