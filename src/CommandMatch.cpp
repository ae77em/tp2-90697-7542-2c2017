#include "CommandMatch.h"

#include <regex>
#include <string>
#include <vector>
#include <iostream>

/*
 * Uso un singleton para contar la cantidad de comandos que ejecuté. Dejo la
 * la clase dentro de la misma implementación del comando ya que se usa sola-
 * mente aquí adentro, y no justifica meterla en otro cpp.
 */
class CounterMatchSingleton {
public:
    static CounterMatchSingleton& instance() {
        static CounterMatchSingleton instance;
        return instance;
    }

    int getIncrementedCounter() {
        return ++counter;
    }

private:
    CounterMatchSingleton() { }

public:
    CounterMatchSingleton(CounterMatchSingleton const&) = delete;
    void operator=(CounterMatchSingleton const&) = delete;

private:
    int counter = 0;
};

/*
 * Implementación de la clase propiamente dicha.
 */
CommandMatch::CommandMatch(std::vector<std::string> args,
        bool is_dbg,
        IntermediateBuffer &previous_buffer,
        IntermediateBuffer &next_buffer,
        int pos_in_pipe)
: Command(args, is_dbg, previous_buffer, next_buffer, pos_in_pipe) {
    if (arguments.size() == 1) {
        initialize();
    } else {
        std::cerr << get_wrong_params_size_msg(to_string());
        throw get_wrong_params_size_msg(to_string());
    }
}

CommandMatch::~CommandMatch() {
}

void CommandMatch::initialize() {
    int ctr = CounterMatchSingleton::instance().getIncrementedCounter();
    counter = ctr;
    pattern = arguments.at(0);
}

string CommandMatch::to_string() {
    return "match";
}

void CommandMatch::do_command() {
    if (std::regex_search(input, std::regex(pattern))) {
        output = input;
    } else {
        output = "";
    }
}

void CommandMatch::load_error_buffer(){
    if (!input.empty()){
        error.append(input);
        error.append(" -> ");

        if (output.empty()){
            error.append("(Filtrado)");
        } else {
            error.append(output);
        }
        error.append("\n");
    }
}
