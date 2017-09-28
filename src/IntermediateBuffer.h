#ifndef INTERMEDIATE_BUFFER_H
#define INTERMEDIATE_BUFFER_H

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

using std::string;
using std::queue;
using std::mutex;
using std::condition_variable;
using std::unique_lock;

class IntermediateBuffer {
private:
    mutex m;
    condition_variable cv;
    
public:
    IntermediateBuffer();
    IntermediateBuffer(const IntermediateBuffer& orig);
    virtual ~IntermediateBuffer();
    
    string find_and_store_next_output();
    void add_intermediate_result(const string &s);
    bool is_processing_yet() const;
    bool has_output() const;
    bool is_ended() const;
    void set_previous_ended(bool ended);

private:
    queue<string> intermediate_results;
    bool previous_ended = false;
};

#endif /* INTERMEDIATE_BUFFER_H */

