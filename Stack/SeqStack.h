//
// Created by California dintist on 2020-05-26.
//

#ifndef STACK_SEQSTACK_H
#define STACK_SEQSTACK_H

const int STACK_INIT_SIZE = 10;
const int INCREMENT = 5;

template <typename T>
T* my_realloc(T *sour, size_t size) {
    T* dest = new T[size];
    memcpy(dest, sour, size);
    delete[] sour;
    return dest;
}

template <typename T>
class SeqStack {
private:
    T* peak;
    T* base;
    int stacksize;
public:
    explicit SeqStack();
    ~SeqStack() {delete[] base; }
    // 取栈顶元素
    T top() const {return *(peak-1); }
    // 出栈栈顶元素
    bool pop();
    //入栈一个元素
    void push(T data);
    // 大小
    int size() const {return peak-base; }
    // 判断栈空
    bool empty() const  {return base == peak; }

};

template <typename T>
SeqStack<T>::SeqStack()
{
    base = new T[STACK_INIT_SIZE];
    peak = base;
    stacksize = STACK_INIT_SIZE;
}

template <typename T>
void SeqStack<T>::push(const T data)
{
    if(peak - base > stacksize){
        base = my_realloc(base, stacksize + INCREMENT);
        peak = base + stacksize;
        stacksize = stacksize + INCREMENT;
    }
    *peak++ = data;
    stacksize++;
}

template <typename T>
bool SeqStack<T>::pop() {
    if (stacksize == 0) {
        std::cout << "Stack is empty! Pop fail." << std::endl;
        return false;
    }
    peak--;
    stacksize--;
    return true;
}

#endif //STACK_SEQSTACK_H
