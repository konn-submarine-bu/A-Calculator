#ifndef QUEUE_H
#define QUEUE_H

#include "vector.h"
template <typename T>
class queue :public vector<T>
{
public:
    void enqueue(T e) {this->insert(e);}
    T dequeue(){return this->remove(0);}
    T front() {return this->get(0);}
};


#endif // QUEUE_H
