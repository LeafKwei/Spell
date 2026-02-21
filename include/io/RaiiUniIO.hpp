#ifndef SPELL_RAIIUNIIO_HPP
#define SPELL_RAIIUNIIO_HPP

class UniIO;
class RaiiUniIO{
public:
    RaiiUniIO(UniIO *ptr);
    ~RaiiUniIO();
    UniIO* get() const noexcept;

private:
    UniIO *ptr_;
};

inline RaiiUniIO::RaiiUniIO(UniIO *ptr) : ptr_(ptr){

}

inline RaiiUniIO::~RaiiUniIO(){
    delete ptr_;
    ptr_ = nullptr;
}

inline UniIO* RaiiUniIO::get() const noexcept{
    return ptr_;
}

#endif