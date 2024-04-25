#pragma once

#include "Node.h"

class LinkedList {
private:
    Node* head; // Pointer to the first node in the linked list

public:
    // Constructor
    LinkedList();
    // Destructor
    ~LinkedList();
    // Function to insert a new node with given data into the linked list
    void insert(Student data);
    // Sorting functions
    void mergeSortFirstName(bool ascending);
    void quickSortLastName(bool ascending);
    void insertionSortIdNumber(bool ascending);
    // Function to display the linked list
    void display() const;
    // Helper functions for sorting algorithms
    Node* merge(Node* left, Node* right, bool ascending); // Merge two sorted linked lists
    Node* mergeSortHelper(Node* head, bool ascending); // Recursive helper function for merge sort
    Node* partition(Node* low, Node* high, bool ascending); // Partitioning function for quick sort

    void quickSortHelper(Node* low, Node* high, bool ascending); // Recursive helper function for quick sort
    Node* getLastNode(Node* head); // Get the last node of the linked list
};