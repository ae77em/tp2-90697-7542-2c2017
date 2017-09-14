#include "InstantiationsCounter.h"

#include <iostream>
#include <string>
#include <stdlib.h>

InstantiationsCounter::InstantiationsCounter() {
}

InstantiationsCounter::~InstantiationsCounter() {
}

int InstantiationsCounter::getCounterAndIncrementIt() {
    return ++counter;
}

//InstantiationsCounter *InstantiationsCounter::instance(string type) {
//    if (!inst) {
//        if (type == "echo") {
//            inst = new InstantiationsCounterEcho();
//        } else if (type == "replace") {
//            inst = new InstantiatiosnCounterReplace();
//        } else if (type == "match") {
//            inst = new InstantiatiosnCounterReplace();
//        }
//        return inst;
//    }
//
//}