#include "Pipeline.h"
#include "StringUtils.h"

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

Pipeline::Pipeline(istream& is = std::cin,
        ostream& os = std::cout,
        bool is_dbg = false,
        const string &cmds = "")
: input(&is, [](istream*) {
})
, output(&os, [](ostream*) {
})

, is_debug(is_dbg) {
    initialize(cmds);
}

Pipeline::Pipeline(istream& is,
        string filename,
        bool is_dbg = false,
        const string& cmds = "") :
input(&is, [](istream*) {
})

,
output(new std::ofstream(filename), std::default_delete<std::ostream>()),
is_debug(is_dbg) {
    if (!dynamic_cast<std::ofstream&> (*output).is_open()) {
        // manejo de errores de apertura (!!!)
    }

    initialize(cmds);
}

Pipeline::Pipeline(string filename,
        ostream& os,
        bool is_dbg = false,
        const string& cmds = "") :
input(new std::ifstream(filename), std::default_delete<std::istream>()),
output(&os, [](ostream*) {
})

, is_debug(is_dbg) {
    if (!dynamic_cast<std::ifstream&> (*input).is_open()) {
        // manejo de errores de apertura (!!!)
    }

    initialize(cmds);
}

Pipeline::Pipeline(string ifilename,
        string ofilename,
        bool is_dbg = false,
        const string& cmds = "")
: input(new std::ifstream(ifilename), std::default_delete<std::istream>()),
output(new std::ofstream(ofilename), std::default_delete<std::ostream>()),
is_debug(is_dbg) {

    if (!dynamic_cast<std::ifstream&> (*input).is_open()) {
        // manejo de errores de apertura (!!!)
    }

    if (!dynamic_cast<std::ofstream&> (*output).is_open()) {
        // manejo de errores de apertura (!!!)
    }

    initialize(cmds);
}

void Pipeline::initialize(const string &cmds) {
    vector<string> cmds_list = StringUtils::split(cmds, PIPELINE_DELIMITER);
    vector<string> splitted_cmd;

    string cmd;

    for (string &entire_cmd : cmds_list) {
        splitted_cmd = StringUtils::split(entire_cmd, PARAM_SEPARATOR);
        cmd = splitted_cmd.at(0);
        vector<string> args(splitted_cmd.begin() + 1, splitted_cmd.end());

        Command *command = CommandFactory::createCommand(cmd, args, is_debug);
        commands.push_back(command);
    }
}

Pipeline::~Pipeline() {
}

void Pipeline::run() {
    istream &in = dynamic_cast<istream&> (*input);
    ostream &out = dynamic_cast<ostream&> (*output);

    string intermediate_buffer;
    string current_input;

    while (std::getline(in, intermediate_buffer)) {
        current_input = intermediate_buffer;
        for (Command *c : commands) {
            c->set_input(current_input);
            c->run();
            out << c->get_output() << std::endl;
            current_input = c->get_output();
        }
    }
}
