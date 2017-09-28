#ifndef WRITTER_H
#define WRITTER_H

#include "Thread.h"
#include "IntermediateBuffer.h"

#include <ostream>
#include <string>

class Writer : public Thread {
private:
    IntermediateBuffer &input;
    std::ostream &output;

public:
    Writer(IntermediateBuffer &in, std::ostream &out);

    virtual ~Writer();

    void run();

private:
    Writer() = delete;

    Writer(const Writer &orig) = delete;
};

#endif /* WRITTER_H */
