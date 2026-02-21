#include "io/impl/RegIO.hpp"

RegIO::RegIO(regsize_t *regp) : regp_(regp){

}

int RegIO::id(){
    return UNIIO_ID_REG;
}

regsize_t RegIO::in(){
    return (*regp_);
}

void RegIO::out(regsize_t data){
    (*regp_) = data;
}