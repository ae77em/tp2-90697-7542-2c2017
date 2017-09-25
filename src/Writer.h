#ifndef WRITTER_H
#define WRITTER_H

#include "Thread.h"
#include "IntermediateBuffer.h"

#include <ostream>
#include <mutex>
#include <condition_variable>
#include <string>

using std::ostream;
using std::string;

class Writer : public Thread {
private:
    IntermediateBuffer &input;
    ostream &output;

public:
    Writer(IntermediateBuffer &in, ostream &out);

    virtual ~Writer();

    void run();

private:
    Writer() = delete;

    Writer(const Writer &orig) = delete;
};

#endif /* WRITTER_H */
