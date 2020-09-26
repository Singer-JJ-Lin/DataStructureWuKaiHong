//
// Created by Only Blue on 2020/6/8.
//

#include <iostream>
#include <iomanip>

template <typename T>
int maxBit(const T arr[], int n) {
    int d = 1; //保存最大的位数
    int p = 10;
    for (int i = 0; i < n; ++i) {
        while (arr[i] >= p) {
            p *= 10;
            d++;
        }
    }
    return d;
}


template <typename T>
void radixSort(T arr[], int size) {
    int d = maxBit(arr, size);
    int tmp[size];
    int count[10]; //计数器
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //进行d次排序
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for(j = 0; j < size; j++)
        {
            k = (arr[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for(j = size - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (arr[j] / radix) % 10;
            tmp[count[k] - 1] = arr[j];
            count[k]--;
        }
        for(j = 0; j < size; j++) //将临时数组的内容复制到arr中
            arr[j] = tmp[j];
        radix = radix * 10;
    }
}

int main()
{
    int array[10] = {73,22,93,43,55,14,28,65,39,81};
    radixSort(array,10);
    for(int i:array)
        std::cout << std::setw(4) << std::setiosflags(std::ios::left) << i;
    std::cout << std::endl;
    return 0;
}
