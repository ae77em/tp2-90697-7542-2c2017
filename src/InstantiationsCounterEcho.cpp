#include "InstantiationsCounter.h"

class InstantiationsCounterEcho : public InstantiationsCounter {
public:
    friend class InstantiationsCounter;
protected:

    InstantiationsCounterEcho() {
    }
};

