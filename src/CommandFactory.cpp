#include "CommandFactory.h"

CommandEcho* CommandFactory::createEcho(vector<string> args,
        bool is_dbg,
        IntermediateBuffer &previous,
        IntermediateBuffer &next) {
    return new CommandEcho(args, is_dbg, previous, next);
}

CommandMatch* CommandFactory::createMatch(vector<string> args,
        bool is_dbg,
        IntermediateBuffer &previous,
        IntermediateBuffer &next) {
    return new CommandMatch(args, is_dbg, previous, next);
}

CommandReplace* CommandFactory::createReplace(vector<string> args,
        bool is_dbg,
        IntermediateBuffer &previous,
        IntermediateBuffer &next) {
    return new CommandReplace(args, is_dbg, previous, next);
}

Command* CommandFactory::create(vector<string> args,
        bool is_dbg,
        IntermediateBuffer &previous,
        IntermediateBuffer &next) {
    return new Command(args, is_dbg, previous, next);
}

Command* CommandFactory::createCommand(string cmd,
        vector<string> args,
        bool is_dbg,
        IntermediateBuffer &previous,
        IntermediateBuffer &next) {
    if (cmd.compare("echo") == 0) {
        return createEcho(args, is_dbg, previous, next);
    } else if (cmd.compare("replace") == 0) {
        return createReplace(args, is_dbg, previous, next);
    } else if (cmd.compare("match") == 0) {
        return createMatch(args, is_dbg, previous, next);
    } else {
        return create(args, is_dbg, previous, next);
    }
}
