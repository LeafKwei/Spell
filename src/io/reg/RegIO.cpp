#include "io/reg/RegIO.hpp"

int RegIO::id(){
    return UNIIO_ID_REG;
}

void* RegIO::ptr(){
    return regp_;
}

void  RegIO::setptr(void *ptr){
    regp_ = static_cast<regsize_t*>(ptr);
}

regsize_t RegIO::in(){
    return (*regp_);
}

void RegIO::out(regsize_t data){
    (*regp_) = data;
}