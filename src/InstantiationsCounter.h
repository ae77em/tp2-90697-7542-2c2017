#ifndef INSTANTIATIONSCOUNTER_H
#define INSTANTIATIONSCOUNTER_H

class InstantiationsCounter {
public:
    InstantiationsCounter();
    InstantiationsCounter(const InstantiationsCounter& orig) = delete;
    virtual ~InstantiationsCounter();
    
    //static InstantiationsCounter *instance(string type);    
    int getCounterAndIncrementIt();
    
private:    
    int counter = 0;
    static InstantiationsCounter *inst;
};

#endif /* INSTANTIATIONSCOUNTER_H */

