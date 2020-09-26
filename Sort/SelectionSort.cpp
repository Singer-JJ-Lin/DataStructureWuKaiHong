//
// Created by Only Blue on 2020/6/2.
//

#include <iostream>
#include <algorithm>
#include <iomanip>

template <typename T>
void swap(T& arg1, T& arg2) {
    T temp = arg1;
    arg1 = arg2;
    arg2 = temp;
}

template <typename T>
T myMax(T arg1, T arg2, T arg3) {
    T max = arg1;
    if (arg1 < arg2) max = arg2;
    if (max  < arg3) max = arg3;
    return max;
}

template <typename T>
void SelectionSort(T arr[], int size, bool(*cmp)(T, T)) {
    for(int i = 0; i < size -1; i++) {
        int index = i;
        for(int j = i; j < size; j++) {
            if(cmp(arr[index], arr[j]))
                index = j;
        }
        swap(arr[i], arr[index]);
    }
}

bool cmp(int arg1, int arg2) {
    return arg1 < arg2;
}


template <typename T>
struct Compare {
	bool operator()(T arg1, T arg2) const
	{
		return (arg1 < arg2);
	}
};


//=========================HeapSort==========================//
template <typename T, class Compare>
class Heap {
private:
    T *arr;
    int size;
    Compare cmp;

public:
    Heap(const T *array, int size_array);

    void HeapAdjust(int index, int length);

    void HeapSort();

    void print();

};

template <typename T, class Compare>
void Heap<T, Compare>::print() {
	for (int i = 0; i < size; i++) {
		std::cout << std::setw(4) << std::setiosflags(std::ios::left) << arr[i];
	}
	std::cout << std::endl;
}

template <typename T, class Compare>
Heap<T, Compare>::Heap(const T *array, int size_array) {
    arr = new T[size_array];
    size = size_array;
    for (int i = 0; i < size; i++) {
        arr[i] = array[i];
    }
}

template<typename T, class Compare>
void Heap<T, Compare>::HeapAdjust(int index, int length) {
    int temp = arr[index];//先取出当前元素i
    for (int k = index * 2 + 1; k < length; k = k * 2 + 1) {//从i结点的左子结点开始，也就是2i+1处开始
        if (k + 1 < length && cmp(arr[k], arr[k + 1])) {//如果左子结点小于右子结点，k指向右子结点
            k++;
        }
        if (cmp(temp, arr[k])) {//如果子节点大于父节点，将子节点值赋给父节点（不用进行交换）
            arr[index] = arr[k];
            index = k;
        } else {
            break;
        }
    }
    arr[index] = temp;//将temp值放到最终的位置
}

template <typename T, class Compare>
void Heap<T, Compare>::HeapSort() {
	for (int i = size / 2 - 1; i >= 0; i--) { // 调整为最大堆
		HeapAdjust(i, size);
	}

	for (int i = size - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		HeapAdjust(0, i);
	}
}


int main() {
	int arr[11] = {12, 7, 543, 333, 111, 4, 5, 87, 99, 0, 0x44};
	Heap<int, Compare<int>> h(arr, sizeof(arr) / sizeof(arr[9]));
	h.HeapSort();
	h.print();

	return 0;
}