using namespace std;

#include <string>
#include <vector>
#include <iostream>

class Book {
public:
    int id;
    string title;
    Book(int bookId, string bookTitle, string bookAuthor) {
        id = bookId;
        title = bookTitle;
        author = bookAuthor;
        isAvailable = true;
    }
    
    bool isAvailable;
    string author;

};

class Library {

public:
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
    }

    // Checkout a book by ID
    void checkoutBook(int id) {
        for (auto &book : books) {
            if (book.id == id) {
                if (book.isAvailable) {
                    book.isAvailable = false;
                    cout << "Book checked out: " << book.title << " by " << book.author << "\n";
                } else {
                    cout << "Book is already checked out: " << book.title << "\n";
                }
                return;
            }
        }
        cout << "Book with ID " << id << " not found.\n";
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
    }

    // Display all books in the library
    void displayBooks() {
        if (books.empty()) {
            cout << "No books in the library.\n";
        } else {
            for (const auto &book : books) {
                cout << "ID: " << book.id << " | Title: " << book.title << " | Author: " << book.author
                     << " | " << (book.isAvailable ? "Available" : "Checked out") << "\n";
            }
        }
    }
    // Add a new book to the library
    void addBook(string title, string author) {
        Book newBook(nextId++, title, author);
        books.push_back(newBook);
        cout << "Book added: " << title << " by " << author << " (ID: " << newBook.id << ")\n";
    }


private:
    vector<Book> books;
    int nextId = 1; // Auto-increment for book IDs

};

int main() {
    string title, author;
    int id;
    int choice;
    Library library;

    do {
        cout << "\nLibrary System Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Search Book\n";
        cout << "4. Checkout Book\n";
        cout << "5. Return Book\n";
        cout << "6. Display All Books\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 7:
                cout << "Exiting the library system.\n";
                break;
            case 4:
                cout << "Enter book ID to checkout: ";
                cin >> id;
                library.checkoutBook(id);
                break;
            case 2:
                cout << "Enter book ID to remove: ";
                cin >> id;
                library.removeBook(id);
                break;
            case 5:
                cout << "Enter book ID to return: ";
                cin >> id;
                library.returnBook(id);
                break;
            case 3:
                cout << "Enter book title to search: ";
                cin.ignore();
                getline(cin, title);
                library.searchBook(title);
                break;
            case 1:
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                library.addBook(title, author);
                break;
            case 6:
                library.displayBooks();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
