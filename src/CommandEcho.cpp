#include "CommandEcho.h"

#include <string>
#include <vector>

/*
 * Uso un singleton para contar la cantidad de comandos que ejecuté. Dejo la
 * la clase dentro de la misma implementación del comando ya que se usa sola-
 * mente aquí adentro, y no justifica meterla en otro cpp.
 */
class CounterEchoSingleton {
public:
    // comentario para que ande cpplint

    static CounterEchoSingleton& instance() {
        static CounterEchoSingleton instance;
        return instance;
    }

    int getIncrementedCounter() {
        return ++counter;
    }

private:
    // comentario para que ande cpplint

    CounterEchoSingleton() {
    }

public:
    CounterEchoSingleton(CounterEchoSingleton const&) = delete;
    void operator=(CounterEchoSingleton const&) = delete;

private:
    int counter = 0;
};

/*
 * Implementación de la clase propiamente dicha.
 */
CommandEcho::CommandEcho()
: Command() {
    initialize();
}

CommandEcho::CommandEcho(vector<string> args, bool is_dbg)
: Command(args, is_dbg) {
    initialize();
}

CommandEcho::~CommandEcho() {
}

void CommandEcho::initialize() {
    int counter = CounterEchoSingleton::instance().getIncrementedCounter();
    set_counter(counter);
}

int CommandEcho::run() {
    do_echo();
    return EXIT_SUCCESS;
}

string CommandEcho::to_string() {
    return "echo";
}

void CommandEcho::do_echo() {
    output = input;
    print_cont();
    set_previous_buffer_for_debug();
    print_intermediate_buffer();
}
