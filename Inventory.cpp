#include "Inventory.h"
#include <iostream>
#include <algorithm>

// Constructor
Inventory::Inventory() {
    // Vector is automatically initialized as empty
}

// Destructor - Important! Clean up dynamically allocated memory
Inventory::~Inventory() {
    // Delete all Book objects to prevent memory leaks
    for (Book* book : books) {
        delete book;
    }
    books.clear();
}

// Add a book to the inventory (sorted by title alphabetically)
void Inventory::addBook(Book* bookPtr) {
    if (bookPtr == nullptr) {
        std::cout << "Error: Cannot add null book pointer.\n";
        return;
    }

    // Find the correct position to insert (alphabetical order by title)
    auto insertPos = std::upper_bound(books.begin(), books.end(), bookPtr,
        [](const Book* a, const Book* b) {
            return a->getTitle() < b->getTitle();
        });

    books.insert(insertPos, bookPtr);
    std::cout << "Book '" << bookPtr->getTitle() << "' added to inventory.\n";
}

// Display all books in the inventory
void Inventory::displayAll() const {
    if (books.empty()) {
        std::cout << "No books in inventory.\n";
        return;
    }

    std::cout << "\n=== INVENTORY CONTENTS ===\n";
    std::cout << "Total books: " << books.size() << "\n\n";
    
    for (size_t i = 0; i < books.size(); ++i) {
        std::cout << "Book #" << (i + 1) << ":\n";
        books[i]->displayInfo();
    }
    std::cout << "\n";
}

// Remove a book by title
void Inventory::removeBook(const std::string& title) {
    auto it = std::find_if(books.begin(), books.end(),
        [&title](const Book* book) {
            return book->getTitle() == title;
        });

    if (it != books.end()) {
        std::cout << "Removing book: " << (*it)->getTitle() << "\n";
        delete *it; // Free the memory
        books.erase(it);
    } else {
        std::cout << "Book '" << title << "' not found in inventory.\n";
    }
}

// Get the number of books
size_t Inventory::getBookCount() const {
    return books.size();
}

// Search for a book by title
Book* Inventory::findBook(const std::string& title) const {
    auto it = std::find_if(books.begin(), books.end(),
        [&title](const Book* book) {
            return book->getTitle() == title;
        });
    
    return (it != books.end()) ? *it : nullptr;
}

// Check if inventory is empty
bool Inventory::isEmpty() const {
    return books.empty();
}