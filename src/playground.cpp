#include <iostream>
#include <string>

#include "definitions.h"

int main() {
    net::streambuf buf;

    std::ostream output_stream(&buf);

    output_stream << "Teste";


    std::istream input_stream(&buf);

    std::string message;

    std::getline(input_stream, message);

    std::cout << message << std::endl;

    return 0;
}