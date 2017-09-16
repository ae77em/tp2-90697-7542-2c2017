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
    static std::string ltrim(const std::string &s);
    static std::string rtrim(const std::string &s);
    static std::string trim(const std::string &s);
};

#endif /* UTILS_H */

