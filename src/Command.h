#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <regex>
#include <fstream>

using namespace std;

class Command {
public:
    Command();
    Command(const Command& orig);
    virtual ~Command();
    
    void echo(string &text, ostream &output);
    string match(string input);
    string replace(string pattern, string replacement);
    void pipeline();
    
    
private:

};

#endif /* COMMANDS_H */

