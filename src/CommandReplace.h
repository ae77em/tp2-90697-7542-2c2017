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
    CommandReplace();
    CommandReplace(vector<string> args, bool is_dbg);
    CommandReplace(const CommandReplace& orig) = delete;
    virtual ~CommandReplace();
    
    int run();
    string to_string();
    
protected:    
    void initialize();
    
private:
    void do_replace();
    
};

#endif /* REPLACE_H */

