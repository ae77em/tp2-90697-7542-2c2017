#ifndef COMMAND_H
#define COMMAND_H

#include "Thread.h"
#include "IntermediateBuffer.h"

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>

using std::istream;
using std::ostream;
using std::function;
using std::string;
using std::unique_ptr;
using std::vector;
using std::mutex;
using std::condition_variable;

class Command : public Thread {
private:
    int pos_in_pipe = 0;
        
protected:
    mutex m;
    condition_variable cv;
    string input;
    string output;
    vector<string> arguments;
    bool is_debug;
    int counter;
    bool buffer_is_ready;
    IntermediateBuffer &previous_buffer;
    IntermediateBuffer &next_buffer;
       
public:
    Command(vector<string> args, 
            bool is_dbg, 
            IntermediateBuffer &previous_buffer,
            IntermediateBuffer &next_buffer);
    virtual ~Command();
    
    void run();
    virtual string to_string();

    bool get_is_debug() const;
    void set_is_debug(bool is_debug);
    vector<string> get_arguments() const;
    string get_input() const;
    void set_input(string input);
    string get_output() const;
    void set_output(string output);
    void set_buffer_is_ready(bool ir);
    bool is_ready();    
    void load_in_next_buffer(string str);
    string get_from_previous_buffer();
        
private:
    Command() = delete;
    Command(const Command& orig) = delete;
    
protected:
    virtual void do_command() = 0;
    void initialize();
        
    void print_cont();
    string get_wrong_params_size_msg(string command);
    void print_pos_in_pipe();
    void print_intermediate_buffer();
    void set_previous_buffer_for_debug();
    
    int get_counter() const;
    void set_counter(int counter);
    string get_previous_buffer_data() const;
    void set_intermediate_buffer(string intermediate_buffer);        
};

#endif /* COMMAND_H */

