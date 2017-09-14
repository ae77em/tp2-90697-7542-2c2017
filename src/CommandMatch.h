#ifndef MATCH_H
#define MATCH_H

#include "Command.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class CommandMatch : public Command {
public:
    CommandMatch(istream& is, ostream& os, bool is_dbg);
    CommandMatch(istream& is, string filename, bool is_dbg);
    CommandMatch(string filename, ostream& os, bool is_dbg);
    CommandMatch(string ifilename, string ofilename, bool is_dbg);
    CommandMatch(const CommandMatch& orig) = delete;
    virtual ~CommandMatch();
    
    int run(vector<string> args);
    string to_string();
    
private:    
    void do_match(string pattern);
};

#endif /* MATCH_H */

