#include "CommandMatch.h"

#include <regex>

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

    CounterMatchSingleton() {
    }

public:
    CounterMatchSingleton(CounterMatchSingleton const&) = delete;
    void operator=(CounterMatchSingleton const&) = delete;

private:
    int counter = 0;
};

/*
 * Implementación de la clase propiamente dicha.
 */
CommandMatch::CommandMatch()
: Command() {
    initialize();
}

CommandMatch::CommandMatch(vector<string> args, bool is_dbg)
: Command(args, is_dbg) {
    initialize();
}

CommandMatch::~CommandMatch() {
}

void CommandMatch::initialize() {
    int counter = CounterMatchSingleton::instance().getIncrementedCounter();
    set_counter(counter);
}

string CommandMatch::to_string() {
    return "match";
}

int CommandMatch::run() {
    int status = EXIT_SUCCESS;

    if (get_arguments().size() == 1) {
        pattern = get_arguments().at(0);
        do_match();
    } else {
        status = EXIT_FAILURE;
        std::cerr << get_wrong_params_size_msg(to_string());
    }

    return status;
}

void CommandMatch::do_match() {
    print_cont();
    set_previous_buffer_for_debug();
    if (std::regex_search(input, std::regex(pattern))) {
        output = input;
    } else {
        output = "";
    }
    print_intermediate_buffer();
}
