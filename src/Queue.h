#pragma once

struct queueNode {
    int data;
    queueNode* next;
    queueNode(int value) : data(value), next(nullptr) {}
};

class Queue {
private:
    queueNode* front;
    queueNode* rear;

public:
    Queue();              // Constructor
    ~Queue();             // Destructor
    void enqueue(int value); // Add element to the end of the queue
    int dequeue();        // Remove element from the front of the queue
    bool isEmpty() const; // Check if the queue is empty
    int frontElement() const;
};