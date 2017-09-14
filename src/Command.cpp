#include "Command.h"
#include "InstantiationsCounter.h"

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

#define PIPELINE_DELIMITER "::"

Command::Command(istream& is = std::cin,
        ostream& os = std::cout,
        bool is_dbg = false)
: input(&is, [](istream*) {
})
, output(&os, [](ostream*) {
})

, is_debug(is_dbg) {
}

Command::Command(istream& is, string filename, bool is_dbg = false) :
input(&is, [](istream*) {
})

,
output(new std::ofstream(filename), std::default_delete<std::ostream>()),
is_debug(is_dbg) {
    if (!dynamic_cast<std::ofstream&> (*output).is_open()) {
        // manejo de errores de apertura (!!!)
    }
}

Command::Command(string filename, ostream& os, bool is_dbg = false) :
input(new std::ifstream(filename), std::default_delete<std::istream>()),
output(&os, [](ostream*) {
})

, is_debug(is_dbg) {
    if (!dynamic_cast<std::ifstream&> (*input).is_open()) {
        // manejo de errores de apertura (!!!)
    }
}

Command::Command(string ifilename, string ofilename, bool is_dbg = false)
: input(new std::ifstream(ifilename), std::default_delete<std::istream>()),
output(new std::ofstream(ofilename), std::default_delete<std::ostream>()),
is_debug(is_dbg) {

    if (!dynamic_cast<std::ifstream&> (*input).is_open()) {
        // manejo de errores de apertura (!!!)
    }

    if (!dynamic_cast<std::ofstream&> (*output).is_open()) {
        // manejo de errores de apertura (!!!)
    }

}

Command::~Command() {
}

void Command::initialize() {
    //  counter = InstantiationsCounter::instance()
}

string Command::get_wrong_params_size_msg(string command) {
    return command + ": cantidad de parámetros incorrecta.";
}

void pipeline(string commands) {
    //    istream &in = dynamic_cast<istream&> (*input);
    //    ostream &out = dynamic_cast<ostream&> (*output);
    //    vector<string> cmds = StringUtils::split(commands, PIPELINE_DELIMITER);
    //    vector<string> splitted_cmd;
    //    string cmd;
    //
    //    while (std::getline(in, intermediate_buffer)) {
    //        for (string &entire_cmd : cmds) {
    //            print_pos_in_pipe();
    //            splitted_cmd = StringUtils::split(entire_cmd, PARAM_SEPARATOR);
    //            cmd = splitted_cmd.at(0);
    //            vector<string> args(splitted_cmd.begin() + 1, splitted_cmd.end());
    //
    //            this->run(cmd, args);
    //        }
    //
    //        pos_in_pipe = 0;
    //
    //        if (intermediate_buffer.compare("") != 0) {
    //            out << intermediate_buffer << std::endl;
    //            out.flush();
    //        }
    //    }
}

void Command::print_pos_in_pipe() {
    if (is_debug) {
        pos_in_pipe++;
        cerr << "(" << pos_in_pipe << ") ";
    }
}

int Command::run(std::vector<string> args) {
    return 0;
}

string Command::to_string() {
    return "base command";
}

void Command::print_cont() {
    if (is_debug) {
        cerr << this->to_string() << counter << std::endl;
    }
}

void Command::print_intermediate_buffer() {
    if (is_debug) {
        cerr << previous_buffer << " -> " << intermediate_buffer << std::endl;
    }
}

void Command::set_previous_buffer_for_debug() {
    if (is_debug) {
        previous_buffer = intermediate_buffer;
    }
}

