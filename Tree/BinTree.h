//
// Created by Only Blue on 2020-05-26.
//

#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

/*=================定义二叉树节点================*/
template <typename T>
class BTNode
{
public:
    BTNode() :leftChild(nullptr), rightChild(nullptr) {}
    explicit BTNode(T x, BTNode<T>* left = nullptr, BTNode<T>* right = nullptr) :data(x), leftChild(left), rightChild(right) {}    //带默认值的有参构造参数
    T data;
    BTNode<T>* leftChild;
    BTNode<T>* rightChild;
};

/*=================================定义二叉树================================*/
template <typename T>
class BinaryTree
{
private:
    BTNode<T>* root;
    T RefValue;   // 数据输入停止的标志，需要一个构造函数

public:
//=============二叉树构造与析构==============//

    // 构造函数
    BinaryTree() :root(nullptr) {}
    // 指定结束标志的构造函数
    explicit BinaryTree(T value) :RefValue(value), root(nullptr) {}
    // 析构函数
    ~BinaryTree() { Destroy(root); }

//================二叉树的创建================//

    // 使用广义表创建二叉树，以#字符代表结束
    void CreateBinTree() { CreateBinTree(root); }

    // 前序遍历创建二叉树(前序遍历的应用)，#代表空节点
    void CreateBinTree_PreOrder() { CreateBinTree_PreOrder(root); }

    // 使用先序遍历和中序遍历创建二叉树
    void CreateBinTree_Pre_In(const vector<T> pre, const vector<T> in) { CreateBinTree_Pre_In(root, pre, in); }

    // 使用后序遍历和中序遍历创建二叉树
    void CreateBinTree_Post_In(const vector<T> post, const vector<T> in) { CreateBinTree_Post_In(root, post, in); }

    // 以二叉树的中序遍历和层次遍历创建二叉树
    void CreateBinTree_Level_In(const vector<T> level, const vector<T> in) { CreateBinTree_Level_In(root, level, in); }

//================二叉树的遍历================//

    // 先序遍历(递归)
    void PreOrder() { PreOrder(root); }

    // 中序遍历(递归)
    void InOrder() { InOrder(root); }

    // 后序遍历(递归)
    void PostOrder() { PostOrder(root); }

    // 先序遍历(非递归)
    void PreOrder_NoRecurve() { PreOrder_NoRecurve(root); }

    // 中序遍历(非递归)
    void InOrder_NoRecurve() { InOrder_NoRecurve(root); }

    // 后序遍历(非递归)
    void PostOrder_NoRecurve() { PostOrder_NoRecurve(root); }

    // 层次遍历
    void LevelOrder() { LevelOrder(root); }

//=====================获取节点==================//

    // 获取二叉树根节点
    BTNode<T>* getRoot() const { return root; }

    // 获取current节点的父节点
    BTNode<T>* Parent(BTNode<T>* current)
    {
        return (root == nullptr || root == current) ? nullptr : Parent(root, current);
    }

    // 获取current节点的左节点
    BTNode<T>* leftChild(BTNode<T>* current)
    {
        return (current != nullptr) ? current->leftChild : nullptr;
    }

    // 获取current节点的右节点
    BTNode<T>* rightChild(BTNode<T>* current)
    {
        return (current != nullptr) ? current->rightChild : nullptr;
    }

//===================成员函数====================//

    // 销毁函数
    void Destroy() { Destroy(root); }

    // 拷贝二叉树，用于前序遍历
    BinaryTree(const BinaryTree<T>& s) { root = Copy(s.getRoot()); }

    // 判断两颗二叉树是否相等
    bool operator==(BinaryTree<T> &s) { return equal(this->getRoot(), s.getRoot()); }

    // 二叉树节点个数，用于后遍历
    int Size() { return Size(root); }

    // 计算二叉树的高度
    int Height() { return Height(root); }

    //判断二叉树是否为空
    bool Empty() { return root == nullptr; }

    // 以广义表形式输出二叉树，用于前序遍历
    void PrintBinTree() { PrintBinTree(root); }

protected:

//=======================二叉树的创建=======================//

    // 使用广义表创建二叉树函数，字符为data,#代表结束
    //广义表A ( B ( D , E ( G , ) ) , C (, F ) ) #
    /*               A
                    / \
                   B   C
                  / \   \
                 D   E   F
                    /
                   G       Author:不会打代码的Jason*/

    void CreateBinTree(BTNode<T>*& BT) {
        /*1.若是节点的值(这里为字母)，则建立新节点，并连接到父节点上
        2.'('表示子表开始，')'表示子表结束,','表示左子树处理完毕，处理右子树*/
        stack<BTNode<T> *> s;
        BT = nullptr;
        BTNode<T> *p = nullptr, *t = nullptr;
        int flag = 0;  // 左子树和右子树的标志 0-左子树 1-右子树
        T ch;
        cout << "请输入广义表来创建二叉树: " << endl;
        cin >> ch;
        while (ch != RefValue) {
            if (ch == ' ') {
                continue;
            }
            switch (ch) {
                case '(':
                    s.push(p);
                    flag = 0;
                    break;

                case ')':
                    s.pop();
                    break;

                case ',':
                    flag = 1;
                    break;

                default:
                    p = new BTNode<T>(ch);
                    if (BT == nullptr) {
                        BT = p;
                    } else if (flag == 0) {
                        t = s.top();
                        t->leftChild = p;
                    } else if (flag == 1) {
                        t = s.top();
                        t->rightChild = p;
                    }
            }
            cin >> ch;
        }
    }

    // 二叉树前序遍历创建二叉树，'#'表示空节点
    //前序序列 ABC##DE#G##F###
    /*                    A
                         / \
                        B   #
                       / \___
                      C      D
                     / \    / \___
                    #   #  E      F
                          / \    / \
                          #   G  #   #
                            / \
                           #   #     */
    void CreateBinTree_PreOrder(BTNode<T>*& subTree) {
        T temp;
        cin >> temp;
        if (temp != RefValue) {
            subTree = new BTNode<T>(temp);
            CreateBinTree_PreOrder(subTree->leftChild); // 递归构建左子树
            CreateBinTree_PreOrder(subTree->rightChild);// 递归构建右子树
        } else {
            subTree = nullptr;    // 左子树或右子树为空
        }
    }

    // 以二叉树的前序遍历和中序遍历创建二叉树
    void CreateBinTree_Pre_In(BTNode<T>*&cur,vector<T> pre, vector<T> in) {
        if (pre.size() <= 0) {
            cur = nullptr;
            return;
        }

        int pos = 0;
        while (pre[0] != in[pos]) {
            pos++;
        }

        vector<T> pre_left(pre.begin() + 1, pre.begin() + pos + 1);
        vector<T> in_left(in.begin(), in.begin() + pos + 1);
        vector<T> pre_right(pre.begin() + pos + 1, pre.end());
        vector<T> in_right(in.begin() + pos + 1, in.end());
        cur = new BTNode<T>(in[pos]);
        CreateBinTree_Pre_In(cur->leftChild, pre_left, in_left);
        CreateBinTree_Pre_In(cur->rightChild, pre_right, in_right);
    }

    // 以二叉树的中序遍历和后序遍历创建二叉树
    void CreateBinTree_Post_In(BTNode<T>*& cur, vector<T> post, vector<T> in) {
        if (post.size() <= 0) {
            cur = nullptr;
            return;
        }

        int pos = 0;
        while (in[pos] != *(post.end() - 1)) {
            pos++;
        }

        cur = new BTNode<T>(*(post.end() - 1));
        vector<T> post_left(post.begin(), post.begin() + pos);
        vector<T> in_left(in.begin(), in.begin() + pos);
        vector<T> post_right(post.begin() + pos, post.end() - 1);
        vector<T> in_right(in.begin() + pos + 1, in.end());
        CreateBinTree_Post_In(cur->leftChild, post_left, in_left);
        CreateBinTree_Post_In(cur->rightChild, post_right, in_right);
    }

    // 以二叉树的中序遍历和层次遍历创建二叉树
    void CreateBinTree_Level_In(BTNode<T>*& cur, vector<T> level, vector<T> in) {
        if (in.size() <= 0) {
            cur = nullptr;
            return;
        }

        int pos = 0;
        while (level[0] != in[pos]) {
            pos++;
        }

        cur = new BTNode<T>(level[0]);
        typename vector<T>::iterator it;

        vector<T> in_left(in.begin(), in.begin() + pos);
        vector<T> level_left;
        for (int i = 0; i < level.size(); i++)
            if ((it = find(in_left.begin(), in_left.end(), level[i])) != in_left.end())
                level_left.push_back(level[i]);

        vector<T> in_right(in.begin() + pos + 1, in.end());
        vector<T> level_right;
        for (int i = 0; i < level.size(); i++)
            if ((it = find(in_right.begin(), in_right.end(), level[i])) != in_right.end())
                level_right.push_back(level[i]);

        CreateBinTree_Level_In(cur->leftChild, level_left, in_left);
        CreateBinTree_Level_In(cur->rightChild, level_right, in_right);
    }

//===================输出遍历二叉树======================//

    // 以广义表的形式输出二叉树
    void PrintBinTree(BTNode<T>* BT) {
        if (BT != nullptr) {
            cout << BT->data << ' ';
            if (BT->leftChild || BT->rightChild) {
                cout << "( ";
                if (BT->leftChild) {
                    PrintBinTree(BT->leftChild);
                }
                cout << ",";
                if (BT->rightChild) {
                    PrintBinTree(BT->rightChild);
                }
                cout << ")";
            }
        }
    }

    // 二叉树的前序遍历(递归):根->左->右
    void PreOrder(BTNode<T>*& subTree) {
        if (subTree != nullptr) {
            cout << subTree->data << " ";
            PreOrder(subTree->leftChild);
            PreOrder(subTree->rightChild);
        }
    }

    // 二叉树的中序遍历(递归):左->根->右
    void InOrder(BTNode<T>*& subTree) {
        if (subTree != nullptr) {
            InOrder(subTree->leftChild);
            cout << subTree->data << " ";
            InOrder(subTree->rightChild);
        }
    }

    // 二叉树的后序遍历(递归):左->右->根
    void PostOrder(BTNode<T>*& subTree) {
        if (subTree != nullptr) {
            PostOrder(subTree->leftChild);
            PostOrder(subTree->rightChild);
            cout << subTree->data << " ";
        }
    }

    // 二叉树先序遍历(非递归) Version 1
    // 每次访问一个节点，先用站记录节点的右子树(如果有)，再沿左子树遍历
    // 左子树回退时从栈顶取右子树节点，继续遍历
    void PreOrder_NoRecurve(BTNode<T>* subTree) {
        stack<BTNode<T> *> s;
        s.push(nullptr); // 先push一个nullptr，最后的时候为nullptr退出循环

        while (subTree != nullptr) {
            cout << subTree->data << " ";
            if (subTree->rightChild) {
                s.push(subTree->rightChild);
            }

            if (subTree->leftChild) {
                subTree = subTree->leftChild;
            } else {
                subTree = s.top();
                s.pop();
            }
        }
    }

    // 二叉树前序遍历(非递归) Version 2
    /*void PreOrder_NoRecurve(BTNode<T>* subTree) {
        stack<BTNode<T>*> s;
        BTNode<T>* t = nullptr;
        s.push(subTree);

        while (!s.empty()) {
            t = s.top();
            s.pop();
            cout << t->data << ' ';

            if (t->rightChild) {
                s.push(t->rightChild);
            }

            if (t->leftChild) {
                s.push(t->leftChild);
            }
        }
    }*/

    // 二叉树的中序遍历(非递归)
    void InOrder_NoRecurve(BTNode<T>* subTree) {
        stack<BTNode<T> *> s;

        do {
            while (subTree) {
                s.push(subTree);
                subTree = subTree->leftChild;
            }

            if (!s.empty()) {
                subTree = s.top();
                s.pop();
                cout << subTree->data << " ";
                subTree = subTree->rightChild;
            }
        } while (subTree || !s.empty());
    }

    // 二叉树的后序遍历(非递归)
    void PostOrder_NoRecurve(BTNode<T>* subTree) {
        stack<BTNode<T> *> Stack;
        stack<BTNode<T> *> Output;

        BTNode<T> *temp = subTree;
        while (temp != nullptr || !Stack.empty()) {
            if (temp != nullptr) {
                Stack.push(temp);
                Output.push(temp);
                temp = temp->rightChild;
            } else {
                temp = Stack.top();
                Stack.pop();
                temp = temp->leftChild;
            }
        }

        while (Output.size() > 0) {
            temp = Output.top();
            Output.pop();
            cout << temp->data << " ";
        }
    }

    //二叉树层次遍历
    void LevelOrder(BTNode<T>* subTree) {
        queue<BTNode<T> *> q;  // 队列真tm是个好东西
        q.push(subTree);
        BTNode<T> *t;

        while (!q.empty()) {
            t = q.front();
            q.pop();
            cout << t->data << ' ';

            if (t->leftChild) {
                q.push(t->leftChild);
            }

            if (t->rightChild) {
                q.push(t->rightChild);
            }
        }
    }


//====================其他函数=====================//

    // 销毁函数
    void Destroy(BTNode<T>*& subTree) {
        if (subTree != nullptr) {
            Destroy(subTree->leftChild);
            Destroy(subTree->rightChild);

            delete subTree;
            subTree = nullptr;
        }
    }

    // 判断两颗二叉树是否相等
    bool equal(BTNode<T>* a, BTNode<T>* b) {
        if (a == nullptr && b == nullptr) return true;
        return a != nullptr && b != nullptr && a->data == b->data && equal(a->leftChild, b->leftChild) &&
               equal(a->rightChild, b->rightChild);
    }

    // 复制二叉树，返回orginalNode的副本
    BTNode<T>* Copy(BTNode<T> *orginalNode) { //递归

        if (orginalNode == nullptr) {
            return nullptr;
        }

        auto temp = new BTNode<T>;    // 创建根节点
        temp->data = orginalNode->data;
        temp->leftChild = Copy(orginalNode->leftChild);
        temp->rightChild = Copy(orginalNode->rightChild);
        return temp;
    }

    // 计算以subTree为根的节点个数
    int Size(BTNode<T>* subTree) const
    {
        if (subTree == nullptr)                //递归出口，空树返回0
            return 0;

        return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
    }

    // 计算以subTree为根节点的二叉树的高度
    int Height(BTNode<T>* subTree) {
        if (subTree == nullptr) {      // 递归出口，空树返回0
            return 0;
        }

        int left = Height(subTree->leftChild);
        int right = Height(subTree->rightChild);
        return left < right ? right + 1 : left + 1;
    }

    // 求二叉树某节点的父节点，从某个节点开始寻找，找到返回父节点，找不到返回nullptr
    BTNode<T>* Parent(BTNode<T>*  subTree, BTNode<T>* current) {
        if (subTree == nullptr) {
            return nullptr;
        }

        if (subTree->leftChild == current || subTree->rightChild == current) {
            return subTree;
        }

        BTNode<T> *temp = nullptr;
        if ((temp = Parent(subTree->leftChild)) != nullptr) {    // 左子树搜索
            return temp;
        }

        if ((temp = Parent(subTree->rightChild)) != nullptr) {   // 右子树搜索
            return temp;
        }
    }
};
#endif //BINTREE_BINTREE_H
