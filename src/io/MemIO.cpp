#include "io/impl/MemIO.hpp"

void* MemIO::ptr(){
    return unitp_;
}

void MemIO::setptr(void *ptr){
    unitp_ = static_cast<charunit_t*>(ptr);
}

int MemIO::id(){
    return UNIIO_ID_MEM;
}

regsize_t MemIO::in(){
    return (*unitp_);
}

void MemIO::out(regsize_t data){
    (*unitp_) = static_cast<charunit_t>(data);
}