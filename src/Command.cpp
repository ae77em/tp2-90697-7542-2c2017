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
    // do nothing...hill
}

void Command::do_command() {
    // do nothing...hill
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

void Command::run() {
    while (previous_buffer.is_processing_yet()) {
        std::unique_lock<std::mutex> lck(m);
        cv.wait(lck, [this] {
            return previous_buffer.has_output();
        });

        do_command();

        lck.unlock();

        next_buffer.add_intermediate_result(output);
    }
    next_buffer.set_previous_ended(true);
}

void Command::set_buffer_is_ready(bool ir) {
    buffer_is_ready = ir;
}

string Command::to_string() {
    return "base command";
}

IntermediateBuffer &Command::get_previous_buffer() {
    return previous_buffer;
}

IntermediateBuffer &Command::get_next_buffer() {
    return next_buffer;
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
    return "";
}

void Command::set_intermediate_buffer(string intermediate_buffer) {

}

void Command::load_in_next_buffer(string str) {
    this->next_buffer.add_intermediate_result(str);
}
