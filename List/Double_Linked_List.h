//
// Created by Only Blue on 2020/6/21.
//

#ifndef LIST_DOUBLE_LINKED_LIST_H
#define LIST_DOUBLE_LINKED_LIST_H

template <typename T>
class ListNode {
public:
	T data;
	ListNode<T> *prior;
	ListNode<T> *next;

	explicit ListNode(T data = 0) : data(data), prior(nullptr), next(nullptr) {}
};

template <typename T>
class DoubleLinkedList {
private:
	ListNode<T> *head;
	int size;
public:
	// Constructor
	DoubleLinkedList() : head(new ListNode<T>), size(0) { head->next = head, head->prior = head; }

	// length of list
	int length() const { return size; }

	// isEmpty
	bool isEmpty() const {return size == 0; }

	// insert new node into list
	bool insert(T data, int index);

	// remove node in list by index
	bool remove(int index);

	// append one element into list
	void append(T data);

};

template<typename T>
bool DoubleLinkedList<T>::insert(T data, int index) {
	if (index < 0 || index > size)
		return false;

	ListNode<T> pNode = head->next;
	int pos = 1;

	while(pNode && pos < index) {
		pos++;
		pNode = pNode.next;
	}

	auto newNode = new ListNode<T>(data);
	newNode->next = pNode->next;
	newNode->prior = pNode;
	pNode->next->prior = newNode;
	pNode->next = newNode;
	size++;
	return true;
}

template<typename T>
bool DoubleLinkedList<T>::remove(int index) {
	if(isEmpty())
		return false;

	if(index < 0 || index > size)
		return false;

	int pos = 1;
	ListNode<T> *pNode = head->next;
	while(pNode && pos < index - 1) {
		pos++;
		pNode = pNode->next;
	}

	auto temp = pNode->next;
	pNode->next = pNode->next->next;
	pNode->next->prior = pNode;
	delete temp;
	size--;
	return true;
}

template<typename T>
void DoubleLinkedList<T>::append(T data) {
	auto newNode = new ListNode<T>(data);
	auto pNode = head->next;
	while(pNode->next)
		pNode= pNode->next;

	pNode->next= newNode;
	newNode->prior = pNode;
	size++;
}

#endif //LIST_DOUBLE_LINKED_LIST_H
