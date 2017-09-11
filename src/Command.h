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

#define PARAM_SEPARATOR "#|#"

class Command {

private:
    unique_ptr<istream, function<void(istream*)>> input;
    unique_ptr<ostream, function<void(ostream*)>> output;
    bool is_debug;
    
    string intermediate_buffer;
    string previous_buffer;
    int pos_in_pipe = 0;
    int cont_echo = 0;
    int cont_match = 0;
    int cont_replace = 0;
    
    string get_wrong_params_size_msg(string command);
    void print_pos_in_pipe();
    void print_cont_echo();
    void print_cont_match();
    void print_cont_replace();
    void print_intermediate_buffer();
    void set_previous_buffer_for_debug();
    
public:
    Command(istream& is, ostream& os, bool is_dbg);
    Command(istream& is, string filename, bool is_dbg);
    Command(string filename, ostream& os, bool is_dbg);
    Command(string ifilename, string ofilename, bool is_dbg);
    Command(const Command& orig) = delete;
    virtual ~Command();
    
    int run(string command, std::vector<string> args);
    
    void echo();
    void match(string regex);
    void replace(string pattern, string replacement);
    void pipeline(string commands);    
    
};

#endif /* COMMANDS_H */

