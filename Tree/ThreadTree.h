//
// Created by Only Blue on 2020-05-26.
//

#ifndef BINTREE_THREADTREE_H
#define BINTREE_THREADTREE_H
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class ThreadNode
{
public:
    T data;
    ThreadNode<T>* leftchild, * rightchild;
    int ltag, rtag;
    explicit ThreadNode(const T item) :data(item), leftchild(NULL), rightchild(NULL), ltag(0), rtag(0) {}
};

template <typename T>
class ThreadTree
{
private:
    ThreadNode<T>* root;
    T RefValue;

public:
    //===================函数构造与析构=================//

    // 一般构造函数
    ThreadTree() :root(NULL) {}

    // 指定结束标志的构造函数
    explicit ThreadTree(T item) :root(NULL), RefValue(item) {}

    //析构函数
    ~ThreadTree() { Destroy(root); }

    //=====================创建二叉树===================//

    // 使用前序遍历创建二叉树(未线索化)
    void CreateTree() { CreateTree(root); }

    // 对二叉树中序线索化
    void CreateInThread() {
        ThreadNode<T>* pre = NULL;
        if (root) {
            CreateInThread(root, pre);
            pre->rightchild = NULL;
            pre->rtag = 1;
        }
    }

    //=================线索化二叉树遍历=================//

    // 线索化二叉树的中序遍历
    void PreOrder() { PreOrder(root); }

    // 线索化二叉树的中序遍历
    void InOrder() { InOrder(root); }

    // 线索化二叉树的后序遍历
    void PostOrder() { PostOrder(root); }

    void NPreOrder() { NPreOrder(root); }

protected:

    // 使用前序遍历创建二叉树(未线索化)
    void CreateTree(ThreadNode<T>* &subTree) {
        T item;
        cin >> item;
        if (item != RefValue) {
            subTree = new ThreadNode<T>(item);
            CreateTree(subTree->leftchild);
            CreateTree(subTree->rightchild);
        } else {
            subTree = NULL;
        }
    }

    //使用中序遍历线索化二叉树
    void CreateInThread(ThreadNode<T>* current, ThreadNode<T>*& pre) {
        if (current == NULL) {
            return;
        }

        CreateInThread(current->leftchild, pre);
        if (current->leftchild == NULL) {
            current->leftchild = pre;
            current->ltag = 1;
        }

        if (pre && pre->rightchild == NULL) {
            pre->rightchild = current;
            pre->rtag = 1;
        }

        pre = current;
        CreateInThread(current->rightchild, pre);
    }

    // 寻找中序遍历的第一个节点
    ThreadNode<T>* First(ThreadNode<T>* subTree) {
        ThreadNode<T> *temp = subTree;
        while (temp->ltag == 0 && temp->leftchild) {
            temp = temp->leftchild;
        }
        return temp;
    }

    // 寻找中序遍历的最后一个节点
    ThreadNode<T>* Last(ThreadNode<T>* current) {
        ThreadNode<T> *temp = current;
        while (temp->rtag == 0) {
            temp = temp->rightchild;
        }
        return temp;
    }

    // 寻找中序下某节点的后继节点
    ThreadNode<T>* Next(ThreadNode<T>* current) {
        if (current->rtag == 0) {
            return First(current->rightchild);
        } else {
            return current->rightchild;
        }
    }

    // 寻找中序下某节点的前驱节点
    void* Prior(ThreadNode<T>* current) {
        if (current->ltag == 0) {
            return First(current->leftchild);
        } else {
            return current->rightchild;
        }
    }

    // 中序线索二叉树中寻找父节点
    ThreadNode<T>* Parent(ThreadNode<T>* subTree) {
        ThreadNode<T> *p;
        if (subTree == root) {
            return NULL;
        }

        for (p = subTree; p->ltag == 0; p = p->leftchild);

        if (p->leftchild != NULL) {
            for (p = p->leftchild; p && p->leftchild != subTree && p->rightchild != subTree; p = p->rightchild);
        }

        if (p == NULL || p->leftchild == NULL) {
            for (p = subTree; p->rtag == 0; p = p->rightchild);
            if (p->leftchild != NULL) {
                for (p = p->rightchild;
                     p && p->rightchild != subTree && p->leftchild != subTree; p = subTree->leftchild);
            }
        }
        return p;
    }

    // 线索化二叉树的前序遍历
    void PreOrder(ThreadNode<T>* subTree) {
        while (subTree != NULL) {
            cout << subTree->data << " ";
            if (subTree->ltag == 0) {
                subTree = subTree->leftchild;
            } else if (subTree->rtag == 0) {
                subTree = subTree->rightchild;
            } else {
                while (subTree && subTree->rtag == 1) {  // 寻找第一个具有右子树的节点
                    subTree = subTree->rightchild;
                }

                if (subTree) {
                    subTree = subTree->rightchild;
                }
            }
        }
        cout << endl;
    }

    // 线索化二叉树的中序遍历
    void InOrder(ThreadNode<T>* subTree) {
        for (subTree = First(subTree); subTree != NULL; subTree = Next(subTree)) {
            cout << subTree->data << " ";
        }
        cout << endl;
    }

    // 线索化二叉树的后序遍历
    void PostOrder(ThreadNode<T>* subTree) {
        ThreadNode<T> *t = subTree;
        while (t->ltag == 0 || t->rtag == 0) {
            if (t->ltag == 0) {
                t = t->leftchild;
            } else if (t->rtag == 0) {
                t = t->rightchild;
            }
        }

        cout << t->data << " ";
        while ((subTree = Parent(subTree)) != NULL) {
            if (subTree->rightchild == t || (subTree->leftchild == t && subTree->rtag == 1)) {
                t = subTree;
            } else {
                t = subTree->rightchild;
                while (t->ltag == 0 || t->rtag == 0) {
                    if (t->ltag == 0)
                        t = t->leftchild;
                    else if (t->rtag == 0)
                        t = t->rightchild;
                }
            }
        }
        cout << t->data << " ";
    }

    // 二叉树的前序遍历(递归):根->左->右
    void NPreOrder(ThreadNode<T>*& subTree) {
        if (subTree != NULL) {
            cout << subTree->data << " ";
            NPreOrder(subTree->leftchild);
            NPreOrder(subTree->rightchild);
        }
    }

    // 销毁函数
    void Destroy(ThreadNode<T>*& subTree) {
        if (subTree != NULL) {
            if (subTree->ltag == 0)
                Destroy(subTree->leftchild);

            if (subTree->rtag == 0)
                Destroy(subTree->rightchild);

            delete subTree;
            subTree = NULL;
        }
    }

};
#endif //BINTREE_THREADTREE_H
