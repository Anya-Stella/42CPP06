#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <cstdint>
#include "Data.hpp"

class Serializer
{
private:
/*.default */
	Serializer();
	Serializer(const Serializer &other);
	Serializer	&operator=(const Serializer &rhs);
	~Serializer();
public:
	static	uintptr_t serialize(Data* ptr);
	static	Data* deserialize(uintptr_t raw);
};
#endif