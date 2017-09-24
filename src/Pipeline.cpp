#include "Pipeline.h"
#include "Reader.h"
#include "Writter.h"

using std::vector;
using std::string;
using std::thread;

Pipeline::Pipeline(istream &is = std::cin,
        ostream &os = std::cout,
        bool is_dbg = false,
        const string &cmds = "")
: input(&is, [](istream *) {
}), output(&os, [](ostream *) {
})

, is_debug(is_dbg) {
    initialize(cmds);
}

Pipeline::Pipeline(istream &is,
        string filename,
        bool is_dbg = false,
        const string &cmds = "") :
input(&is, [](istream *) {
})

,
output(new std::ofstream(filename),
        std::default_delete<std::ostream>()),
is_debug(is_dbg) {
    if (!dynamic_cast<std::ofstream &> (*output).is_open()) {
        throw exception();
    }

    initialize(cmds);
}

Pipeline::Pipeline(string filename,
        ostream &os,
        bool is_dbg = false,
        const string &cmds = "") :
input(new std::ifstream(filename), std::default_delete<std::istream>()),
output(&os, [](ostream *) {
})

, is_debug(is_dbg) {
    if (!dynamic_cast<std::ifstream &> (*input).is_open()) {
        throw exception();
    }

    initialize(cmds);
}

Pipeline::Pipeline(string ifilename,
        string ofilename,
        bool is_dbg = false,
        const string &cmds = "")
: input(new std::ifstream(ifilename),
std::default_delete<std::istream>()),
output(new std::ofstream(ofilename),
std::default_delete<std::ostream>()),
is_debug(is_dbg) {
    if (!dynamic_cast<std::ifstream &> (*input).is_open()) {
        throw exception();
    }

    if (!dynamic_cast<std::ofstream &> (*output).is_open()) {
        dynamic_cast<std::ifstream &> (*input).close();
        throw exception();
    }

    initialize(cmds);
}

void Pipeline::initialize(const string &cmds) {
    vector<string> cmds_list = StringUtils::split(cmds, PIPELINE_DELIMITER);
    vector<string> splitted_cmd;

    string cmd;
    string entire_cmd;

    IntermediateBuffer *previous = new IntermediateBuffer();

    for (int i = 0; i < (int) cmds_list.size(); ++i) {
        IntermediateBuffer *next = new IntermediateBuffer();

        entire_cmd = cmds_list.at(i);
        splitted_cmd = StringUtils::split(entire_cmd, PARAM_SEPARATOR);
        cmd = splitted_cmd.at(0);
        vector<string> args(splitted_cmd.begin() + 1, splitted_cmd.end());

        Command *command = CommandFactory::createCommand(cmd,
                args,
                is_debug,
                *previous,
                *next);

        commands.push_back(command);

        previous = next;
    }
}

bool is_deleted(Command *command) {
    //delete command;
    return true;
}

Pipeline::~Pipeline() {
    commands.remove_if(is_deleted);
}

void Pipeline::run() {
    istream &in = dynamic_cast<istream &> (*input);
    ostream &out = dynamic_cast<ostream &> (*output);

    std::vector<Thread *> threads;
    Command *first_command = commands.front();
    Command *last_command = commands.back();
    Reader *reader = new Reader(in, first_command->get_previous_buffer());
    Writter *writter = new Writter(last_command->get_next_buffer(), out);

    threads.push_back(reader);

    for (Command *c : commands) {
        threads.push_back(c);
    }

    threads.push_back(writter);

    for (Thread *t : threads) {
        t->start();
    }

    int size = (int) threads.size();
    for (int i = 0; i < size; ++i) {
        threads[i]->join();
        delete threads[i];
    }
}
