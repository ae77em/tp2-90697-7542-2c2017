#include "CommandFactory.h"

#include <vector>
#include <string>

CommandEcho* CommandFactory::createEcho(std::vector<std::string> args,
        bool is_dbg,
        IntermediateBuffer &previous,
        IntermediateBuffer &next,
        int pos_in_pipe) {
    return new CommandEcho(args, is_dbg, previous, next, pos_in_pipe);
}

CommandMatch* CommandFactory::createMatch(std::vector<std::string> args,
        bool is_dbg,
        IntermediateBuffer &previous,
        IntermediateBuffer &next,
        int pos_in_pipe) {
    return new CommandMatch(args, is_dbg, previous, next, pos_in_pipe);
}

CommandReplace* CommandFactory::createReplace(std::vector<std::string> args,
        bool is_dbg,
        IntermediateBuffer &previous,
        IntermediateBuffer &next,
        int pos_in_pipe) {
    return new CommandReplace(args, is_dbg, previous, next, pos_in_pipe);
}

Command* CommandFactory::create(std::vector<std::string> args,
        bool is_dbg,
        IntermediateBuffer &previous,
        IntermediateBuffer &next,
        int pos_in_pipe) {
    return new Command(args, is_dbg, previous, next, pos_in_pipe);
}

Command* CommandFactory::createCommand(string cmd,
        std::vector<std::string> args,
        bool is_dbg,
        IntermediateBuffer &previous,
        IntermediateBuffer &next,
        int pos_in_pipe) {
    if (cmd.compare("echo") == 0) {
        return createEcho(args, is_dbg, previous, next, pos_in_pipe);
    } else if (cmd.compare("replace") == 0) {
        return createReplace(args, is_dbg, previous, next, pos_in_pipe);
    } else if (cmd.compare("match") == 0) {
        return createMatch(args, is_dbg, previous, next, pos_in_pipe);
    } else {
        return create(args, is_dbg, previous, next, pos_in_pipe);
    }
}
