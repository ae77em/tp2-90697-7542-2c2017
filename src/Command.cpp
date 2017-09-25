#include "Command.h"

#include <regex>
#include <vector>
#include <string>

using std::string;
using std::cerr;
using std::vector;

Command::Command(vector<string> args,
        bool is_dbg,
        IntermediateBuffer &previous_buffer,
        IntermediateBuffer &next_buffer) : arguments(args),
is_debug(is_dbg),
source_buffer(previous_buffer),
dest_buffer(next_buffer) {
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

bool Command::is_load_input_from_source_successful() {
    return source_buffer.find_and_store_next_output(input);
}

void Command::run() {
    while (source_buffer.is_processing_yet()) {
        if (is_load_input_from_source_successful()) {
            do_command();
            load_dest_from_output();
        }
    }
    dest_buffer.set_previous_ended(true);
}

string Command::to_string() {
    return "base command";
}

IntermediateBuffer &Command::get_source_buffer() {
    return source_buffer;
}

IntermediateBuffer &Command::get_dest_buffer() {
    return dest_buffer;
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

void Command::set_intermediate_buffer(string intermediate_buffer) { }

void Command::load_dest_from_output() {
    this->dest_buffer.add_intermediate_result(output);
}
