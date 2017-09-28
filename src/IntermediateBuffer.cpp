#include "IntermediateBuffer.h"

#include <iostream>
#include <string>

using std::string;

IntermediateBuffer::IntermediateBuffer() {
}

IntermediateBuffer::~IntermediateBuffer() {
}

string IntermediateBuffer::find_and_store_next_output() {
    string result = "";
    
    unique_lock<mutex> lck(m);
    cv.wait(lck, [this] {
        return has_output() || is_ended();
    });

    if (has_output()) {
        result.assign(intermediate_results.front());
        intermediate_results.pop();
    }

    cv.notify_one();
    lck.unlock();

    return result;
}

void IntermediateBuffer::add_intermediate_result(const string &s) {
    unique_lock<mutex> lck(m);

    intermediate_results.push(s);

    cv.notify_one();
    lck.unlock();
}

bool IntermediateBuffer::is_processing_yet() const {
    return !previous_ended || !intermediate_results.empty();
}

bool IntermediateBuffer::is_ended() const {
    return previous_ended && intermediate_results.empty();
}

bool IntermediateBuffer::has_output() const {
    return !intermediate_results.empty();
}

void IntermediateBuffer::set_previous_ended(bool ended) {
    unique_lock<mutex> lck(m);

    previous_ended = ended;

    cv.notify_one();
    lck.unlock();
}
