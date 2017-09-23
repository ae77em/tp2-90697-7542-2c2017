#ifndef MATCH_H
#define MATCH_H

#include "Command.h"

#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ostream;
using std::istream;

class CommandMatch : public Command {
private:
    string pattern;
public:
    CommandMatch(vector<string> args, 
            bool is_dbg,
            IntermediateBuffer &previous_buffer,
            IntermediateBuffer &next_buffer);
    virtual ~CommandMatch();
    
    void do_command();
    string to_string();
        
protected:    
    void initialize();
    
private:    
    CommandMatch() = delete;
    CommandMatch(const CommandMatch& orig) = delete;
};

#endif /* MATCH_H */

