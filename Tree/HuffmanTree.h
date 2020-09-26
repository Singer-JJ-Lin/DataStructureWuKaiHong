//
// Created by Only Blue on 2020-05-22.
//

#ifndef CLIONCODE_HUFFMANTREE_H
#define CLIONCODE_HUFFMANTREE_H

#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

class HuffmanNode
{
public:
    char key;
    float weight;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode* parent;

    // 构造函数
    explicit HuffmanNode(float w, char value = 0, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr, HuffmanNode* p = nullptr)
    :weight(w), key(value), left(l), right(r), parent(p){}

    //是否为叶子节点
    bool isleaf() const {return !left && !right; }
};


struct compare
{
    bool operator()(const HuffmanNode* h1, const HuffmanNode* h2)
    {
        return h1->weight > h2->weight;
    }
};


class Code
{
public:
    string code;
    char key;

    Code(string& str, char data):code(str), key(data) {}
};


class HuffmanTree
{
private:
    HuffmanNode *root;
    vector<Code*>  codedict;
    vector<HuffmanNode*> leaf_set;

public:
    HuffmanTree():root(nullptr){}
    ~HuffmanTree() {destroy(root); }

    HuffmanNode* getRoot() const {return root; }

    // 创建哈夫曼树
    void CreateTree(char keys[], float weights[], int size);
    // 哈夫曼编码
    void BuildCodeDict();
    // ShowCodeDict
    void ShowCodeDict();
    // 编码
    string encoding(const string& str);
    // 解码
    string decoding(const string& str);
    // 带权路径长度
    int lengthWithWeight() const {return lengthWithWeight(root, 0); }


protected:

    // 销毁哈夫曼树
    void destroy(HuffmanNode* subTree)
    {
        if(subTree == nullptr)
            return;

        destroy(subTree->left);
        destroy(subTree->right);
        delete subTree;
    }

    // 带权路径长度
    static int lengthWithWeight(HuffmanNode* T, int height) {
	    int valueOfLeftChild = 0;
	    int valueOfRightChild = 0;

	    if(T == nullptr)
	    	return 0;

	    if(T->left->isleaf() && T->right->isleaf())
	    	return T->weight * (1.0) * height;

	    valueOfLeftChild = lengthWithWeight(T->left, height + 1);
	    valueOfRightChild = lengthWithWeight(T->right, height + 1);
	    return valueOfRightChild + valueOfLeftChild;
    }
};

void HuffmanTree::CreateTree(char keys[], float weights[], int size)
{
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> minHeap; // 优先队列创建最小堆
    for (int i = 0; i < size; i++) {
        auto temp = new HuffmanNode(weights[i],keys[i]);
        leaf_set.push_back(temp);
        minHeap.push(temp);
    }

    HuffmanNode* p = nullptr, * l = nullptr, * r = nullptr;
    while (!minHeap.empty()) {
        l = minHeap.top();
        minHeap.pop();
        if (minHeap.empty()) break;
        r= minHeap.top();
        minHeap.pop();

        p = new HuffmanNode(l->weight + r->weight);
        if(l->weight == r->weight){
            p->left = r;
            p->right = l;
        }
        else {
            p->left = l;
            p->right = r;
        }

        l->parent = p;
        r->parent = p;

        minHeap.push(p);
    }
    root = p;
}


void HuffmanTree::BuildCodeDict()
{
    for(auto leaf : leaf_set){
        string value;
        HuffmanNode* temp = leaf;
        while(temp->parent) {
            if (temp->parent->left == temp)
                value = '0' + value;
            else if (temp->parent->right == temp)
                value = '1' + value;
            temp = temp->parent;
        }
        codedict.push_back(new Code(value, leaf->key));
    }
}

// 模仿python的字典 key->value
void HuffmanTree::ShowCodeDict()
{
    cout << "CodeDict" << endl;
    cout << "{";
    for(int i = 0; i < codedict.size(); i++){
        cout << "'" << codedict[i]->key << "' : " << codedict[i]->code;
        if(i != codedict.size()-1)
            cout << ", ";
    }
    cout << '}' << endl;
}


string HuffmanTree::encoding(const string& str)
{
    string res = "";
    for(auto ch : str){
        for (auto j  : codedict) {
            if (ch == j->key)
                res += j->code;
        }
    }
    return res;
}

string HuffmanTree::decoding(const string& str)
{
    string res;
    HuffmanNode *temp = root;
    for(auto ch:str) {
        if(ch == '0')
            temp = temp->left;
        else if(ch == '1')
            temp = temp->right;
        if(temp->isleaf()) {
            res += temp->key;
            temp = root;
        }
    }
    return res;
}

#endif //CLIONCODE_HUFFMANTREE_H
