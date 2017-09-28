#include "Writer.h"

#include <ostream>
#include <string>

Writer::Writer(IntermediateBuffer &in, std::ostream &out)
: input(in), output(out) {
}

Writer::~Writer() {
}

void Writer::run() {
    std::string result;

    while (input.is_processing_yet()) {
        result = input.find_and_store_next_output();
        if (!result.empty()) {
            output << result << std::endl;
        }
    }
}
