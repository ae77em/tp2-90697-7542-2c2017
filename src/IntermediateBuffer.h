#ifndef INTERMEDIATE_BUFFER_H
#define INTERMEDIATE_BUFFER_H

#include <string>
#include <queue>

using std::string;
using std::queue;

class IntermediateBuffer {
    
public:
    IntermediateBuffer();
    IntermediateBuffer(const IntermediateBuffer& orig);
    virtual ~IntermediateBuffer();
    
    string get_next_intermediate_result();
    void add_intermediate_result(const string &s);
    bool is_processing_yet() const;
    bool has_output() const;

private:
    queue<string> intermediate_results;
    bool previous_ended;
};

#endif /* INTERMEDIATE_BUFFER_H */

