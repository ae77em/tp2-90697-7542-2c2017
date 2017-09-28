#ifndef MATCH_H
#define MATCH_H

#include "Command.h"

#include <string>
#include <vector>

class CommandMatch : public Command {
private:
    string pattern;
public:
    CommandMatch(std::vector<std::string> args,
            bool is_dbg,
            IntermediateBuffer &previous_buffer,
            IntermediateBuffer &next_buffer,
            int pos_in_pipe);
    virtual ~CommandMatch();
    
    void do_command();
    void load_error_buffer();
    string to_string();
        
protected:    
    void initialize();
    
private:    
    CommandMatch() = delete;
    CommandMatch(const CommandMatch& orig) = delete;
};

#endif /* MATCH_H */

