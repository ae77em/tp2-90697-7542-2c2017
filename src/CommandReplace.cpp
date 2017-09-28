#include "CommandReplace.h"

#include <string>
#include <vector>
#include <iostream>

/*
 * Uso un singleton para contar la cantidad de comandos que ejecuté.
 */
class CounterReplaceSingleton {
public:
    static CounterReplaceSingleton& instance() {
        static CounterReplaceSingleton instance;
        return instance;
    }

    int getIncrementedCounter() {
        return ++counter;
    }

private:
    CounterReplaceSingleton() { }

public:
    CounterReplaceSingleton(CounterReplaceSingleton const&) = delete;
    void operator=(CounterReplaceSingleton const&) = delete;

private:
    int counter = 0;
};

/*
 * Implementación de la clase propiamente dicha.
 */
CommandReplace::CommandReplace(vector<string> args,
        bool is_dbg,
        IntermediateBuffer &previous_buffer,
        IntermediateBuffer &next_buffer,
        int pos_in_pipe)
: Command(args, is_dbg, previous_buffer, next_buffer, pos_in_pipe) {
    if (arguments.size() == 2) {
        initialize();
    } else {
        std::cerr << get_wrong_params_size_msg("replace");
        throw get_wrong_params_size_msg("replace");
    }
}

CommandReplace::~CommandReplace() { }

void CommandReplace::initialize() {
    int ctr = CounterReplaceSingleton::instance().getIncrementedCounter();
    counter = ctr;
    pattern = get_arguments().at(0);
    replacement = get_arguments().at(1);
}

void CommandReplace::do_command() {
    output = std::regex_replace(
            input,
            std::regex(pattern),
            replacement);
}

string CommandReplace::to_string() {
    return "replace";
}
