#include "CommandReplace.h"

/*
 * Uso un singleton para contar la cantidad de comandos que ejecuté. Dejo la
 * la clase dentro de la misma implementación del comando ya que se usa sola-
 * mente aquí adentro, y no justifica meterla en otro cpp.
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

    CounterReplaceSingleton() {
    }

public:
    CounterReplaceSingleton(CounterReplaceSingleton const&) = delete;
    void operator=(CounterReplaceSingleton const&) = delete;

private:
    int counter = 0;
};

/*
 * Implementación de la clase propiamente dicha.
 */
CommandReplace::CommandReplace()
: Command() {
    initialize();
}

CommandReplace::CommandReplace(vector<string> args, bool is_dbg)
: Command(args, is_dbg) {
    initialize();
}

CommandReplace::~CommandReplace() {
}

void CommandReplace::initialize() {
    int counter = CounterReplaceSingleton::instance().getIncrementedCounter();
    set_counter(counter);
}

int CommandReplace::run() {
    int status = EXIT_SUCCESS;

    if (get_arguments().size() == 2) {
        pattern = get_arguments().at(0);
        replacement = get_arguments().at(1);
        do_replace();
    } else {
        status = EXIT_FAILURE;
        std::cerr << get_wrong_params_size_msg("replace");
    }

    return status;
}

void CommandReplace::do_replace() {
    print_cont();
    set_previous_buffer_for_debug();
    output = std::regex_replace(
            input,
            std::regex(pattern),
            replacement);
    print_intermediate_buffer();
}

string CommandReplace::to_string() {
    return "replace";
}
