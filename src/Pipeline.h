#ifndef PIPELINE_H
#define PIPELINE_H

#include "Command.h"

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <list>
#include <exception>

#define PARAM_SEPARATOR "#|#"
#define PIPELINE_DELIMITER "::"

class Pipeline {
private:
    std::istream& input;
    std::ostream& output;
    bool is_debug;    
    std::list<Command*> commands;
    std::list<IntermediateBuffer*> buffers;
    
public:
    Pipeline(std::istream& is, 
            std::ostream& os, 
            bool is_dbg, 
            const std::string &cmds);
    Pipeline(const Pipeline& orig);
    virtual ~Pipeline();
    
    void run();
private:
    Pipeline() = delete;
    void initialize(const std::string &commands);
};

#endif /* PIPELINE_H */
