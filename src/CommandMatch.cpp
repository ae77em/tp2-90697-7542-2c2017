#include "CommandMatch.h"

#include <regex>

CommandMatch::CommandMatch(istream& is, ostream& os, bool is_dbg)
: Command(is, os, is_dbg) {
}

CommandMatch::CommandMatch(istream& is, string ofilename, bool is_dbg)
: Command(is, ofilename, is_dbg) {
}

CommandMatch::CommandMatch(string ifilename, ostream& os, bool is_dbg)
: Command(ifilename, os, is_dbg) {
}

CommandMatch::CommandMatch(string ifilename, string ofilename, bool is_dbg)
: Command(ifilename, ofilename, is_dbg) {
}

CommandMatch::~CommandMatch() {
}

string CommandMatch::to_string() {
    return "match";
}

int CommandMatch::run(vector<string> args) {
    int status = EXIT_SUCCESS;

    if (args.size() == 1) {
        do_match(args.at(0));
    } else {
        status = EXIT_FAILURE;
        std::cerr << get_wrong_params_size_msg("match");
    }

    return status;
}

void CommandMatch::do_match(string pattern) {
    print_cont();
    set_previous_buffer_for_debug();
    if (!std::regex_search(intermediate_buffer, std::regex(pattern))) {
        intermediate_buffer = "";
    }
    print_intermediate_buffer();
}
