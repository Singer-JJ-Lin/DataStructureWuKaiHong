//
// Created by Only Blue on 2020/6/8.
//
// Divide and Conquer

#include <iostream>
#include <iomanip>

template <typename T>
void merge(T arr[], int low, int mid, int high) {
    int left = low;     // 左边部分指针
    int right = mid+1;  // 右边部分指针
    T *swap = new T[high - low + 1];
    int k = 0;        // 操作swap[]的指针
    while (left <= mid && right <= high) {
        if (arr[left] > arr[right]) {
            swap[k++] = arr[right++];
        } else {
            swap[k++] = arr[left++];
        }
    }

    // 查看左边序列是否为空
    while (left <= mid ) {
        swap[k++] = arr[left++];
    }

    // 查看右边序列是否为空
    while (right <= high) {
        swap[k++] = arr[right++];
    }

    k = 0;
    // 移动回原数组
    for(int i = low; i <= high; i++) {
        arr[i] = swap[k++];
    }
    delete[] swap;
}

template <typename T>
void MergeSort(T arr[], int low, int high) {
    if(low < high) {
        int mid = low + ((high - low) >> 1);
        MergeSort(arr, low, mid);
        MergeSort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}

int main() {
    int arr[10] = {12,7,543,88,3,67,71,96,33,6};
    MergeSort(arr, 0, sizeof(arr)/ sizeof(arr[0])-1);
    for(int i : arr) {
        std::cout << std::setw(3) << std::setiosflags(std::ios::left) << i << " ";
    }
    return 0;
}