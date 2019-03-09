//
// Created by max on 18.02.19.
//

#ifndef LAB1_MYLIST_H
#define LAB1_MYLIST_H

#include <iostream>
#include <exception>
#include <string>

using namespace std;

template <class T> class MyList;

template <class T> class ComplexElement{
public:
    ~ComplexElement();
protected:
    T value;
    ComplexElement* next;
    friend class MyList<T>;
};

template<class T> ComplexElement<T>::~ComplexElement() {
    next = nullptr;
}

template <class T> class MyList{
public:
    MyList();
    ~MyList();
    T* ToArr();
    void PushFront(T elem);
    void PushBack(T elem);
    void Show();
    void PopBack();
    void PopFront();
    void Insert(T elem, int position);
    T At(int position);
    void Remove(int position);
    int GetSize();
    void Clear();
    void Set(T newValue, int position);
    bool isEmpty(){ return (size == 0); }
    template <typename T1> friend ostream& operator<< (ostream &out, MyList<T1> list);
private:
    ComplexElement<T>* cursor;
    int size;
    ComplexElement<T>* head = nullptr;
};

template<class T> MyList<T>::MyList() {
    cursor = new ComplexElement<T>();
    size = 0;
    head = nullptr;
}

template<class T> MyList<T>::~MyList() {
    Clear();
}

template<class T> void MyList<T>::PushFront(T elem) {
    auto * newElem = new ComplexElement<T>();
    newElem->value = elem;
    if(head == nullptr){
        head = newElem;
        newElem->next= nullptr;
    }else{
        newElem->next = head;
        head = newElem;
    }
    size++;///Increment size value
}

template<class T> void MyList<T>::PushBack(T elem) {
    auto * newElem = new ComplexElement<T>();
    newElem->value = elem;
    newElem->next = nullptr;

    if(head == nullptr){
        head = newElem;
    }else{
        cursor = head;
        while(cursor->next != nullptr){
            cursor = cursor->next;
        }
        cursor->next = newElem;
    }
    size++; ///Increment size value
}

template<class T> void MyList<T>::Show() {
    cursor = head;

    if (cursor != nullptr){
        cout << "{ ";
        while (cursor != nullptr){
            cout << " " << cursor->value << (cursor->next == nullptr ? " ":",");
            cursor = cursor->next;
        }
        cout << "}" << endl;
    }else{
        cout << "Empty list" << endl;
    }
}

template<class T> void MyList<T>::PopBack() {
    cursor = head;

    if(cursor != nullptr){
        if(cursor->next != nullptr){
            while(cursor->next->next != nullptr){
                cursor = cursor->next;
            }

            delete cursor->next;
            cursor->next = nullptr;
        }else if(cursor->next == nullptr){ //List has one element
            head = nullptr;
            delete cursor;
            cursor = nullptr;
        }
        size--; ///Decrement size value
    }else{
        throw length_error("List is already empty");
    }
}

template<class T> void MyList<T>::PopFront() {
    cursor = head;

    if(cursor != nullptr){
        if(cursor->next != nullptr){
            head = head->next;
            delete cursor;
            cursor = nullptr;
        }else{ //List has one element
            head = nullptr;
            delete cursor;
            cursor = nullptr;
        }
        size--; ///Decrement size value
    }else{
        throw length_error("List is already empty");
    }
}

template<class T> void MyList<T>::Insert(T elem, int position) {
    if(position < 0 || position > size) throw invalid_argument("position must be >= 0");

    cursor = head;
    auto * newElem = new ComplexElement<T>();
    newElem->value = elem;
    newElem->next = nullptr;
    int countPosition = 0;

    if(position == 0){
        newElem->next = head;
        head = newElem;
    }else{
        while(countPosition+1 != position && cursor->next != nullptr){ //I'm already check situation when position > size, so let it down
            countPosition++;
            cursor = cursor->next;
        }

        newElem->next = cursor->next;
        cursor->next = newElem;
    }
    size++; ///Increment size value

}

template<class T> T MyList<T>::At(int position) {
    if(position < 0 || position >= size) throw invalid_argument("position must be >= 0 and < size");

    if(head != nullptr){
        cursor = head;

        int countPosition = 0;
        while(cursor != nullptr){
            if(countPosition == position) return cursor->value;
            cursor = cursor->next;
            countPosition++;
        }
    }else{
        throw length_error("List in empty");
    }
}

template<class T> void MyList<T>::Remove(int position) {
    if(position < 0 || position >= size){
        throw invalid_argument("position must be >= 0 and < size");
    }else if(position == 0){
        PopFront();
    }else{
        cursor = head;
        int cursorPosition = 0;

        while(cursorPosition + 1 != position && cursor != nullptr){
            cursor = cursor->next;
            cursorPosition++;
        }

        if(cursor->next == nullptr){
            PopBack();
        }else{
            ComplexElement<T>* varForDeleteElement = cursor->next;
            cursor->next = cursor->next->next;
            delete varForDeleteElement;
            size--; ///Size decrement
        }
    }
}

template<class T> int MyList<T>::GetSize() {
    return size;
}

template<class T> void MyList<T>::Clear() {
    while (head != nullptr){
        cursor = head->next;
        delete head;
        head = cursor;
    }
    size = 0;
}

template<class T> void MyList<T>::Set(T newValue, int position) {
    if(position < 0 || position >= size) throw invalid_argument("position must be >= 0 and < size");
    if(head == nullptr) throw length_error("List is empty");
    cursor = head;
    int cursorPosition = -1;

    do{
        cursorPosition++;
        if(cursorPosition == position) cursor->value = newValue;
        cursor = cursor->next;
    }while(cursorPosition != position && cursor != nullptr);
}

template<class T> ostream &operator<<(ostream &out, MyList<T> list) {
    list.Show();
    return out;
}

template<class T> T *MyList<T>::ToArr() {
    if(size == 0) return nullptr;
    T *output = new T[size];
    int i = 0;
    cursor = head;

    while (cursor != nullptr){
        output[i] = cursor->value;
        i++;
        cursor = cursor->next;
    }

    return output;
}

#endif //LAB1_MYLIST_H
