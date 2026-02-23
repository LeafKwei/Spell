#include <iostream>
#include "def/dev.hpp"
#include "io/dev/term/TermDeviceIO.hpp"

regsize_t TermDeviceIO::in(){
    charunit_t ch;

    switch(port_){
        case DEV_TERM_STDIN:
            std::cin >> ch;     
            return ch;
        case DEV_TERM_STDOUT:
        case DEV_TERM_STDERR:
        default:
            return 0;
    }
}

void TermDeviceIO::out(regsize_t data){
    charunit_t ch = static_cast<charunit_t>(data);

    switch(port_){
        case DEV_TERM_STDOUT:
            std::cout << ch;
        case DEV_TERM_STDERR:
            std::cerr << ch;
        case DEV_TERM_STDIN:
        default:
            break;
    }
}

void TermDeviceIO::setport(regsize_t port){
    port_ = port;
}