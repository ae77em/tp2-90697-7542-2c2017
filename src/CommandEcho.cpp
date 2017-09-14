#include "CommandEcho.h"

CommandEcho::CommandEcho(istream& is, ostream& os, bool is_dbg)
: Command(is, os, is_dbg) {
}

CommandEcho::CommandEcho(istream& is, string ofilename, bool is_dbg)
: Command(is, ofilename, is_dbg) {
}

CommandEcho::CommandEcho(string ifilename, ostream& os, bool is_dbg)
: Command(ifilename, os, is_dbg) {
}

CommandEcho::CommandEcho(string ifilename, string ofilename, bool is_dbg)
: Command(ifilename, ofilename, is_dbg) {
}

CommandEcho::~CommandEcho() {
}

int CommandEcho::run(vector<string> args) {
    do_echo();
    return 0;
}

string CommandEcho::to_string() {
    return "echo";
}

void CommandEcho::do_echo() {
    print_cont();
    set_previous_buffer_for_debug();
    print_intermediate_buffer();
}
