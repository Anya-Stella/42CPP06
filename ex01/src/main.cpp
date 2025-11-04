#include <iostream>
#include "Serializer.hpp"

int main() {

	/*.define */
    Data data;
    data.name = "Alice";
    data.age = 42;

	/*.Serialize */
    std::cout << "Original pointer: " << &data << std::endl;
    uintptr_t raw = Serializer::serialize(&data);
    std::cout << "Serialized: " << raw << std::endl;

	/*.Deserialze */
    Data* ptr = Serializer::deserialize(raw);
    std::cout << "Deserialized pointer: " << ptr << std::endl;

	
    std::cout << "ptr->name = " << ptr->name << std::endl;
    std::cout << "ptr->age = " << ptr->age << std::endl;

    if (ptr == &data)
        std::cout << "Success: same pointer" << std::endl;
    else
        std::cout << "Failed: different pointer" << std::endl;

    return 0;
}
