#include "Command.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::vector;

Command::Command() : Thread() {
}

Command::Command(const Command& orig) : Thread() {
}

Command::Command(vector<string> args, bool is_dbg)
: arguments(args), is_debug(is_dbg) {
}

Command::~Command() {
}

void Command::initialize() {
    //  counter = InstantiationsCounter::instance()
}

void Command::wait_for_input() {
    //    std::unique_lock<std::mutex> lk(my_mutex);
    //    cv.wait(lk, [] {
    //        return ready;
    //    });
    //
    //    // acá tengo que procesar....
    //
    //    lk.unlock();
    //    cv.notify_one();
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
