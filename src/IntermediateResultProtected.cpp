#include "IntermediateResultProtected.h"

#include <string>
#include <queue>

using std::string;
using std::queue;

IntermediateResultProtected::IntermediateResultProtected(string v,
        mutex &m,
        condition_variable &cv) : m(m), cv(cv) {
    intermediate_results.push(v);
}

IntermediateResultProtected::~IntermediateResultProtected() {
}

string IntermediateResultProtected::get_next_intermediate_result() {
    string first_element = "";
    if (!intermediate_results.empty()) {
        string first_element = intermediate_results.front();
        intermediate_results.pop();
    }
    return first_element;
}

void IntermediateResultProtected::add_intermediate_result(string s) {
    intermediate_results.push(s);
}

bool IntermediateResultProtected::is_previous_ended() const {
    return previous_ended;
}

void IntermediateResultProtected::set_previous_ended(bool is_ended) {
    previous_ended = is_ended;
}

mutex& IntermediateResultProtected::get_mutex() {
    return m;
}

condition_variable& IntermediateResultProtected::get_condition_variable() {
    return cv;
}

bool IntermediateResultProtected::is_processing_yet() const {
    return !(previous_ended && intermediate_results.empty());
}

bool IntermediateResultProtected::has_output() const {
    return !intermediate_results.empty();
}