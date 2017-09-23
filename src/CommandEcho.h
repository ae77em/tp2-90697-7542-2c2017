#ifndef ECHO_H
#define ECHO_H

#include "Command.h"

#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ostream;
using std::istream;

class CommandEcho : public Command {
public:
    CommandEcho(vector<string> args, 
                bool is_dbg,
                IntermediateBuffer &previous_buffer,
                IntermediateBuffer &next_buffer);
    virtual ~CommandEcho();
    
    void run();
    string to_string();
        
protected:    
    void initialize();
    void do_command();
    
private:
    CommandEcho() = delete;
    CommandEcho(const CommandEcho& orig) = delete;    
};

#endif /* ECHO_H */

