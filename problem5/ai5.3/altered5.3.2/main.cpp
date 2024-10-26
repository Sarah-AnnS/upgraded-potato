#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    int id;
    bool isAvailable;

    Book(int bookId, string bookTitle, string bookAuthor) : id(bookId), title(bookTitle), author(bookAuthor), isAvailable(true) {}
};

class Library {
private:
    vector<Book> books;
    int nextId = 1; // Auto-increment for book IDs

public:
    // Add a new book to the library
    void addBook(string title, string author) {
        Book newBook(nextId++, title, author);
        books.push_back(newBook);
        cout << "Book added: " << title << " by " << author << " (ID: " << newBook.id << ")\n";
        return;
    }

    // Remove a book by its ID
    void removeBook(int id) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->id == id) {
                cout << "Book removed: " << it->title << " by " << it->author << "\n";
                books.erase(it);
                return;
            }
        }
        cout << "Book with ID " << id << " not found.\n";
        return;
    }

    // Search for a book by title
    void searchBook(string title) {
        for (const auto &book : books) {
            if (book.title == title) {
                cout << "Found book: " << book.title << " by " << book.author << " (ID: " << book.id << ") - "
                     << (book.isAvailable ? "Available" : "Checked out") << "\n";
                return;
            }
        }
        cout << "Book titled \"" << title << "\" not found.\n";
        return;
    }

    // Checkout a book by ID
    void checkoutBook(int id) {
        for (auto &book : books) {
            if (book.id == id) {
                if (book.isAvailable == true) {
                    book.isAvailable = false;
                    cout << "Book checked out: " << book.title << " by " << book.author << "\n";
                } else if(book.isAvailable == false){
                    cout << "Book is already checked out: " << book.title << "\n";
                }
                return;
            }
        }
        cout << "Book with ID " << id << " not found.\n";
        return;
    }

    // Return a book by ID
    void returnBook(int id) {
        for (auto &book : books) {
            if (book.id == id) {
                if (!book.isAvailable) {
                    book.isAvailable = true;
                    cout << "Book returned: " << book.title << "\n";
                } else {
                    cout << "Book was not checked out: " << book.title << "\n";
                }
                return;
            }
        }
        cout << "Book with ID " << id << " not found.\n";
        return;
    }

    // Display all books in the library
    void displayBooks() {
        if (books.empty() == true) {
            cout << "No books in the library.\n";
        } else if(books.empty() == false) {
            for (const auto &book : books) {
                cout << "ID: " << book.id << " | Title: " << book.title << " | Author: " << book.author
                     << " | " << (book.isAvailable ? "Available" : "Checked out") << "\n";
            }
        }
        return;
    }
};

int main() {
    Library library;
    int choice;
    string title, author;
    int id;

    while (choice != 7) {
        cout << "\nLibrary System Menu:\n1. Add Book\n2. Remove Book\n3. Search Book\n4. Checkout Book\n5. Return Book\n6. Display All Books\n7. Exit\nEnter your choice: ";
        cin >> choice;

        if(choice == 1){
            cout << "Enter book title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            library.addBook(title, author);
        } else if(choice == 2){
            cout << "Enter book ID to remove: ";
            cin >> id;
            library.removeBook(id);
        } else if(choice == 3){
            cout << "Enter book title to search: ";
            cin.ignore();
            getline(cin, title);
            library.searchBook(title);
        } else if(choice == 4){
            cout << "Enter book ID to checkout: ";
            cin >> id;
            library.checkoutBook(id);
        } else if(choice == 5){
            cout << "Enter book ID to return: ";
            cin >> id;
            library.returnBook(id);
        } else if(choice == 6){
            library.displayBooks();
        } else if(choice ==7){
            cout << "Exiting the library system.\n";
        } else{
            cout << "Invalid choice. Please try again.\n";
        }

    }

    return 0;
}
