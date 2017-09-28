#ifndef COMMAND_H
#define COMMAND_H

#include "Thread.h"
#include "IntermediateBuffer.h"

#include <string>
#include <vector>

class Command : public Thread {
protected:
    int pos_in_pipe = 0;
    std::string input = "";
    std::string output = "";
    std::string error = "";
    std::vector<std::string> arguments;
    bool is_debug;
    int counter;
    IntermediateBuffer &source_buffer;
    IntermediateBuffer &dest_buffer;
           
public:
    Command(std::vector<std::string> args, 
            bool is_dbg, 
            IntermediateBuffer &previous_buffer,
            IntermediateBuffer &next_buffer,
            int pos_in_pipe);
    virtual ~Command();
    
    void run();
    
    virtual std::string to_string();

    std::vector<std::string> get_arguments() const;

    IntermediateBuffer &get_source_buffer();
    IntermediateBuffer &get_dest_buffer();
    
    std::string get_debug_text();

private:
    Command() = delete;
    Command(const Command& orig) = delete;
    
protected:
    virtual void do_command();
    virtual void load_error_buffer();
    void initialize();
    
    void load_input_from_source();
    void load_dest_from_output();
        
    std::string get_error_header();
    std::string get_wrong_params_size_msg(std::string command);

    void set_counter(int counter);
};

#endif /* COMMAND_H */

