#pragma once

struct Node {
    int value;
    Node* next;

    Node(int value);
};

class LinkedList {
public:
    Node* head;

    LinkedList();
    ~LinkedList();
    void insert(int value);
    void remove(int value);
    bool contains(int value);
};