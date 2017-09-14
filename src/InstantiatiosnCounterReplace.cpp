#include "InstantiationsCounter.h"

class InstantiatiosnCounterReplace : public InstantiationsCounter {
public:
    friend class InstantiationsCounter;
protected:

    InstantiatiosnCounterReplace() {
    }
};

