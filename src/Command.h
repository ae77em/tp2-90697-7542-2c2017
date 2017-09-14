#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>

#include "StringUtils.h"

using std::istream;
using std::ostream;
using std::function;
using std::string;
using std::unique_ptr;
using std::queue;

#define PARAM_SEPARATOR "#|#"

class Command {

private:
    string previous_buffer;
    int pos_in_pipe = 0;
    int cont_echo = 0;
    int cont_match = 0;
    int cont_replace = 0;
    
protected:
    unique_ptr<istream, function<void(istream*)>> input;
    unique_ptr<ostream, function<void(ostream*)>> output;
    bool is_debug;
    int counter;
    string intermediate_buffer;
       
public:
    Command(istream& is, ostream& os, bool is_dbg);
    Command(istream& is, string filename, bool is_dbg);
    Command(string filename, ostream& os, bool is_dbg);
    Command(string ifilename, string ofilename, bool is_dbg);
    Command(const Command& orig) = delete;
    virtual ~Command();
    
    virtual int run(std::vector<string> args);
    virtual string to_string();
    
protected:
    void print_cont();
    string get_wrong_params_size_msg(string command);
    void print_pos_in_pipe();
    void print_intermediate_buffer();
    void set_previous_buffer_for_debug();
    
private:
    void initialize();
};

#endif /* COMMANDS_H */

