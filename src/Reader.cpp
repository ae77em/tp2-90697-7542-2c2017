#include "Reader.h"

#include <string>
#include <istream>

Reader::Reader(std::istream &is, IntermediateBuffer &out)
: input(is), output(out) {}

Reader::~Reader() { }

void Reader::run() {
    std::string buffer;

    while (std::getline(input, buffer)) {
        output.add_intermediate_result(buffer);
    }

    output.set_previous_ended(true);
}
