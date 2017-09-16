#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

using std::istream;
using std::ostream;
using std::function;
using std::string;
using std::unique_ptr;
using std::vector;

class Command {
private:
    string previous_buffer;
    int pos_in_pipe = 0;
        
protected:
    string input;
    string output;
    vector<string> arguments;
    bool is_debug;
    int counter;
    string intermediate_buffer;
       
public:
    Command();
    Command(vector<string> args, bool is_dbg);
    Command(const Command& orig);
    virtual ~Command();
    
    virtual int run();
    virtual string to_string();

    bool get_is_debug() const;
    void set_is_debug(bool is_debug);
    vector<string> get_arguments() const;
    string get_input() const;
    void set_input(string input);
    string get_output() const;
    void set_output(string output);
    
protected:
    void print_cont();
    string get_wrong_params_size_msg(string command);
    void print_pos_in_pipe();
    void print_intermediate_buffer();
    void set_previous_buffer_for_debug();
    
    int get_counter() const;
    void set_counter(int counter);
    string get_intermediate_buffer() const;
    void set_intermediate_buffer(string intermediate_buffer);
        
    void initialize();    
};

#endif /* COMMANDS_H */

