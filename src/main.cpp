#include <cstdlib>
#include <iostream>
#include <string>

#include "Command.h"
#include "Tests.h"

using std::istream;
using std::string;
using std::cin;
using std::cout;

#define OPT_INPUT "--input"
#define OPT_OUTPUT "--output"
#define OPT_DEBUG "--debug"

int runCommand(string, string, bool, string);

int main(int argc, char** argv) {

    /* * Recorrer los parametros
     * * Una vez identificados los parámetros de construcción del comando
     * inicial.
     * * Esplitear los otros comandos.
     */

    string param;
    string input = "";
    string output = "";
    bool is_debug = false;
    string pipeline_params = "";

    for (int i = 1; i < argc; i++) { // el 0 es el nombre del programa
        param = string(argv[i]);

        if (param.compare(OPT_INPUT) == 0) {
            i++;
            input = argv[i];
        } else if (param.compare(OPT_OUTPUT) == 0) {
            i++;
            output = argv[i];
        } else if (param.compare(OPT_DEBUG) == 0) {
            is_debug = true;
        } else {
            pipeline_params += param;
            if (i < argc - 1) {
                pipeline_params += PARAM_SEPARATOR;
            }
        }
    }

    return runCommand(input, output, is_debug, pipeline_params);
}

int runCommand(string infile, string outfile, bool is_dbg, string params) {
    Command *command;

    if (infile == "" && outfile == "") {
        command = new Command(cin, cout, is_dbg);
    } else if (infile != "" && outfile == "") {
        command = new Command(infile, cout, is_dbg);
    } else if (infile == "" && outfile != "") {
        command = new Command(cin, outfile, is_dbg);
    } else {
        command = new Command(infile, outfile, is_dbg);
    }

    command->pipeline(params);

    return EXIT_SUCCESS;
}

