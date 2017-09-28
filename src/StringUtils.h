#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

class StringUtils {
public:
    StringUtils();
    StringUtils(const StringUtils& orig);
    virtual ~StringUtils();
    
    static std::vector<std::string> split(const std::string &s,
                                            const std::string &delimiters);
};

#endif /* UTILS_H */

