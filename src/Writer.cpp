#include "Writer.h"

#include <iostream>
#include <string>

using std::string;

Writer::Writer(IntermediateBuffer &in, ostream &out)
: input(in), output(out) {
}

Writer::~Writer() {
}

void Writer::run() {
    string result;

    while (input.is_processing_yet()) {
        if (input.find_and_store_next_output(result)) {
            output << result << std::endl;
        }
    }
}
