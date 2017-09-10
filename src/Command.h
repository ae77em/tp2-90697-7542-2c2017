#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <fstream>
#include <iostream>
#include <memory>

#include "StringUtils.h"

using std::istream;
using std::ostream;
using std::function;
using std::string;
using std::unique_ptr;

class Command {

private:
    string get_wrong_params_size_msg(string command);
    unique_ptr<istream, function<void(istream*)>> input;
    unique_ptr<ostream, function<void(ostream*)>> output;
    bool is_debug;
    
public:
    Command(istream& is, ostream& os, bool is_dbg);
    Command(istream& is, string filename, bool is_dbg);
    Command(string filename, ostream& os, bool is_dbg);
    Command(string ifilename, string ofilename, bool is_dbg);
    Command(const Command& orig) = delete;
    virtual ~Command();
    
    int run(string command, std::vector<string> args);
    
    void echo(string &text);
    void echo();
    void match(string regex);
    void replace(string pattern, string replacement);
    void pipeline(string commands);
};

#endif /* COMMANDS_H */

