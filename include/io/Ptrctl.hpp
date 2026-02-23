#ifndef SPELL_PTRCTL_HPP
#define SPELL_PTRCTL_HPP

class Ptrctl{
public:
    virtual ~Ptrctl() =default;
    virtual void  setptr(void *ptr) =0;
    virtual void* ptr() =0;
};

#endif 