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

#define PIPELINE_DELIMITER "::"
#define CMD_ECHO "echo"
#define CMD_MACTCH "match"
#define CMD_REPLACE "replace"

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

string Command::get_wrong_params_size_msg(string command) {
    return command + ": cantidad de parámetros incorrecta.";
}

int Command::run(string command, vector<string> args) {

    int status = EXIT_SUCCESS;

    if (command.compare(CMD_ECHO) == 0) {
        echo();
    } else if (command.compare(CMD_MACTCH) == 0) {
        if (args.size() == 1) {
            match(args.at(0));
        } else {
            status = EXIT_FAILURE;
            std::cerr << get_wrong_params_size_msg(CMD_MACTCH);
        }
    } else if (command.compare(CMD_REPLACE) == 0) {
        if (args.size() == 2) {
            replace(args.at(0), args.at(1));
        } else {
            status = EXIT_FAILURE;
            std::cerr << get_wrong_params_size_msg(CMD_REPLACE);
        }
    } else {
        status = EXIT_FAILURE;
        std::cerr << "Comando '" << command << "' desconocido.";
    }

    return status;
}

void Command::echo() {
    print_cont_echo();
    set_previous_buffer_for_debug();
    print_intermediate_buffer();
}

void Command::match(string pattern) {
    print_cont_match();
    set_previous_buffer_for_debug();
    if (!std::regex_search(intermediate_buffer, std::regex(pattern))) {
        intermediate_buffer = "";
    }
    print_intermediate_buffer();
}

void Command::replace(string pattern, string replacement) {
    print_cont_replace();
    set_previous_buffer_for_debug();
    intermediate_buffer = std::regex_replace(
            intermediate_buffer,
            std::regex(pattern),
            replacement);
    print_intermediate_buffer();
}

void Command::pipeline(string commands) {
    istream &in = dynamic_cast<istream&> (*input);
    ostream &out = dynamic_cast<ostream&> (*output);
    vector<string> cmds = StringUtils::split(commands, PIPELINE_DELIMITER);
    vector<string> splitted_cmd;
    string cmd;

    while (std::getline(in, intermediate_buffer)) {
        for (string &entire_cmd : cmds) {
            print_pos_in_pipe();
            splitted_cmd = StringUtils::split(entire_cmd, PARAM_SEPARATOR);
            cmd = splitted_cmd.at(0);
            vector<string> args(splitted_cmd.begin() + 1, splitted_cmd.end());

            this->run(cmd, args);
        }

        pos_in_pipe = 0;

        if (intermediate_buffer.compare("") != 0) {
            out << intermediate_buffer << std::endl;
            out.flush();
        }
    }
}

void Command::print_pos_in_pipe() {
    if (is_debug) {
        pos_in_pipe++;
        cerr << "(" << pos_in_pipe << ") ";
    }
}

void Command::print_cont_echo() {
    if (is_debug) {
        cont_echo++;
        cerr << "echo" << cont_echo << std::endl;
    }
}

void Command::print_cont_match() {
    if (is_debug) {
        cont_match++;
        cerr << "match" << cont_match << std::endl;
    }
}

void Command::print_cont_replace() {
    if (is_debug) {
        cont_replace++;
        cerr << "replace" << cont_replace << std::endl;
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