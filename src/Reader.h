#ifndef READER_H
#define READER_H

#include "Thread.h"
#include "IntermediateBuffer.h"

#include <istream>

using std::istream;

class Reader : public Thread {
private:
    istream &input;
    IntermediateBuffer &output;

public:
    Reader(istream &is, IntermediateBuffer &out);

    virtual ~Reader();

    void run();

private:
    Reader() = delete;

    Reader(const Reader &orig) = delete;

};


#endif /* READER_H */
