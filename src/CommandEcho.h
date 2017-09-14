#ifndef ECHO_H
#define ECHO_H

#include "Command.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class CommandEcho : public Command {
public:
    CommandEcho(istream& is, ostream& os, bool is_dbg);
    CommandEcho(istream& is, string filename, bool is_dbg);
    CommandEcho(string filename, ostream& os, bool is_dbg);
    CommandEcho(string ifilename, string ofilename, bool is_dbg);
    CommandEcho(const CommandEcho& orig) = delete;
    virtual ~CommandEcho();
    
    int run(vector<string> args);
    string to_string();
    
private:    
    void do_echo();    
};

#endif /* ECHO_H */

