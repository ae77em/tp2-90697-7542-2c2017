#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

#include "Pipeline.h"

using std::istream;
using std::ifstream;
using std::ostream;
using std::ofstream;
using std::string;
using std::cin;
using std::cout;

#define OPT_INPUT "--input"
#define OPT_OUTPUT "--output"
#define OPT_DEBUG "--debug"

int runPipeline(string, string, bool, string);

int main(int argc, char** argv) {
    if (argc <= 1){
        return EXIT_FAILURE;
    }

    string param;
    string input = "";
    string output = "";
    bool is_debug = false;
    string pipeline_params = "";

    for (int i = 1; i < argc; i++) {
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

    std::istream input(NULL);
    std::ostream output(NULL);
    std::ifstream ifile;
    std::ofstream ofile;

    if (infile == ""){
        input.rdbuf(std::cin.rdbuf());
    } else {
        ifile.open(infile.c_str(), std::ios_base::in);
        input.rdbuf(ifile.rdbuf());
    }

    if (outfile == ""){
        output.rdbuf(std::cout.rdbuf());
    } else {
        ofile.open(outfile.c_str(), std::ios_base::out);
        output.rdbuf(ofile.rdbuf());
    }

    pipeline = new Pipeline(input, output, is_dbg, params);

    pipeline->run();
    delete pipeline;

    return EXIT_SUCCESS;
}

