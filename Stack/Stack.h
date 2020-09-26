//
// Created by California dintist on 2020-05-27.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H
#include <iostream>
using namespace std;
template <typename T>
class Node {
public:
    T data;
    Node* next;
    explicit Node(T d = 0):data(d), next(NULL) {}
};

template <typename T>
class Stack {
private:
    Node<T>* head;
    int stack_size;
public:
    explicit Stack(): stack_size(0), head(new Node<T>) {}
    ~Stack();
    // 判断是否为空
    bool empty() const {return head->next == NULL; }
    // 栈大小
    size_t size() const {return stack_size; }
    // 取栈顶元素
    T top() const;
    // 出栈
    bool pop();
    // 入栈
    void push(T data);
};

template <typename T>
Stack<T>::~Stack() {
    if (head == NULL)
        return;
    Node<T> *p = head;
    while (head) {
        p = head->next;
        delete head;
        head = p;
    }
}

template <typename T>
T Stack<T>::top () const {
    static_assert(head->next != NULL);
    return head->next->data;
}

template <typename T>
bool Stack<T>::pop() {
    if(empty()){
        std::cout << "Stack is empty, can't pop!" << std::endl;
        return false;
    }
    head->next = head->next->next;
    stack_size--;
    return true;
}

template <typename T>
void Stack<T>::push(const T data) {
    auto* pNode = new Node<T>(data);
    pNode->next = head->next;
    head->next = pNode;
}
#endif //STACK_STACK_H
