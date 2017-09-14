#include "InstantiationsCounter.h"

class InstantiatiosnCounterMatch : public InstantiationsCounter {
public:
    friend class InstantiationsCounter;
protected:

    InstantiatiosnCounterMatch() {
    }
};

