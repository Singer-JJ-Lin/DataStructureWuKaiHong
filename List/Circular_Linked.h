//
// Created by Only Blue on 2020/6/20.
//

#ifndef LIST_CIRCULAR_LINKED_LIST_H
#define LIST_CIRCULAR_LINKED_LIST_H

#include <iostream>

template <typename T>
class ListNode {
public:
	T data;
	ListNode<T>* next;
	explicit ListNode(T data = 0): data(data), next(nullptr) {}
};


template <typename  T>
class CircularLinkedList {
private:
	ListNode<T> *front;
	ListNode<T> *rear;
	int size;
public:
	// constructor
	CircularLinkedList() : front(nullptr), rear(nullptr), size(0) {}

	// is empty or not
	bool isEmpty() const { return rear == nullptr; }

	// return length of list
	int length() const { return size; }

	// append a new node into list
	void append(ListNode<T>* newNode);

	// append a new node into list
	bool insert(ListNode<T>* newNode, int index);

	// remove an element in list
	bool remove(int index);
};

template<typename T>
void CircularLinkedList<T>::append(ListNode<T>* newNode) {
	if(isEmpty()) {
		front = newNode;
		rear = newNode;
		size++;
	}

	else {
		newNode->next = front;
		rear->next = newNode;
		rear = newNode;
		size++;
	}
}

template<typename T>
bool CircularLinkedList<T>::insert(ListNode<T> *newNode, int index) {
	if(index < 0 || index > size)
		return false;

	if(isEmpty()) {
		append(newNode);
		return true;
	}

	if(index == 1 || !isEmpty()) {
		rear->next = newNode;
		newNode->next = front;
		rear = newNode;
		size++;
		return true;
	}

	else if(index == size) {
		append(newNode);
		return true;
	}

	else {
		int pos = 1;
		ListNode<T> *pPre = nullptr;
		ListNode<T> *pNode = front;

		while(pNode != rear && pos < index) {
			pPre = pNode;
			pNode = pNode->next;
			pos++;
		}

		pPre->next = newNode;
		newNode->next = pNode;
		size++;
		return true;
	}
}

template<typename T>
bool CircularLinkedList<T>::remove(int index) {
	if(isEmpty())
		return false;

	if(index < 0 || index > size)
		return false;

	if(index == 1) {
		rear->next = front->next;
		delete front;
		front = rear->next;
		size--;
		return true;
	}

	else if(index == size) {
		ListNode<T> *pNode = front;
		while(pNode->next != rear) {
			pNode = pNode->next;
		}

		pNode->next = front;
		delete rear;
		rear = pNode;
		size--;
		return true;
	}

	else {
		ListNode<T> *pPre = nullptr;
		ListNode<T> *pNode = front;
		int pos = 1;

		while(pos < index && front != rear) {
			pos++;
			pPre = pNode;
			pNode = pNode->next;
		}

		pPre->next = pNode->next;
		delete pNode;
		size--;
		return true;
	}
}

#endif //LIST_CIRCULAR_LINKED_LIST_H
