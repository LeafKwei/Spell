#include "io/impl/MemIO.hpp"

MemIO::MemIO(charunit_t *unitp) : unitp_(unitp){

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