#include "StringUtils.h"
#include "Command.h"

#include <cassert>
#include <iostream>
#include <vector>

static void ltrimTest() {
    std::string aaa("aaa ");
    std::string ltrimstr(" aaa ");
    ltrimstr = StringUtils::ltrim(ltrimstr);
    assert(aaa.compare(ltrimstr) == 0);

    std::string bbb("b  bb ");
    std::string ltrimstr2(" b  bb ");
    ltrimstr2 = StringUtils::ltrim(ltrimstr2);
    assert(bbb.compare(ltrimstr2) == 0);

    std::cout << "Corrida de tests ltrim exitosa.\n";
}

static void rtrimTest() {
    std::string aaa(" aaa");
    std::string rtrimstr(" aaa ");
    rtrimstr = StringUtils::rtrim(rtrimstr);
    assert(aaa.compare(rtrimstr) == 0);

    std::string bbb(" b  bb");
    std::string rtrimstr2(" b  bb ");
    rtrimstr2 = StringUtils::rtrim(rtrimstr2);
    assert(bbb.compare(rtrimstr2) == 0);

    std::cout << "Corrida de tests rtrim exitosa.\n";
}

static void trimTest() {
    std::string aaa("aaa");
    std::string trimstr(" aaa ");
    trimstr = StringUtils::trim(trimstr);
    assert(aaa.compare(trimstr) == 0);

    std::string bbb("b  bb");
    std::string trimstr2(" b  bb ");
    trimstr2 = StringUtils::trim(trimstr2);
    assert(bbb.compare(trimstr2) == 0);

    std::cout << "Corrida de tests trim exitosa.\n";
}

static void splitTest() {
    std::string toBeSplitted(" aa :: bb :: cc :: ");
    std::string delimiter = "::";
    std::vector<std::string> splittedValues = StringUtils::split(toBeSplitted, delimiter);
    const std::vector<std::string> values({"aa", "bb", "cc"});

    for (unsigned int i = 0; i < splittedValues.size(); i++) {
        assert(values.at(i).compare(splittedValues.at(i)) == 0);
    }

    std::cout << "Corrida de tests split exitosa.\n";
}

void stringUtilsTest() {
    ltrimTest();
    rtrimTest();
    trimTest();
    splitTest();

    std::cout << "Corrida de tests exitosa.\n";
}

void testEcho() {
    std::cout << "Inicia test echo...\n";

    string ifilename("input.txt");
    string ofilename("output.txt");
    Command *cmd = new Command(ifilename, ofilename, false);
    string to_print("texto lindo");
    cmd->echo(to_print);
    cmd->echo();

    delete(cmd);

    std::cout << "Finaliza test echo...\n";
}

void testMatch() {
    std::cout << "Inicia test match...\n";

    string ifilename("input.txt");
    string ofilename("output.txt");
    Command *cmd = new Command(ifilename, ofilename, false);

    string regex("(tra)(.*)");
    cmd->match(regex);

    delete(cmd);

    std::cout << "Finaliza test match...\n";
}

void testReplace() {
    std::cout << "Inicia test replace...\n";

    string ifilename("input.txt");
    string ofilename("output.txt");
    Command *cmd = new Command(ifilename, ofilename, false);

    string regex("\\b(e)");
    cmd->replace(regex, "O");

    delete(cmd);

    std::cout << "Finaliza test replace...\n";
}

void commandTest() {
    testEcho();
    testMatch();
    testReplace();
}
