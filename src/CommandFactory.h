#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "Command.h"
#include "CommandEcho.h"
#include "CommandMatch.h"
#include "CommandReplace.h"

#include <string>
#include <vector>

class CommandFactory {
private:
    static CommandEcho* createEcho(std::vector<std::string> args, 
            bool is_dbg,
            IntermediateBuffer &previous, 
            IntermediateBuffer &next,
            int pos_in_pipe);

    static CommandMatch* createMatch(std::vector<std::string> args, 
            bool is_dbg,
            IntermediateBuffer &previous, 
            IntermediateBuffer &next,
            int pos_in_pipe);

    static CommandReplace* createReplace(std::vector<std::string> args,
            bool is_dbg,
            IntermediateBuffer &previous, 
            IntermediateBuffer &next,
            int pos_in_pipe);

    static Command* create(std::vector<std::string> args,
            bool is_dbg,
            IntermediateBuffer &previous, 
            IntermediateBuffer &next,
            int pos_in_pipe);

public:
    CommandFactory();
    CommandFactory(const CommandFactory& orig) = delete;
    virtual ~CommandFactory();
    
    static Command *createCommand(std::string cmd, 
                    std::vector<std::string> args, 
                    bool is_dbg,
                    IntermediateBuffer &previous, 
                    IntermediateBuffer &next,
                    int pos_in_pipe);
};

#endif /* COMMANDFACTORY_H */
