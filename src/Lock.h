#ifndef LOCK_H
#define LOCK_H

#include <mutex>

class Lock {
    private:
        std::mutex &m;

    public:
        Lock(std::mutex &m);
        ~Lock();

    private:
        Lock(const Lock&) = delete;
        Lock& operator=(const Lock&) = delete;
        Lock(Lock&&) = delete;
        Lock& operator=(Lock&&) = delete;

};


#endif /* LOCK_H */

