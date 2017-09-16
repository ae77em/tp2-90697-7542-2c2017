#include "CommandFactory.h"

CommandEcho* CommandFactory::createEcho(vector<string> args, bool is_dbg) {
    return new CommandEcho(args, is_dbg);
}

CommandMatch* CommandFactory::createMatch(vector<string> args, bool is_dbg) {
    return new CommandMatch(args, is_dbg);
}

CommandReplace* CommandFactory::createReplace(vector<string> args, bool is_dbg) {
    return new CommandReplace(args, is_dbg);
}

Command* CommandFactory::create(vector<string> args, bool is_dbg) {
    //return new Command(args, is_dbg);
    return NULL;
}

Command* CommandFactory::createCommand(string cmd, vector<string> args, bool is_dbg) {
    if (cmd.compare("echo") == 0) {
        return createEcho(args, is_dbg);
    } else if (cmd.compare("replace") == 0) {
        return createReplace(args, is_dbg);
    } else if (cmd.compare("match") == 0) {
        return createMatch(args, is_dbg);
    } else {
        return NULL; //create(args, is_dbg);
    }
}