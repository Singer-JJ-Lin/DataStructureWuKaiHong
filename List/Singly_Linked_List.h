//
// Created by Only Blue on 2020/6/3.
//

#ifndef LIST_SINGLY_LINKED_LIST_H
#define LIST_SINGLY_LINKED_LIST_H

#include <iostream>
#include <iomanip>
#include <cassert>

template <typename T>
struct Node {
    T data;
    Node* next;
    explicit Node(T data = 0):data(data), next(nullptr) {}
};

template <typename T>
class SinglyLinkedListWithHead {
private:
    Node<T>* head;
    int size;
public:
    // 构造函数
    SinglyLinkedListWithHead(): head(new Node<T>),size(0) {}
    // 拷贝构造
    SinglyLinkedListWithHead(const SinglyLinkedListWithHead<T> &SL);
    // 运算符重载
    SinglyLinkedListWithHead<T>& operator=(const SinglyLinkedListWithHead<T> &SL);
    // 析构函数
    ~SinglyLinkedListWithHead() {destroy(); }
    // 判断单链表是否为空
    bool empty() const {return size == 0; }
    // 取头节点
    Node<T>* getHead() const {return head; }
    // 清空链表
    void clear();
    // 链表长度
    int length() const {return size; }
    // 尾插
    void push_back(T data);
    // 头插
    void push_front(T data);
    // 删除表头节点
    void pop_back();
    // 删除表尾节点
    void pop_front();
    // 删除第一个与val相同的节点，释放该节点的资源
    void remove_first(T val);
    // 删除所有与val相同的节点，释放该节点的资源
    void remove_all(T val);
    // 按序号删除节点
    void erase(int index);
    // 指定位置插入
    void insert(T data, int index);
    // 排序
    void sort(bool(*Compare)(T, T));

protected:
    // 销毁链表
    void destroy();
};

template <typename T>
void SinglyLinkedListWithHead<T>:: clear() {
    if (empty()) {
        return;
    }

    Node<T> *pNode = head->next;
    Node<T> *pTemp = nullptr;
    while (pNode) {
        pTemp = pNode->next;
        delete pNode;
        pNode = nullptr;
        pNode = pTemp;
    }
}

template <typename T>
void SinglyLinkedListWithHead<T>::destroy() {
    clear();
    delete head;
    head = nullptr;
}

template <typename T>
void SinglyLinkedListWithHead<T>::push_back(T data) {
    auto pNode = head;

    while (pNode->next) {
        pNode = pNode->next;
    }

    auto *newNode = new Node<T>(data);
    pNode->next = newNode;
    size++;
}

template <typename T>
void SinglyLinkedListWithHead<T>::push_front(T data) {
    auto *newNode = new Node<T>(data);
    newNode->next = head->next;
    head->next = newNode;
    size++;
}

template <typename T>
void SinglyLinkedListWithHead<T>::pop_back() {
    if (empty())
        return;

    if(size == 1) {
        delete head->next;
        head->next = nullptr;
        size = 0;
    }

    Node<T> *pNode = head->next;
    while (pNode->next->next) {
        pNode = pNode->next;
    }

    delete (pNode->next);
    pNode->next = nullptr;
    size--;
}

template <typename T>
void SinglyLinkedListWithHead<T>::pop_front() {
    if (empty())
        return;

    auto pNode = head->next;
    head->next = head->next->next;
    delete pNode;
    size--;
}

template <typename T>
void SinglyLinkedListWithHead<T>::sort(bool(*Compare)(T, T)) {
    if (empty()) {
        return;
    }

    Node<T> *pNode = head->next, *qNode = nullptr, *curr = nullptr, *preNode = nullptr;
    head->next = nullptr;

    while (true) {
        while (pNode) {
            curr = head->next;
            preNode = head;

            while (curr && Compare(curr, pNode)) {
                preNode = curr;
                curr = curr->next;
            }

            qNode = pNode;
            pNode = pNode->next;
            qNode->next = preNode->next;
            preNode->next = qNode;
        }
        break;
    }
}

template <typename T>
void SinglyLinkedListWithHead<T>::remove_first(T val) {
    if (empty())
        return;

    auto pNode = head->next;
    auto preNode = head;
    while (pNode) {
        if (pNode->data == val) {
            preNode->next = pNode->next;
            delete pNode;
            pNode = nullptr;
            size--;
            break;
        }
        preNode = preNode->next;
        pNode = pNode->next;
    }
}

template <typename T>
void SinglyLinkedListWithHead<T>::remove_all(T val) {
    if (empty())
        return;

    auto pNode = head->next;
    auto preNode = head;
    while (pNode) {
        if (pNode->data == val) {
            preNode = pNode->next;
            delete pNode;
            pNode = nullptr;
            size--;
        }
        preNode = preNode->next;
        pNode = pNode->next;
    }
}

template <typename T>
void SinglyLinkedListWithHead<T>::erase(int index) {
    if (empty())
        return;

    assert(index < length());
    assert(index > 0);

    int position = 1;
    auto pNode = head->next;
    auto preNode = head;

    while (pNode && position != index) {
        pNode = pNode->next;
        preNode = preNode->next;
        position++;
    }
    preNode->next = pNode->next;
    delete (pNode);
    pNode = nullptr;
    size--;
}

template <typename T>
void SinglyLinkedListWithHead<T>::insert(T data, int index) {
    if (empty())
        return;

    assert(index < length());
    assert(index > 0);

    int position = 1;
    auto pNode = head->next;
    auto preNode = head;
    auto newNode = new Node<T>(data);

    while (pNode && position != index) {
        pNode = pNode->next;
        preNode = preNode->next;
        position++;
    }

    newNode->next = preNode->next;
    preNode->next = newNode;
    size++;
}

template <typename T>
SinglyLinkedListWithHead<T>::SinglyLinkedListWithHead(const SinglyLinkedListWithHead<T> &SL) {
    if (this == &SL)
        return;

    size = SL.size;
    auto pNode = SL.getHead();

    while (pNode) {
        push_back(pNode->data);
        pNode = pNode->next;
    }
}

template <typename T>
SinglyLinkedListWithHead<T>& SinglyLinkedListWithHead<T>::operator=(const SinglyLinkedListWithHead<T> &SL) {
    if (this == &SL)
        return *this;

    clear();
    size = SL.size;
    auto pNode = SL.getHead();

    while (pNode) {
        push_back(pNode->data);
        pNode = pNode->next;
    }
    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const SinglyLinkedListWithHead<T>& List) {
    if(List.empty())
        return os;

    auto pNode = List.getHead()->next;
    while (pNode) {
        os << std::setw(5) << std::setiosflags(std::ios::left) << pNode->data;
        pNode = pNode->next;
    }
    os << std::endl;
    return os;
}


#endif //LIST_SINGLY_LINKED_LIST_H
