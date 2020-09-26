//
// Created by California dintist on 2020-05-27.
//

#ifndef QUEUE_PRIORITYQUEUE_H
#define QUEUE_PRIORITYQUEUE_H
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template <typename T, class Compare>
class Priority_Queue {
private:
    vector<T> PQ;
    Compare cmp;
public:
    int size() const {return PQ.size(); }

    int empty() const {return PQ.empty(); }

    T front() const {assert(!PQ.empty()); return PQ[0]; }

    void push(const T data) {PQ.push_back(data); sort(PQ.begin(), PQ.end(), cmp); }

    void pop() {typename vector<T>::iterator it = PQ.begin(); PQ.erase(it); }

};
#endif //QUEUE_PRIORITYQUEUE_H
