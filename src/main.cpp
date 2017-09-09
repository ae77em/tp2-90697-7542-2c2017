#include <cstdlib>
#include <iostream>

#include "Command.h"

using namespace std;

int main(int argc, char** argv) {

    Command command;
    string str = "saraza";
    ofstream test_out("test.out", std::ofstream::out);
    
    command.echo(str, test_out);
    cout << command.match("saraza") << "\n";
    cout << command.replace("saraza", "sorozo") << "\n";
    
    return 0;
}

