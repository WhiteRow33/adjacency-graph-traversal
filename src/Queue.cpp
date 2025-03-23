#include "Queue.h"
#include <iostream>
using namespace std;

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

//Add element to rear of the queue
void Queue::enqueue(int value) {
    queueNode* newNode = new queueNode(value);
    if (isEmpty()) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

//Pop element from front of the queue
int Queue::dequeue() {
    if (isEmpty()) {
        return -1;
    }
    queueNode* temp = front;
    int value = temp->data;
    front = front->next;
    delete temp;
    if (front == nullptr) {
        rear = nullptr;
    }
    return value;
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

//Return the front element
int Queue::frontElement() const {
    if (isEmpty()) {
        return -1;
    }
    return front->data;
}