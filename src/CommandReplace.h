#ifndef REPLACE_H
#define REPLACE_H

#include "Command.h"

#include <string>
#include <vector>
#include <regex>

using std::string;
using std::vector;

class CommandReplace : public Command {
public:
    CommandReplace(istream& is, ostream& os, bool is_dbg);
    CommandReplace(istream& is, string filename, bool is_dbg);
    CommandReplace(string filename, ostream& os, bool is_dbg);
    CommandReplace(string ifilename, string ofilename, bool is_dbg);
    CommandReplace(const CommandReplace& orig) = delete;
    virtual ~CommandReplace();
    
    int run(vector<string> args);
    string to_string();
        
private:
    void do_replace(string pattern, string replacement);
};

#endif /* REPLACE_H */

