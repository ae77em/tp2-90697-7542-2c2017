#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "Command.h"
#include "CommandEcho.h"
#include "CommandMatch.h"
#include "CommandReplace.h"

#include <string>
#include <vector>

using std::ostream;
using std::istream;
using std::string;
using std::vector;

class CommandFactory {
private:
    static CommandEcho* createEcho(vector<string> args, 
            bool is_dbg,
            IntermediateBuffer &previous, 
            IntermediateBuffer &next);
    static CommandMatch* createMatch(vector<string> args, 
            bool is_dbg,
            IntermediateBuffer &previous, 
            IntermediateBuffer &next);
    static CommandReplace* createReplace(vector<string> args, 
            bool is_dbg,
            IntermediateBuffer &previous, 
            IntermediateBuffer &next);
    static Command* create(vector<string> args, 
            bool is_dbg,
            IntermediateBuffer &previous, 
            IntermediateBuffer &next);

public:
    CommandFactory();
    CommandFactory(const CommandFactory& orig) = delete;
    virtual ~CommandFactory();
    
    static Command *createCommand(string cmd, 
                    vector<string> args, 
                    bool is_dbg,
                    IntermediateBuffer &previous, 
                    IntermediateBuffer &next);
};



#endif /* COMMANDFACTORY_H */

