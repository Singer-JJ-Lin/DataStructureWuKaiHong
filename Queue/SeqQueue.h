//
// Created by Only Blue on 2020-05-27.
//

#ifndef QUEUE_SEQQUEUE_H
#define QUEUE_SEQQUEUE_H
#include <iostream>
#include <cassert>
using namespace std;

const int MAX_SIZE = 100;

template <typename T>
class SeqQueue {
private:
    T queue[MAX_SIZE];
    int head;
    int rear;
    int count;
public:
    SeqQueue() : head(0), rear(0), count(0) {}

    bool empty() const { return count == 0; }

    bool push(T data);

    bool pop();

    T front() const;

    int size() const {return count; }
};

template <typename T>
bool SeqQueue<T>::push(const T data) {
    if (count > 0 && head == rear) {
        std::cout << "Queue is full, can't push!" << endl;
        return false;
    } else {
        queue[rear] = data;
        rear = (rear + 1) % MAX_SIZE;
        count++;
        return true;
    }
}

template <typename T>
bool SeqQueue<T>::pop() {
    if (empty()) {
        cout << "Queue is empty, can't pop!" << endl;
        return false;
    }

    else {
        head = (head + 1) % MAX_SIZE;
        count--;
        return true;
    }
}

template <typename T>
T SeqQueue<T>::front() const {
    assert(count > 0);
    return queue[head];
}

#endif //QUEUE_SEQQUEUE_H
