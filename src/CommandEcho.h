#ifndef ECHO_H
#define ECHO_H

#include "Command.h"

#include <string>
#include <vector>

class CommandEcho : public Command {
public:
    CommandEcho(std::vector<std::string> args,
                bool is_dbg,
                IntermediateBuffer &previous_buffer,
                IntermediateBuffer &next_buffer, 
                int pos_in_pipe);
    virtual ~CommandEcho();
    
    string to_string();
        
protected:    
    void initialize();
    void do_command();
    
private:
    CommandEcho() = delete;
    CommandEcho(const CommandEcho& orig) = delete;    
};

#endif /* ECHO_H */

