#include "Inventory.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Constructor
Inventory::Inventory() : head(nullptr) {
    // Vector is automatically initialized as empty
}

// Destructor - Important! Clean up dynamically allocated memory
Inventory::~Inventory() {
    // Delete all Book objects to prevent memory leaks
    while (head) {
        Node* next = head->next; 
        delete head;
        head = next;
    }
}

// Add a book to the inventory (sorted by title alphabetically)
void Inventory::addBook(Book* bookPtr) {
    if (bookPtr == nullptr) {
        std::cout << "Error: Cannot add null book pointer.\n";
        return;
    }
    Node* newNode = new Node(bookPtr);

    if (!head || bookPtr->getTitle() < head->data->getTitle()){
        newNode->next = head;
        head = newNode;
        cout << "Book '" << bookPtr->getTitle() << "' added at head." << endl;
        return;
    }
    // Find the correct position to insert (alphabetical order by title)
    Node* current = head;
    while (current->next && current->next->data->getTitle() < bookPtr->getTitle()){
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    cout << "Book '" << bookPtr->getTitle() << "' added to inventory." << endl;

}

// Display all books in the inventory
void Inventory::displayAll() const {
    if (!head) {
        std::cout << "No books in inventory.\n";
        return;
    }

    std::cout << "\n=== INVENTORY CONTENTS ===\n";
    size_t count = 0;
    Node* current = head;
    while(current){
        current = current->next;
        ++count;
    }
    std::cout << "Total books: " << count << "\n\n";
    count = 0;
    current = head;
    while(current){
        cout << "Book #" << ++count << ":" << endl;
        current->data->displayInfo();
        current = current->next;
    }
    std::cout << "\n";
}

// Remove a book by title
void Inventory::removeBook(const std::string& title) {
    if(!head){
        cout << "Inventory is empty." << endl;
        return;
    }
    if(head->data->getTitle() == title){
        Node* temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
        cout << "Removed book '" << title << "'." << endl;
        return;
    }
    Node* current = head;
    while(current->next && current->next->data->getTitle() != title){
        current = current->next;
    }
    if (current->next){
        Node* temp = current->next;
        current->next = temp->next;
        delete temp->data;
        delete temp;
        cout << "Removed book '" << title << "'." << endl;
    } else {
        cout << "Book '" << title << "' not found." << endl;
    }
}

// Get the number of books
size_t Inventory::getBookCount() const {
    size_t count = 0;
    Node* current = head;
    while (current){
        count++;
        current = current->next;
    }
    return count;
}

// Search for a book by title
Book* Inventory::findBook(const std::string& title) const {
    Node* current = head;
    while(current){
        if(current->data->getTitle() == title){
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

// Check if inventory is empty
bool Inventory::isEmpty() const {
    return head == nullptr;
}