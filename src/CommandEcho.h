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
    CommandEcho();
    CommandEcho(vector<string> args, bool is_dbg);
    CommandEcho(const CommandEcho& orig) = delete;
    virtual ~CommandEcho();
    
    int run();
    string to_string();
        
protected:    
    void initialize();
    
private:    
    void do_echo();    
};

#endif /* ECHO_H */

