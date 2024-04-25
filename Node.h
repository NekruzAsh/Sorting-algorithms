#pragma once

#include "Student.h"

class Node {
public:
    Student data; // Data stored in the node, assumed to be of type Student
    Node* next; // Pointer to the next node in the linked list
    Node* prev; // Pointer to the previous node in the linked list
    // Constructor to initialize the node with given data and null pointers for next and prev
    Node(Student data) : data(data), next(nullptr), prev(nullptr) {}
};