#ifndef READER_H
#define READER_H

#include "Thread.h"
#include "IntermediateBuffer.h"

#include <istream>

class Reader : public Thread {
private:
    std::istream &input;
    IntermediateBuffer &output;

public:
    Reader(std::istream &is, IntermediateBuffer &out);

    virtual ~Reader();

    void run();

private:
    Reader() = delete;

    Reader(const Reader &orig) = delete;
};
#endif /* READER_H */
