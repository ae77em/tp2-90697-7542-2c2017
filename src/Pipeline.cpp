#include "Pipeline.h"

#include "StringUtils.h"
#include "CommandFactory.h"
#include "Reader.h"
#include "Writer.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

Pipeline::Pipeline(std::istream &is,
                   std::ostream &os,
        bool is_dbg,
        const string &cmds)
: input(is), output(os), is_debug(is_dbg) {
    initialize(cmds);
}

void Pipeline::initialize(const string &cmds) {
    vector<string> cmds_list = StringUtils::split(cmds, PIPELINE_DELIMITER);
    vector<string> splitted_cmd;

    string cmd;
    string entire_cmd;
    int pos_in_pipe = 0;

    IntermediateBuffer *previous = new IntermediateBuffer();
    buffers.push_back(previous);

    for (int i = 0; i < (int) cmds_list.size(); ++i) {
        IntermediateBuffer *next = new IntermediateBuffer();

        entire_cmd = cmds_list.at(i);
        splitted_cmd = StringUtils::split(entire_cmd, PARAM_SEPARATOR);
        cmd = splitted_cmd.at(0);
        vector<string> args(splitted_cmd.begin() + 1, splitted_cmd.end());

        if (is_debug){
            pos_in_pipe = i + 1;
        }

        Command *command = CommandFactory::createCommand(cmd,
                args,
                is_debug,
                *previous,
                *next,
                pos_in_pipe);

        commands.push_back(command);

        previous = next;
        buffers.push_back(previous);
    }
}

Pipeline::~Pipeline() {
    for (IntermediateBuffer *ib : buffers){
        delete ib;
    }
    buffers.clear();
    commands.clear();
}

void Pipeline::run() {
    vector<Thread *> threads;
    Command *first_command = commands.front();
    Command *last_command = commands.back();
    Reader *reader = new Reader(input, first_command->get_source_buffer());
    Writer *writer = new Writer(last_command->get_dest_buffer(), output);

    threads.push_back(reader);

    for (Command *c : commands) {
        threads.push_back(c);
    }

    threads.push_back(writer);

    for (Thread *t : threads) {
        t->start();
    }

    int size = (int) threads.size();
    std::string err = "";
    for (int i = 0; i < size; ++i) {
        threads[i]->join();

        if (is_debug){
            if (i > 0 && i < size - 1){
                Command *c = dynamic_cast<Command*>(threads[i]);
                err = c->get_debug_text();
                std::cerr << err;
                if (i != size - 2){
                    std::cerr << std::endl;
                }
            }
        }

        delete threads[i];
    }
}
