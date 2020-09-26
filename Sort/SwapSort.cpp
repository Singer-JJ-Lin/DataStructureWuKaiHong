//
// Created by Only Blue on 2020/6/8.
//

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
using namespace std;

#include <sys/time.h>

int comp(const void *p1,const void *p2)
{
    return  *((int*)p2)>*((int*)p1)?1:-1;
}

template <typename T>
bool Compare(T arg1, T arg2) {return arg1 < arg2; }

template <typename T>
void swap(T& arg1, T& arg2) {
    T temp = arg1;
    arg1 = arg2;
    arg2 = temp;
}

template <typename T>
void BubbleSort(T arr[], int size, bool(*cmp)(T, T)) {
	if(arr == nullptr || size < 2)
		return;

    for(int i = 1; i < size; i++) {
        for(int j = 0; j < size - i; j++) {
            if(cmp(arr[j], arr[j+1]))
                swap(arr[j], arr[j+1]);
        }
    }
}

template <typename T>
int getIndex(T arr[], int low, int high, bool(*cmp)(T, T)) {
    int temp = arr[low]; // 基准
    while(low < high) {
        // 当队尾的元素大于等于基准数据时,向前挪动high指针
        while(low < high && arr[high] >= temp) high--;
        // 如果队尾元素小于tmp了,需要将其赋值给low
        arr[low] = arr[high];

        // 当队首元素小于等于tmp时,向前挪动low指针
        while(low < high && arr[low] <= temp) low++;
        // 当队首元素大于tmp时,需要将其赋值给high
        arr[high] = arr[low];
    }
    arr[low] = temp;
    return low;
}

template <typename T>
void QuickSort(T arr[], int low, int high, bool(*cmp)(T, T)) {
	if(arr == nullptr)
		return;

	if (low < high) {
		int index = getIndex(arr, low, high, cmp);
		QuickSort(arr, 0, index - 1, cmp);  // 递归调用
		QuickSort(arr, index + 1, high, cmp); // 递归调用
	}
}


int main() {
    int arr[10] = {75,37,81,19,82,74,50,26,15,6};

//    struct timeval start,finish;
//    gettimeofday(&start,nullptr);
//    double Totaltime = 0.0;
//    for(int i = 0; i < 10000; i++) {
//        std::sort(arr, arr+10);
//        int arr[10] = {12,7,543,3,111,4,5,87,99,0};
//    }
//    gettimeofday(&finish,nullptr);
//    Totaltime = finish.tv_sec - start.tv_sec + (finish.tv_usec - start.tv_usec) / 1000000.0;
//    std::cout << "sort: " << Totaltime << std::endl;
//
//    gettimeofday(&start,nullptr);
//    for(int i = 0; i < 10000; i++) {
//        QuickSort(arr, 0,9, Compare);
//        int arr[10] = {12,7,543,3,111,4,5,87,99,0};
//    }
//    gettimeofday(&finish,nullptr);
//    Totaltime = finish.tv_sec - start.tv_sec + (finish.tv_usec - start.tv_usec) / 1000000.0;
//    std::cout << "QuickSort: " << Totaltime << std::endl;
//
//    for(int i : arr) {
//        std::cout << std::setw(4) << std::setiosflags(std::ios::left) << i << " ";
//    }

//	QuickSort(arr, 0, 9, Compare);
//	for(int i : arr)
//		cout << setw(5) << setiosflags(ios::left) << i;
//	cout << endl;
	cout << 5 / -2 << endl;
    return 0;
}