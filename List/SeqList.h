//
// Created by Only Blue on 2020/6/20.
//

#ifndef LIST_SEQLIST_H
#define LIST_SEQLIST_H

#include <iostream>
using namespace std;

const int MAX_SIZE = 20;
template <typename T>
class SeqList {
private:
	T arr[MAX_SIZE];
	int size;

public:
	// Constructor
	SeqList():size(0) {}
	// return the amount of element in SeqList
	int getSize() const {return size; }
	// insert one element into SeqList, return bool type.
	bool insert(T data, int index);
	// remove one element in SeqList, return bool type.
	bool remove(int index);
	// return elemetn on index
	T getElement(int index);
};

template<typename T>
bool SeqList<T>::insert(T data, int index) {
	if(size >= MAX_SIZE) return false;
	if(index < 0 || index > size) return false;
	else {
		for(int i = size; i > index; i--) {arr[i] = arr[i-1]; }
		arr[index] = data;
		size++;
		return true;
	}
}

template<typename T>
bool SeqList<T>::remove(int index) {
	if(size <= 0) return false;
	if(index < 0 || index > size - 1) return false;
	else {
		for(int i = index + 1; i < size; i++) arr[i-1] = arr[i];
		size--;
		return true;
	}
}

template<typename T>
T SeqList<T>::getElement(int index) {
	if(size <= 0) return nullptr;
	else if(index < 0 || index > size - 1) return false;
	else return arr[index];
}

#endif //LIST_SEQLIST_H
