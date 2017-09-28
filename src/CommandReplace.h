#ifndef REPLACE_H
#define REPLACE_H

#include "Command.h"

#include <string>
#include <vector>
#include <regex>

using std::string;
using std::vector;

class CommandReplace : public Command {
    string pattern;
    string replacement;
    
public:
    CommandReplace(vector<string> args, 
        bool is_dbg, 
        IntermediateBuffer &previous_buffer,
        IntermediateBuffer &next_buffer, 
        int pos_in_pipe);
    virtual ~CommandReplace();
    
    void do_command();
    string to_string();
    
protected:    
    void initialize();
    
private:
    CommandReplace() = delete;
    CommandReplace(const CommandReplace& orig) = delete;
};

#endif /* REPLACE_H */

