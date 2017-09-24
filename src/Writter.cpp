#include "Writter.h"

#include <iostream>

Writter::Writter(IntermediateBuffer &in, ostream &out)
: input(in), output(out) {
}

Writter::~Writter() {
}

void Writter::run() {
    string result;
    //std::cout << "Entre a correr: writter" << std::endl;
    while (input.is_processing_yet()) {
        //std::cout << "Voy a ejecutar: writter" << std::endl;
        if (input.find_and_store_next_output(result)) {
            output << result << std::endl;
        }
        //std::cout << "Ejecuté: writter" << std::endl;
    }
    //std::cout << "Salí de: writter" << std::endl;
}