//
// Created by California dintist on 2020-05-27.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H
#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    explicit Node(T d = 0):data(d), next(NULL) {}
};

template <typename T>
class Queue {
private:
    Node<T> *head;
    Node<T> *rear;
    int length;
public:
    explicit Queue() : head(new Node<T>), rear(head), length(0) {}

    bool empty() const {return head->next == NULL;}

    size_t size() const { return length; }

    void push(T data);

    void pop();

    T front();

};

template <typename T>
void Queue<T>::push(const T data) {
    auto pNode = new Node<T>(data);
    pNode->next = rear->next;
    rear->next = pNode;
    rear = pNode;

    length++;
}

template <typename T>
T Queue<T>::front() {
    assert(head->next != NULL);
    return head->next->data;
}

template <typename T>
void Queue<T>::pop() {
    Node<T>* pNode = head->next;
    head->next = head->next->next;
    delete pNode;
    length--;
}

#endif //QUEUE_QUEUE_H
