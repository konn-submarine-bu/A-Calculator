#ifndef STACK_H
#define STACK_H

#include "vector.h"

template <typename T>
class stack: public vector<T>
{
    public:
        void push (T const e)
        {
            this->insert(this->size(),e);
        }
        T pop()
        {
            return this->remove(this->size()-1);
        }
        T & top()
        {
            return (*this)[this->size()-1];
        }
};

#endif // STACK_H
