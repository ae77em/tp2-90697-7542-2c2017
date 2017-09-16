#include <cstdlib>
#include <iostream>
#include <string>

#include "Pipeline.h"

using std::istream;
using std::string;
using std::cin;
using std::cout;

#define OPT_INPUT "--input"
#define OPT_OUTPUT "--output"
#define OPT_DEBUG "--debug"

int runPipeline(string, string, bool, string);

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

    return runPipeline(input, output, is_debug, pipeline_params);
}

int runPipeline(string infile, string outfile, bool is_dbg, string params) {
    Pipeline *pipeline;

    if (infile == "" && outfile == "") {
        pipeline = new Pipeline(cin, cout, is_dbg, params);
    } else if (infile != "" && outfile == "") {
        pipeline = new Pipeline(infile, cout, is_dbg, params);
    } else if (infile == "" && outfile != "") {
        pipeline = new Pipeline(cin, outfile, is_dbg, params);
    } else {
        pipeline = new Pipeline(infile, outfile, is_dbg, params);
    }

    pipeline->run();
    delete pipeline;

    return EXIT_SUCCESS;
}

