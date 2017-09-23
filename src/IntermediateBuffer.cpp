#include "IntermediateBuffer.h"

using std::string;
using std::queue;

IntermediateBuffer::IntermediateBuffer() {
}

IntermediateBuffer::~IntermediateBuffer() {
}

string IntermediateBuffer::get_next_intermediate_result() {
    string first_element = "";
    if (this->has_output()) {
        first_element = intermediate_results.front();
        intermediate_results.pop();
    }
    return first_element;
}

void IntermediateBuffer::add_intermediate_result(const string &s) {
    intermediate_results.push(s);
}

bool IntermediateBuffer::is_processing_yet() const {
    return !(previous_ended & intermediate_results.empty());
}

bool IntermediateBuffer::has_output() const {
    return !intermediate_results.empty();
}