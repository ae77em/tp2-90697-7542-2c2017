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

    vector<string> get_arguments() const;
    void load_in_next_buffer(string str);

    void set_buffer_is_ready(bool ir);
    
    IntermediateBuffer &get_previous_buffer();
    IntermediateBuffer &get_next_buffer();

private:
    Command() = delete;
    Command(const Command& orig) = delete;
    
protected:
    virtual void do_command();
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

