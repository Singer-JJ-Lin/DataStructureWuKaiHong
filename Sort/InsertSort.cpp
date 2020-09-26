//
// Created by Only Blue on 2020/6/1.
//
#include <iostream>
#include <iomanip>

template <typename T>
void swap(T& arg1, T& arg2) {
	T temp = arg1;
	arg1 = arg2;
	arg2 = temp;
}

// 直接插入排序
template <typename T>
void InsertSort(T arr[], int size, bool(*cmp)(T,T)) {
    T temp;
    for (int i = 0; i < size; i++) {
        temp = arr[i+1];
        int j = i;
        while(j >= 0 && cmp(temp, arr[j])) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}


/*在希尔排序的理解时，我们倾向于对于每一个分组，逐组进行处理，
 但在代码实现中，我们可以不用这么按部就班地处理完一组再调转回来处理下一组*/

template <typename T>
void ShellSort1(T arr[], int size, bool(*cmp)(T, T)) {
	for (int gap = size / 2; gap >= 1; gap /= 2) {
		for (int i = gap; i < size; i++) {
			int j = i;
			while (cmp(arr[j - gap], arr[j]) && j - gap >= 0) {
				swap(arr[j - gap], arr[j]);
				j -= gap;
			}
		}
	}
}

template <typename T>
void ShellSort2(T arr[], int size, bool(*cmp)(T, T)) {
    int h = 1;
    while(h < size / 3) {
        h = 3 * h + 1;        // 优化1
    }

    int exchange = 0;
    for(int i = size - 1; i > 0; i--)
        if(cmp(arr[i-1]),arr[i]) {
            swap(arr[i], arr[i - 1]);
            exchange++;
        }

    // 交换次数为0说明数组有序，无需排序
    if(!exchange) return;

    while(h >= 1) {
        // 将数组变成h有序
        for(int i = h; i < size; i++) {
            int temp = arr[i];
            int j = i;
            while(j >= h && cmp(arr[i-h], temp)) {
                arr[j] = arr[j-h];
                j -= h;
            }
            arr[j] = temp;
        }
        h = h / 3;
    }
}

bool cmp(int arg1, int arg2) {
    return arg1 > arg2;
}

int main() {
    int arr[10] = {12,7,543,3,111,4,5,87,99,0};
    InsertSort(arr, sizeof(arr)/sizeof(int), cmp);
    for(int i : arr) {
        std::cout << std::setw(4) << std::setiosflags(std::ios::left) << i << " ";
    }
    return 0;
}
