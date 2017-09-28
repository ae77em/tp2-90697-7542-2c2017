#include "StringUtils.h"

#include <cstddef>
#include <string>
#include <vector>

StringUtils::StringUtils() {
}

StringUtils::StringUtils(const StringUtils& orig) {
}

StringUtils::~StringUtils() {
}

std::vector<std::string> StringUtils::split(const std::string &s,
        const std::string &delimiter) {
    std::vector<std::string> result;
    size_t next;
    size_t last = 0;
    std::string aResult;
    bool is_finished = false;

    while (!is_finished) {
        if ((next = s.find(delimiter, last)) == std::string::npos) {
            next = s.length();
            is_finished = true;
        }

        if (next > last) {
            aResult = s.substr(last, next - last);
            result.push_back(aResult);
        } else if (next > 0 && next == last && !is_finished){
            aResult = "";
            result.push_back(aResult);
        }
        last = next + delimiter.length();
    }
    return result;
}
