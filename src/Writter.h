#ifndef WRITTER_H
#define WRITTER_H

#include "Thread.h"
#include "IntermediateBuffer.h"

#include <ostream>

using std::ostream;

class Writter : public Thread {
private:
    IntermediateBuffer &input;
    ostream &output;

public:
    Writter(IntermediateBuffer &in, ostream &out);

    virtual ~Writter();

    void run();

private:
    Writter() = delete;

    Writter(const Writter &orig) = delete;

};




#endif /* WRITTER_H */
