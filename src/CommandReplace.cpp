#include "CommandReplace.h"

CommandReplace::CommandReplace(istream& is, ostream& os, bool is_dbg)
: Command(is, os, is_dbg) {
}

CommandReplace::CommandReplace(istream& is, string ofilename, bool is_dbg)
: Command(is, ofilename, is_dbg) {
}

CommandReplace::CommandReplace(string ifilename, ostream& os, bool is_dbg)
: Command(ifilename, os, is_dbg) {
}

CommandReplace::CommandReplace(string ifilename, string ofilename, bool is_dbg)
: Command(ifilename, ofilename, is_dbg) {
}

CommandReplace::~CommandReplace() {
}

int CommandReplace::run(vector<string> args) {
    int status = EXIT_SUCCESS;

    if (args.size() == 2) {
        do_replace(args.at(0), args.at(1));
    } else {
        status = EXIT_FAILURE;
        std::cerr << get_wrong_params_size_msg("replace");
    }

    return status;
}

void CommandReplace::do_replace(string pattern, string replacement) {
    print_cont();
    set_previous_buffer_for_debug();
    intermediate_buffer = std::regex_replace(
            intermediate_buffer,
            std::regex(pattern),
            replacement);
    print_intermediate_buffer();
}

string CommandReplace::to_string() {
    return "replace";
}
