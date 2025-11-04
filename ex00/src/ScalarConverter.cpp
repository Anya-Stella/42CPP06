#include "./ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <cmath>



/*.name space (helper of helper) */
namespace {
	bool	isPrintableChar(int v){
		return (32 <= v && v <= 126);
	}
}

/*.default */
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter&) {}
ScalarConverter::~ScalarConverter() {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) { return *this; }

/*.judge */
bool ScalarConverter::isCharLiteral(const std::string &s, char &out)
{
	// 'a' ...
	if (s.size() == 3 && s[0] == '\'' && s[2] == '\'')
	{
		out = s[1];
		return true;
	}

	// one char( not a number )
	if (s.size() == 1 && !std::isdigit(static_cast<unsigned char>(s[0])))
	{
		out = s[0];
		return true;
	}

	return false;
}

bool ScalarConverter::isIntLiteral(const std::string& s, long &out)
{
	errno = 0;
    char* end = nullptr;
    long v = std::strtol(s.c_str(), &end, 10);

    if (errno == ERANGE) return false;
    if (end == s.c_str()) return false;
    if (*end != '\0') return false;

    out = v;
    return true;
}

bool ScalarConverter::isFloatLiteral(const std::string& s, float &out, bool &isPseudo)
{
	isPseudo = false;

	if (s == "nanf")  { out = std::numeric_limits<float>::quiet_NaN(); isPseudo = true; return true; }
    if (s == "+inff") { out = std::numeric_limits<float>::infinity();  isPseudo = true; return true; }
    if (s == "-inff") { out = -std::numeric_limits<float>::infinity(); isPseudo = true; return true; }

	// end by f?
	if (s.size() < 2 || s[s.size() - 1] != 'f')
		return false;
	
	// get core
	std::string core = s.substr(0, s.size() - 1);

	errno = 0;
    char* end = nullptr;
    float v = std::strtof(core.c_str(), &end);

    if (errno == ERANGE || *end != '\0')
		return false;
	
	out = v;
    return true;
}

bool ScalarConverter::isDoubleLiteral(const std::string& s, double &out, bool &isPseudo)
{
	isPseudo = false;

    if (s == "nan")  { out = std::numeric_limits<double>::quiet_NaN(); isPseudo = true; return true; }
    if (s == "+inf") { out = std::numeric_limits<double>::infinity();  isPseudo = true; return true; }
    if (s == "-inf") { out = -std::numeric_limits<double>::infinity(); isPseudo = true; return true; }

    errno = 0;
    char* end;
    double v = std::strtod(s.c_str(), &end);
    if (errno == ERANGE || *end != '\0')
        return false;

    out = v;
    return true;
}


/*.print */
void	ScalarConverter::printFromChar(char c)
{
	// char
	std::cout << "char: '" << c << "'" << std::endl;

	// int
	int	iv = static_cast<int>(c);
	std::cout << "int: " << iv << std::endl;

	// float.double(set pos of fix point
	float	fv = static_cast<float>(c);
	double	dv = static_cast<double>(c);
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << fv << "f" << std::endl;
	std::cout << "double: " << dv << std::endl;
}

void	ScalarConverter::printFromInt(long v)
{
	// char
	if (v < 0 || 127 < v)
		std::cout << "char: impossible" << std::endl;
	else if (!isPrintableChar(static_cast<int>(v)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(v)<< "'" << std::endl;
	
	// int
	if (v < INT_MIN || INT_MAX < v)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(v) << std::endl;

	// float.double
	// float.double(set pos of fix point
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << static_cast<float>(v) << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(v) << std::endl;	
}

void	ScalarConverter::printFromFloat(float f, bool isPseudo)
{
	// char(check limited)
	if (!std::isfinite(f) || f < 0.0f || 127.0f < f)
		std::cout << "char: impossible" << std::endl;
	else if (!isPrintableChar(static_cast<int>(f)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(f)<< "'" << std::endl;

	// int
	if (!std::isfinite(f) || f < static_cast<float>(INT_MIN) || static_cast<float>(INT_MAX) < f)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(f) << std::endl;
	
	// float
	if (isPseudo)
	{
		if (std::isnan(f))
			std::cout << "float: nanf" << std::endl;
		else if (std::isinf(f) && std::signbit(f))
			std::cout << "float: -inff" << std::endl;
		else	
			std::cout << "float: +inff" << std::endl;
	}
	else
	{
		std::cout << std::fixed << std::setprecision(1);
        std::cout << "float: " << f << "f" << std::endl;
	}

	// double
	double d = static_cast<double>(f);
	if (isPseudo)
	{
		if (std::isnan(d))
			std::cout << "double: nan" << std::endl;
        else if (std::isinf(d) && std::signbit(d))
			std::cout << "double: -inf" << std::endl;
        else
			std::cout << "double: +inf" << std::endl;
	}
	else
	{
		std::cout << std::fixed << std::setprecision(1);
        std::cout << "double: " << d << std::endl;
	}
}

void	ScalarConverter::printFromDouble(double d, bool isPseudo)
{
	// char
	if (!std::isfinite(d) || d < 0.0 || 127.0 < d)
		std::cout << "char: impossible" << std::endl;
	else if (!isPrintableChar(static_cast<int>(d)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;

	// int
	if (!std::isfinite(d) || d < static_cast<double>(INT_MIN) || static_cast<double>(INT_MAX) < d)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(d) << std::endl;

	// float
	if (isPseudo)
	{
		if (std::isnan(d))
			std::cout << "float: nanf" << std::endl;
		else if (std::isinf(d) && std::signbit(d))
			std::cout << "float: -inff" << std::endl;
		else	
			std::cout << "float: +inff" << std::endl;
	}
	else
	{
		float	f = static_cast<float>(d);
		std::cout << std::fixed << std::setprecision(1);
        std::cout << "float: " << f << "f" << std::endl;
	}

	// double
	if (isPseudo)
	{
		if (std::isnan(d))
			std::cout << "double: nan" << std::endl;
        else if (std::isinf(d) && std::signbit(d))
			std::cout << "double: -inf" << std::endl;
        else
			std::cout << "double: +inf" << std::endl;
	}
	else
	{
		std::cout << std::fixed << std::setprecision(1);
        std::cout << "double: " << d << std::endl;
	}
}

void	ScalarConverter::Invalid()
{
	std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}


/*.converter */
void	ScalarConverter::convert(const std::string &literal)
{
	char c; long iv; float fv; double dv;
	bool	isPseudo = false;

	if (isCharLiteral(literal, c)) {
        printFromChar(c);
        return;
    }
    if (isIntLiteral(literal, iv)) {
        printFromInt(iv);
        return;
    }
    if (isFloatLiteral(literal, fv, isPseudo)) {
        printFromFloat(fv, isPseudo);
        return;
    }
    if (isDoubleLiteral(literal, dv, isPseudo)) {
        printFromDouble(dv, isPseudo);
        return;
    }
	Invalid();
}
