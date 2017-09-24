#include "Writter.h"

Writter::Writter(IntermediateBuffer &in, ostream &out)
: input(in), output(out) {
}

Writter::~Writter() {
}

void Writter::run() {
    string buffer;

    while (input.is_processing_yet()) {
        if (input.has_output()) {
            output << input.get_next_intermediate_result() << std::endl;
        }
    }
}