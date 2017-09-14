#ifndef RESULTPROTECTED_H
#define RESULTPROTECTED_H

#include "Lock.h"

#include <mutex>

class ResultProtected {
    
public:
    ResultProtected();
    ResultProtected(const ResultProtected& orig);
    ResultProtected(unsigned int v);
    virtual ~ResultProtected();
    
    unsigned int get_val();
    void inc_if_you_are_zero(unsigned int s);

private:
    std::mutex m;
    unsigned int result;
};

#endif /* RESULTPROTECTED_H */

