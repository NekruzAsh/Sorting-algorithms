#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() : head(nullptr) {} // Constructor initializes head to nullptr

LinkedList::~LinkedList() { // Destructor to deallocate memory
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::insert(Student data) { // Insert new node with given data
    Node* newNode = new Node(data); // Create a new node
    newNode->next = head; // Set new node's next pointer to current head
    head = newNode; // Update head to point to new node
}

void LinkedList::mergeSortFirstName(bool ascending) { // Merge sort by first name
    head = mergeSortHelper(head, ascending); // Call recursive merge sort helper
}

void LinkedList::quickSortLastName(bool ascending) { // Quick sort by last name
    quickSortHelper(head, getLastNode(head), ascending); // Call recursive quick sort helper
}

void LinkedList::insertionSortIdNumber(bool ascending) { // Insertion sort by ID number
    if (head == nullptr || head->next == nullptr)
        return;

    Node* sorted = nullptr;
    Node* current = head;

    while (current != nullptr) {
        Node* next = current->next;
        if (sorted == nullptr || (ascending && current->data.getIdNumber() < sorted->data.getIdNumber()) ||
            (!ascending && current->data.getIdNumber() > sorted->data.getIdNumber())) {
            current->next = sorted;
            sorted = current;
        }
        else {
            Node* temp = sorted;
            while (temp->next != nullptr && ((ascending && temp->next->data.getIdNumber() < current->data.getIdNumber()) ||
                (!ascending && temp->next->data.getIdNumber() > current->data.getIdNumber()))) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    head = sorted;
}

void LinkedList::display() const { // Display linked list nodes
    Node* current = head;
    while (current != nullptr) {
        std::cout << "First Name: " << current->data.getFirstName() << ", ";
        std::cout << "Last Name: " << current->data.getLastName() << ", ";
        std::cout << "ID Number: " << current->data.getIdNumber() << std::endl;
        current = current->next;
    }
}

Node* LinkedList::merge(Node* left, Node* right, bool ascending) { // Merge two sorted linked lists
    Node* result = nullptr;

    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;

    if (ascending) {
        if (left->data.getFirstName() <= right->data.getFirstName()) {
            result = left;
            result->next = merge(left->next, right, ascending);
        }
        else {
            result = right;
            result->next = merge(left, right->next, ascending);
        }
    }
    else {
        if (left->data.getFirstName() >= right->data.getFirstName()) {
            result = left;
            result->next = merge(left->next, right, ascending);
        }
        else {
            result = right;
            result->next = merge(left, right->next, ascending);
        }
    }

    return result;
}
// Merge sort helper
Node* LinkedList::mergeSortHelper(Node* head, bool ascending) {
    if (head == nullptr || head->next == nullptr)
        return head;

    Node* slow = head;
    Node* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* mid = slow->next;
    slow->next = nullptr;

    Node* left = mergeSortHelper(head, ascending);
    Node* right = mergeSortHelper(mid, ascending);

    return merge(left, right, ascending);
}
// Partition function for quick sort
Node* LinkedList::partition(Node* low, Node* high, bool ascending) {
    Student pivot = high->data;
    Node* i = low->prev;

    for (Node* j = low; j != high; j = j->next) {
        if ((ascending && j->data.getLastName() <= pivot.getLastName()) ||
            (!ascending && j->data.getLastName() >= pivot.getLastName())) {
            i = (i == nullptr) ? low : i->next;
            std::swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? low : i->next;
    std::swap(i->data, high->data);
    return i;
}
// Quick sort helper
void LinkedList::quickSortHelper(Node* low, Node* high, bool ascending) {
    if (high != nullptr && low != high && low != high->next) {
        Node* pi = partition(low, high, ascending);
        quickSortHelper(low, pi->prev, ascending);
        quickSortHelper(pi->next, high, ascending);
    }
}
// Get the last node of the linked list
Node* LinkedList::getLastNode(Node* head) {
    if (head == nullptr)
        return nullptr;

    while (head->next != nullptr)
        head = head->next;

    return head;
}