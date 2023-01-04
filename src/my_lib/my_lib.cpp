#include <iostream>

#include "my_lib.h"


unsigned int Factorial( unsigned int number ) {
    if(number < 0)
        throw std::runtime_error("Can't compute factorial of a negative number");
    return number <= 1 ? 1 : Factorial(number-1)*number;
}

void print_hello_world(){
    std::cout << "Hello world \n";
}
