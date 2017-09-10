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

    if (command.compare(CMD_ECHO)) {
        if (args.size() == 2) {
            echo(args.at(0));
        } else {
            status = EXIT_FAILURE;
            std::cerr << get_wrong_params_size_msg(CMD_ECHO);
        }
    } else if (command.compare(CMD_MACTCH)) {
        if (args.size() == 1) {
            match(args.at(0));
        } else {
            status = EXIT_FAILURE;
            std::cerr << get_wrong_params_size_msg(CMD_MACTCH);
        }
    } else if (command.compare(CMD_REPLACE)) {
        if (args.size() == 2) {
            replace(args.at(0), args.at(1));
        } else {
            status = EXIT_FAILURE;
            std::cerr << get_wrong_params_size_msg(CMD_REPLACE);
        }
    } else {
        status = EXIT_FAILURE;
        std::cerr << "Comando desconocido.";
    }

    return status;
}

void Command::echo(string &text) {
    ostream &out = dynamic_cast<ostream&> (*output);

    out << text << "\n";
}

void Command::echo() {
    istream &in = dynamic_cast<istream&> (*input);
    ostream &out = dynamic_cast<ostream&> (*output);

    out << in.rdbuf() << "\n";
}

void Command::match(string pattern) {
    istream &in = dynamic_cast<istream&> (*input);
    ostream &out = dynamic_cast<ostream&> (*output);

    std::ostringstream ss;
    ss << in.rdbuf();
    string buffer = ss.str();

    if (std::regex_match(buffer, std::regex(pattern))) {
        out << buffer << "\n";
    }
}

void Command::replace(string pattern, string replacement) {
    istream &in = dynamic_cast<istream&> (*input);
    ostream &out = dynamic_cast<ostream&> (*output);

    std::ostringstream ss;
    ss << in.rdbuf();
    string buffer = ss.str();

    out << std::regex_replace(buffer, std::regex(pattern), replacement) << "\n";
}

void Command::pipeline(string commands) {

    vector<string> cmds = StringUtils::split(commands, PIPELINE_DELIMITER);
    vector<string> splitted_cmd;
    vector<string> args;

    for (string &cmd : cmds) {
        splitted_cmd = StringUtils::split(cmd, " ");
        cmd = splitted_cmd.at(0);
        vector<string> args(splitted_cmd.begin() + 1, splitted_cmd.end());

        this->run(cmd, args);
    }
}
