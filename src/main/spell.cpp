#include <iostream>
#include "mach/Machine.hpp"

int main(int argc, char *argv[]){
    Machine machine;
    auto err = machine.execute(argv[1]);
    if(err != OK){
        std::cout << "Get an errno: " << err << std::endl;
    }
}