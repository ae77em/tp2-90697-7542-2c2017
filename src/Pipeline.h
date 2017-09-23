#ifndef PIPELINE_H
#define PIPELINE_H

#include "CommandFactory.h"
#include "StringUtils.h"
#include "IntermediateBuffer.h"

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <list>
#include <exception>

using std::istream;
using std::ostream;
using std::function;
using std::string;
using std::unique_ptr;
using std::list;
using std::vector;
using std::exception;

#define PARAM_SEPARATOR "#|#"
#define PIPELINE_DELIMITER "::"

class Pipeline {
private:
    unique_ptr<istream, function<void(istream*)>> input;
    unique_ptr<ostream, function<void(ostream*)>> output;
    bool is_debug;    
    list<Command*> commands;
    
public:
    Pipeline();
    Pipeline(istream& is, ostream& os, bool is_dbg, const string &cmds);
    Pipeline(istream& is, string filename, bool is_dbg, const string &cmds);
    Pipeline(string ifn, ostream& os, bool is_dbg, const string &cmds);
    Pipeline(string ifn, string ofn, bool is_dbg, const string &cmds);
    Pipeline(const Pipeline& orig);
    virtual ~Pipeline();
    
    void run();
private:
    void initialize(const string &commands);
};

#endif /* PIPELINE_H */

