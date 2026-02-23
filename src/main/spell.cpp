#include <iostream>
#include <fstream>
#include "mach/Machine.hpp"

int main(int argc, char *argv[]){
    Machine machine;
    std::string program;
    auto err = OK;
    
    /* 从文件中获取程序 */
    if(argc > 1){
        std::ifstream ifs(argv[1]);
        std::string buf;

        if(!ifs.is_open()){
            std::cerr << "Failed to open: " << argv[1] << std::endl;
            return 1;
        }

        while(std::getline(ifs, buf)){
            program.append(buf);
        }
        ifs.close();
    }
    else{
        std::cerr << "No input file provided." << std::endl;
        return 1;
    }

    try{
        machine.execute(program);
    }catch(SpellExcept &se){
        std::cerr << "spell: execution failed with errno:  " << se.err() << std::endl;
        return se.err();
    }

    return 0;
}