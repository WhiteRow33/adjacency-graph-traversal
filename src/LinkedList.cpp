#include <iostream>
#include "LinkedList.h"

Node::Node(int value) : value(value), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::insert(int value) {
    Node* newNode = new Node(value);

    // If the list is empty or the new value is smaller than the head
    if (head == nullptr || head->value > value) {
        newNode->next = head;
        head = newNode;
        return;
    }

    // If the head itself has the value, we skip adding it
    if (head->value == value) {
        delete newNode; // Avoid memory leak
        return;
    }

    // Traverse the list to find the correct position, checking for duplicates
    Node* current = head;
    while (current->next != nullptr && current->next->value < value) {
        current = current->next;
    }

    // Check if the value is already present at the insert position
    if (current->next != nullptr && current->next->value == value) {
        delete newNode; // Avoid memory leak
        return;
    }


    // Insert the new node in the sorted order
    newNode->next = current->next;
    current->next = newNode;
}


void LinkedList::remove(int value) {
    if (head == nullptr) return; // List is empty

    if (head->value == value) { // Node to be removed is the head
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->value != value) {
        current = current->next;
    }

    if (current->next != nullptr) { // Edge found
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

// Check if the list contains a specific value
bool LinkedList::contains(int value) {
    Node* current = head;
    while (current) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}