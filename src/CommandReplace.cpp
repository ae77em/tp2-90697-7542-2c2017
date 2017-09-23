#include "CommandReplace.h"

/*
 * Uso un singleton para contar la cantidad de comandos que ejecuté. Dejo la
 * la clase dentro de la misma implementación del comando ya que se usa sola-
 * mente aquí adentro, y no justifica meterla en otro cpp.
 */
class CounterReplaceSingleton {
public:
    // comentario para que ande cpplint

    static CounterReplaceSingleton& instance() {
        static CounterReplaceSingleton instance;
        return instance;
    }

    int getIncrementedCounter() {
        return ++counter;
    }

private:
    // comentario para que ande cpplint

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
CommandReplace::CommandReplace(vector<string> args,
        bool is_dbg,
        IntermediateBuffer &previous_buffer,
        IntermediateBuffer &next_buffer)
: Command(args, is_dbg, previous_buffer, next_buffer) {
    if (arguments.size() == 2) {
        initialize();
    } else {
        std::cerr << get_wrong_params_size_msg("replace");
        throw get_wrong_params_size_msg("replace");
    }
}

CommandReplace::~CommandReplace() {
}

void CommandReplace::initialize() {
    int ctr = CounterReplaceSingleton::instance().getIncrementedCounter();
    counter = ctr;
    pattern = get_arguments().at(0);
    replacement = get_arguments().at(1);
}

void CommandReplace::do_command() {
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
