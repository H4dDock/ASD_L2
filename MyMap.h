//
// Created by max on 08.03.19.
//

#ifndef UNTITLED2_MYMAP_H
#define UNTITLED2_MYMAP_H


#include <iostream>

using namespace std;
template <class TKey, class TValue> class MyMap;


template <class TKeys, class TValue>  class Node{
public:
    Node();
    Node(TKeys key, TValue value, bool color,Node* leftSon, Node* rightSon);
    ~Node();
private:
    TKeys key;
    TValue data;
    bool color; //true - Red, false - Black
    Node * father;
    Node * leftSon = nullptr;
    Node * rightSon = nullptr;
    friend class MyMap<TKeys, TValue>;
};

template<class TKeys, class TValue>
Node<TKeys, TValue>::Node() {
}

template<class TKeys, class TValue>
Node<TKeys, TValue>::Node(TKeys key, TValue data, bool color, Node *leftSon, Node *rightSon) {
    this->key = key;
    this->data = data;
    this->color = color;
    this->leftSon = leftSon;
    this->rightSon = rightSon;
    this->father = nullptr;
}

template<class TKeys, class TValue>
Node<TKeys, TValue>::~Node() {
    father = nullptr;
    leftSon = nullptr;
    rightSon = nullptr;
}

template <class TKey, class TValue> class MyMap {
public:
    void LeftRotate(Node<TKey,TValue> *node);
    void RightRotate(Node<TKey,TValue> *node);
    void Insert(TKey key, TValue value);
    void FixInsert(Node<TKey,TValue> *newNode);
    void Remove(TKey key);
    void FixRemove(Node<TKey,TValue> *newNode);
    TValue Find(TKey key);
    TKey * GetKeys();
    TValue * GetValue();
    void Show(Node<TKey,TValue> *node,int level);
    void clear();
    Node<TKey,TValue>* GetRoot(){ return root;}
    ~MyMap();
    MyMap();
private:
    Node<TKey,TValue> *cursor;
    Node<TKey,TValue> *root;
};

template<class TKey, class TValue>
void MyMap<TKey, TValue>::LeftRotate(Node<TKey,TValue> *node) {

    Node<TKey, TValue> *helpToRotate = node->rightSon;

    node->rightSon = helpToRotate->leftSon;
    if (helpToRotate->leftSon != nullptr) helpToRotate->leftSon->father = node;


    if (helpToRotate != nullptr) helpToRotate->father = node->father;
    if (node->father) {
        if (node == node->father->leftSon)
            node->father->leftSon = helpToRotate;
        else
            node->father->rightSon = helpToRotate;
    } else {
        root = helpToRotate;
    }


    helpToRotate->leftSon = node;
    if (node != nullptr) node->father = helpToRotate;
}

template<class TKey, class TValue>
void MyMap<TKey, TValue>::RightRotate(Node<TKey,TValue> *node) {

    Node<TKey, TValue> *helpToRotate = node->leftSon;

    node->leftSon = helpToRotate->rightSon;
    if (helpToRotate->rightSon != nullptr) helpToRotate->rightSon->father = node;


    if (helpToRotate != nullptr) helpToRotate->father = node->father;
    if (node->father) {
        if (node == node->father->rightSon)
            node->father->rightSon = helpToRotate;
        else
            node->father->leftSon= helpToRotate;
    } else {
        root = helpToRotate;
    }


    helpToRotate->rightSon = node;
    if (node != nullptr) node->father = helpToRotate;
}

template<class TKeys, class TValue>
void MyMap<TKeys, TValue>::Insert(TKeys key, TValue value) {
    Node<TKeys,TValue> * newNode = new Node<TKeys,TValue>(key, value, true, nullptr, nullptr);
    if(root == nullptr){
        root = newNode;
        newNode->father = nullptr;
    }else{
        Node<TKeys,TValue> * helpToFindFather = root;
        cursor = root;
        while(cursor != nullptr){
            helpToFindFather = cursor;
            if(cursor->key < newNode->key){
                cursor = cursor->rightSon;
            }else{
                cursor = cursor->leftSon;
            }
        }
        newNode->father = helpToFindFather;
        if(helpToFindFather->key < newNode->key){
            helpToFindFather->rightSon = newNode;
        }else{
            helpToFindFather->leftSon = newNode;
        }
    }
    FixInsert(newNode);
}

template<class TKey, class TValue>
void MyMap<TKey, TValue>::FixInsert(Node<TKey, TValue> *newNode) {
    while (newNode!= root && newNode->father->color){ // while parent red
        // if parent node is left son
        if (newNode->father->father->leftSon == newNode->father){
            Node<TKey, TValue> *uncle = newNode->father->father->rightSon;
            if (uncle!= nullptr && uncle->color){ //uncle red
                newNode->father->color = false;
                uncle->color = false;
                newNode->father->father->color = true;
                newNode = newNode->father->father;
            } else { //uncle black or don't exist
                if (newNode == newNode->father->rightSon){
                    newNode = newNode->father;

                    LeftRotate(newNode);
                }

                newNode->father->color = false;
                newNode->father->father->color = true;

                RightRotate(newNode->father->father);
            }

        } else {

            Node<TKey, TValue> *uncle = newNode->father->father->leftSon;
            if (uncle!= nullptr && uncle->color) { //uncle red
                newNode->father->color = false;
                uncle->color = false;
                newNode->father->father->color = true;
                newNode = newNode->father->father;
            } else {
                if (newNode == newNode->father->leftSon){
                    newNode = newNode->father;

                    RightRotate(newNode);
                }

                newNode->father->color = false;
                newNode->father->father->color = true;

                LeftRotate(newNode->father->father);

            }

        }
    }

    root->color = false;
}

template<class TKeys, class TValue>
void MyMap<TKeys, TValue>::Remove(TKeys key) {

    cursor = root;
    while(cursor->key != key){ //If there is no key?
        if(cursor->key < key){
            cursor = cursor->rightSon;
        }else{
            cursor = cursor->leftSon;
        }
    }
    if (cursor == nullptr) return;

    Node<TKeys, TValue> *x, *y;


    if (cursor->leftSon == nullptr || cursor->rightSon == nullptr) {
        y = cursor;
    } else {
        y = cursor->rightSon;
        while (y->leftSon != nullptr) y = y->leftSon;
    }

    if (y->leftSon != nullptr)
        x = y->leftSon;
    else
        x = y->rightSon;

    if(x == nullptr || y == nullptr) cout << "HYI" << endl;

    x->father = y->father;
    /*if (y->father)
        if (y == y->father->leftSon)
            y->father->leftSon = x;
        else
            y->father->rightSon = x;
    else
        root = x;

    if (y != cursor) cursor->data = y->data;


    //if (!y->color)
        //FixRemove (x);

    free (y);*/
}

template<class TKey, class TValue>
void MyMap<TKey, TValue>::FixRemove(Node<TKey,TValue> *deletedNode) {
    while (deletedNode != root && !deletedNode->color) {
        if (deletedNode == deletedNode->father->leftSon) {
            Node<TKey, TValue> *brother = deletedNode->father->rightSon;
            if (brother->color) {
                brother->color = false;
                deletedNode->father->color = true;
                LeftRotate (deletedNode->father);
                brother = deletedNode->father->rightSon;
            }
            if (!brother->leftSon->color && !brother->rightSon->color) {
                brother->color = true;
                deletedNode = deletedNode->father;
            } else {
                if (!brother->rightSon->color) {
                    brother->leftSon->color = false;
                    brother->color = true;
                    RightRotate (brother);
                    brother = deletedNode->father->rightSon;
                }
                brother->color = deletedNode->father->color;
                brother->father->color = false;
                brother->father->color = false;
                LeftRotate (deletedNode->father);
                deletedNode = root;
            }
        } else {
            Node<TKey, TValue> *brother = deletedNode->father->leftSon;
            if (brother->color) {
                brother->color = false;
                deletedNode->father->color = true;
                RightRotate (deletedNode->father);
                brother = deletedNode->father->leftSon;
            }
            if (!brother->rightSon->color && !brother->leftSon->color) {
                brother->color = true;
                deletedNode = deletedNode->father;
            } else {
                if (!brother->leftSon->color) {
                    brother->rightSon->color = false;
                    brother->color = true;
                    LeftRotate (brother);
                    brother = deletedNode->father->leftSon;
                }
                brother->color = deletedNode->father->color;
                deletedNode->father->color = false;
                brother->leftSon->color = false;
                RightRotate (deletedNode->father);
                deletedNode = root;
            }
        }
    }
    deletedNode->color = false;
}

template<class TKeys, class TValue>
TValue MyMap<TKeys, TValue>::Find(TKeys key) {
    return nullptr;
}

template<class TKeys, class TValue>
void MyMap<TKeys, TValue>::clear() {

}

template<class TKey, class TValue>
TKey *MyMap<TKey, TValue>::GetKeys() {
    return nullptr;
}

template<class TKey, class TValue>
TValue *MyMap<TKey, TValue>::GetValue() {
    return nullptr;
}

template<class TKey, class TValue>
MyMap<TKey, TValue>::~MyMap() {

}

template<class TKey, class TValue>
void MyMap<TKey, TValue>::Show(Node<TKey , TValue> *node, int level) {
    if (node) {
        Show(node->leftSon,level+1);
        for(int i = 0;i< level;i++) cout<<"     ";
        cout << node->key << "[" << node->color << "]" << endl;
        Show(node->rightSon,level+1);

    }
}

template<class TKey, class TValue>
MyMap<TKey, TValue>::MyMap() {
    cursor = new Node<TKey, TValue>();
    root = nullptr;
}

#endif //UNTITLED2_MYMAP_H
