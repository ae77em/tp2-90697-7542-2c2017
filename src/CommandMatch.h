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
    CommandMatch();
    CommandMatch(vector<string> args, bool is_dbg);
    CommandMatch(const CommandMatch& orig) = delete;
    virtual ~CommandMatch();
    
    int run();
    string to_string();
        
protected:    
    void initialize();
    
private:    
    void do_match();
};

#endif /* MATCH_H */

