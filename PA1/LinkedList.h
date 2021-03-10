#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <iostream>

#include "Node.h"
using namespace std;

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const T arr[], int arrSize);
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;

    int getNumberOfNodes() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    void insertAtTheHead(const T &data);
    void insertAtTheTail(const T &data);
    void insertSorted(const T &data);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();

    void print() const;

    T *toArray() const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.




private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    Node<T> *tail;
};

template<class T>
LinkedList<T>::LinkedList() {
    this->head = nullptr;
    this->tail = head;
}

template<class T>
LinkedList<T>::LinkedList(const T arr[], int arrSize) {
    this->head = nullptr;
    this->tail = head;
    for(int i=0; i<arrSize; i++) {
        insertAtTheTail(arr[i]);
    }
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    
    this->head = nullptr;
    this->tail = nullptr;
    
    if(obj.isEmpty()) {
        return;
    }

    Node<T>*current;

    for(current = obj.head; current != nullptr; current = current->next) {
        if(this->isEmpty()) {
            this->head = new Node<T> (current->data,nullptr, nullptr);
            this->tail = head;
        }
        else {
            this->tail->next = new Node<T>(current->data,this->tail,nullptr);
            this->tail = this->tail->next;
        }
    }


}

template<class T>
LinkedList<T>::~LinkedList() {
    
    if(isEmpty()) {
        return;
    }
    /*
    Node<T>* current = head;
    Node<T>*next;
    
    while(current!=nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
*/
    removeAllNodes();

}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    return tail;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    
    Node<T>* current;
    for(current=head; current!=nullptr; current=current->next) {
        if(current->data == data) {
            return current;
        }
    }
    return nullptr;
}

template<class T>
int LinkedList<T>::getNumberOfNodes() const {
    int i=0;
    Node<T>* current;
    for(current=head; current!=nullptr; current=current->next) {
        i++;
    }
    return i;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    return this->head == nullptr;
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    
    Node<T>* current;
    
    for(current=head; current!=nullptr; current=current->next) {
        if(current == node) {
            return true;
        }
    }
    return false;
}

template<class T>
void LinkedList<T>::insertAtTheHead(const T &data) {
    
    Node<T>* newNode = new Node<T>(data, nullptr, nullptr);
    
    if(isEmpty()) {
        this->head = newNode;
        this->tail = head;
    }
    else {
        newNode->next = head;
        this->head = newNode;
    }

}

template<class T>
void LinkedList<T>::insertAtTheTail(const T &data) {
    
    Node<T>* newNode = new Node<T>(data,nullptr, nullptr);
    
    if(isEmpty()) {
        this->head = newNode;
        this->tail = head;
    }
    else {
        newNode->prev = tail;
        this->tail->next = newNode;
        this->tail = newNode;
    }
}

template<class T>
void LinkedList<T>::insertSorted(const T &data) {

    Node<T>* current;
    
    if(isEmpty() || data<= head->data) {
        insertAtTheHead(data);
    }
    else if(data>= tail->data) {
        insertAtTheTail(data);
    }
    else {
        
        Node<T>* newNode = new Node<T>(data,nullptr,nullptr);

        for(current=head; current!=nullptr; current=current->next) {
            if(current->data <= newNode->data && current->next->data >= newNode->data) {

                newNode->prev = current;
                newNode->next = current->next;
                current->next->prev = newNode;
                current->next = newNode;
                break;
            }
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    
    if(isEmpty() || !this->contains(node)) {
        return;
    }
    else if(head == node) {
        if(tail == node) {
            head = nullptr;
            tail = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;
        }


    }
    else if(tail==node) {
        tail = tail->prev;
        tail->next = nullptr;


    }
    else {
        node->prev->next = node->next;
        node->next->prev = node->prev;

    }
    delete node;

}

template<class T>
void LinkedList<T>::removeNode(const T &data) {

    Node<T>* current;
    for(current=head; current!=nullptr; current=current->next) {
        if(current->data==data) {
            if(current==this->tail) {
                tail = current->prev;
                tail->next = nullptr;
            }
            else if(current == this->head) {
                head = current->next;
                head->prev = nullptr;
            }
            else {
                current->next->prev = current->prev;
                current->prev->next = current->next;
            }
            break;
        }
    }
    delete current;
    
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    Node<T>* current;
    Node<T>* next;
    current = head;
    while(current!=nullptr) {
        next = current->next;
        removeNode(current);
        current = next;
    }
    head = nullptr;
    
}

template<class T>
void LinkedList<T>::print() const {
    std::cout << "Printing the linked list ..." << std::endl;

    if (this->isEmpty()) {
        std::cout << "empty" << std::endl;
        return;
    }

    Node<T> *node = this->head;

    while (node) {
        std::cout << *node << std::endl;
        node = node->next;
    }
}

template<class T>
T *LinkedList<T>::toArray() const {
    int i=0;
    T * arr = nullptr;

    if(!isEmpty()) {

        Node<T>* current;
        int arraySize = getNumberOfNodes();
        arr = new T[arraySize];
        
        for(current=head; current!=nullptr; current=current->next) {
            arr[i] = current->data;
            i++;
        }
    }
    
    return arr;


}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    
    if(!(this->isEmpty())) {
        this->removeAllNodes();
    }
    if(rhs.isEmpty()) {
        return *this;
    }
    
    Node<T>*current;

    for(current = rhs.head; current != nullptr; current = current->next) {
        if(this->isEmpty()) {
            this->head = new Node<T> (current->data,nullptr, nullptr);
            this->tail = head;
        }
        else {
            this->tail->next = new Node<T>(current->data,this->tail,nullptr);
            this->tail = this->tail->next;
        }
    }
    return *this;
}


#endif //LINKEDLIST_H
