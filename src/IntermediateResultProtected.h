#ifndef INTERMEDIATERESULTPROTECTED_H
#define INTERMEDIATERESULTPROTECTED_H

#include <mutex>
#include <string>
#include <queue>
#include <condition_variable>

using std::mutex;
using std::string;
using std::queue;
using std::condition_variable;

class IntermediateResultProtected {
    
public:
    IntermediateResultProtected();
    IntermediateResultProtected(const IntermediateResultProtected& orig);
    IntermediateResultProtected(string v, mutex &m, condition_variable &cv);
    virtual ~IntermediateResultProtected();
    
    string get_next_intermediate_result();
    void add_intermediate_result(string s);
    bool is_previous_ended() const;
    void set_previous_ended(bool is_ended);
    mutex& get_mutex();
    condition_variable& get_condition_variable();
    bool is_processing_yet() const;
    bool has_output() const;

private:
    mutex &m;
    condition_variable &cv;
    queue<string> intermediate_results;
    bool previous_ended;
};

#endif /* INTERMEDIATERESULTPROTECTED_H */

