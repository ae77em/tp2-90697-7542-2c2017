#include "Command.h"

#include <regex>

using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::vector;

Command::Command(vector<string> args,
        bool is_dbg,
        IntermediateBuffer &previous_buffer,
        IntermediateBuffer &next_buffer
        ) : arguments(args),
is_debug(is_dbg),
previous_buffer(previous_buffer),
next_buffer(next_buffer) {
}

Command::~Command() {
}

void Command::initialize() {
    //  counter = InstantiationsCounter::instance()
}

string Command::get_wrong_params_size_msg(string command) {
    return command + ": cantidad de parámetros incorrecta.";
}

void Command::print_pos_in_pipe() {
    if (is_debug) {
        pos_in_pipe++;
        cerr << "(" << pos_in_pipe << ") ";
    }
}

void Command::set_buffer_is_ready(bool ir) {
    buffer_is_ready = ir;
}

bool Command::is_ready() {
    return buffer_is_ready;
}

void Command::run() {
    while (previous_buffer.is_processing_yet()) {
        std::unique_lock<std::mutex> lck(m);
        cv.wait(lck, [this] {
            return buffer_is_ready;
        });

        do_command();

        lck.unlock();

        next_buffer.add_intermediate_result(output);
    }
}

string Command::to_string() {
    return "base command";
}

vector<string> Command::get_arguments() const {
    return arguments;
}

void Command::print_cont() {
    if (is_debug) {
        cerr << this->to_string() << counter << std::endl;
    }
}

void Command::print_intermediate_buffer() {
    if (is_debug) {
        cerr << input << " -> " << output << std::endl;
    }
}

void Command::set_previous_buffer_for_debug() {
    //    if (is_debug) {
    //        previous_buffer = intermediate_buffer;
    //    }
}

int Command::get_counter() const {
    return counter;
}

void Command::set_counter(int counter) {
    this->counter = counter;
}

string Command::get_previous_buffer_data() const {
    //    return previous_buffer.get_next_intermediate_result();
    return "";
}

void Command::set_intermediate_buffer(string intermediate_buffer) {
    //    this->intermediate_buffer = intermediate_buffer;
}

bool Command::get_is_debug() const {
    return is_debug;
}

void Command::set_is_debug(bool is_dbg) {
    this->is_debug = is_dbg;
}

string Command::get_input() const {
    return this->input;
}

void Command::set_input(string input) {
    this->input = input;
}

string Command::get_output() const {
    return this->output;
}

void Command::set_output(string output) {
    this->output = output;
}

void Command::load_in_next_buffer(string str) {
    this->next_buffer.add_intermediate_result(str);
}

string Command::get_from_previous_buffer() {
    return this->previous_buffer.get_next_intermediate_result();
}
