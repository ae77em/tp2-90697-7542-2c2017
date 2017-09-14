#include "ResultProtected.h"

ResultProtected::ResultProtected(unsigned int v) : result(v) {
}

ResultProtected::~ResultProtected() {
}

unsigned int ResultProtected::get_val() {
    Lock l(m);
    return result;
}

void ResultProtected::inc_if_you_are_zero(unsigned int s) {
    Lock l(m);
    if (result == 0) {
        result += s;
    }
}

