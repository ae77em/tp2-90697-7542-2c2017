#include "Command.h"

#include <regex>
#include <vector>
#include <string>
#include <iostream>

Command::Command(std::vector<std::string> args,
        bool is_dbg,
        IntermediateBuffer &previous_buffer,
        IntermediateBuffer &next_buffer,
        int pos_in_pipe) : arguments(args),
is_debug(is_dbg),
source_buffer(previous_buffer),
dest_buffer(next_buffer){
    this->pos_in_pipe = pos_in_pipe;
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


void Command::load_input_from_source() {
    input = source_buffer.find_and_store_next_output();
}

void Command::run() {
    while (source_buffer.is_processing_yet()) {
        load_input_from_source();
        if (!input.empty()) {
            do_command();
            load_dest_from_output();
        }
        if (is_debug){
            load_error_buffer();
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

std::vector<std::string> Command::get_arguments() const {
    return arguments;
}

string Command::get_error_header() {
    std::string header = "";

    header.append("(");
    header.append(std::to_string(pos_in_pipe));
    header.append(") ");
    header.append(this->to_string());
    header.append(std::to_string(counter));
    header.append("\n");

    return header;
}

void Command::load_error_buffer() {
    if (!input.empty()){
        error.append(input);
        error.append(" -> ");
        error.append(output);
        error.append("\n");
    }
}

void Command::set_counter(int counter) {
    this->counter = counter;
}

void Command::load_dest_from_output() {
    this->dest_buffer.add_intermediate_result(output);
}

string Command::get_debug_text(){
    std::string text = "";

    text.append(get_error_header());
    text.append(error);
    
    return text;
}
