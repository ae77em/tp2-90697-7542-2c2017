#include "Command.h"

using namespace std;

Command::Command() {
}

Command::Command(const Command& orig) {
}

Command::~Command() {
}

void Command::echo(string &text, ostream &output){
    output << text << "\n";
}

string Command::match(string input){
    string output = "match " + input;
    
    return output;
}

string Command::replace(string pattern, string replacement){
    string output = "replace " + pattern + " " + replacement;
    
    return output;
}

void Command::pipeline(){
    
}

