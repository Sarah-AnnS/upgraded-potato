#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Book class to represent a single book
class Book {
private:
    string title;
    string author;
    string isbn;
    bool isAvailable;
    
public:
    // Constructor
    Book(string t, string a, string i) : title(t), author(a), isbn(i), isAvailable(true) {}

    // Getters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    bool getAvailability() const { return isAvailable; }

    // Mark the book as checked out
    void checkOut() { 
        if (isAvailable) {
            isAvailable = false; 
            cout << "Book checked out successfully!" << endl;
        } else {
            cout << "Book is already checked out!" << endl;
        }
    }

    // Mark the book as returned
    void returnBook() { 
        isAvailable = true; 
        cout << "Book returned successfully!" << endl;
    }

    // Display book information
    void display() const {
        cout << "Title: " << title << ", Author: " << author
             << ", ISBN: " << isbn << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

// Library class to manage the collection of books
class Library {
private:
    vector<Book> books;
    
public:
    // Add a book to the library
    void addBook(const string& title, const string& author, const string& isbn) {
        books.push_back(Book(title, author, isbn));
        cout << "Book added successfully!" << endl;
    }

    // Remove a book from the library by ISBN
    void removeBook(const string& isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getISBN() == isbn) {
                books.erase(it);
                cout << "Book removed successfully!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Search for a book by title
    void searchByTitle(const string& title) const {
        for (const auto& book : books) {
            if (book.getTitle() == title) {
                book.display();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Search for a book by ISBN
    void searchByISBN(const string& isbn) const {
        for (const auto& book : books) {
            if (book.getISBN() == isbn) {
                book.display();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Check out a book by ISBN
    void checkOutBook(const string& isbn) {
        for (auto& book : books) {
            if (book.getISBN() == isbn) {
                book.checkOut();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Return a book by ISBN
    void returnBook(const string& isbn) {
        for (auto& book : books) {
            if (book.getISBN() == isbn) {
                book.returnBook();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Display all books in the library
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "No books in the library!" << endl;
        } else {
            for (const auto& book : books) {
                book.display();
            }
        }
    }
};

// Function to display the menu
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Remove Book" << endl;
    cout << "3. Search Book by Title" << endl;
    cout << "4. Search Book by ISBN" << endl;
    cout << "5. Check Out Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Books" << endl;
    cout << "8. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
    Library library;
    int choice;
    string title, author, isbn;
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Ignore newline character left by cin

        switch (choice) {
            case 1:
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter ISBN: ";
                getline(cin, isbn);
                library.addBook(title, author, isbn);
                break;
                
            case 2:
                cout << "Enter ISBN of the book to remove: ";
                getline(cin, isbn);
                library.removeBook(isbn);
                break;
                
            case 3:
                cout << "Enter title: ";
                getline(cin, title);
                library.searchByTitle(title);
                break;

            case 4:
                cout << "Enter ISBN: ";
                getline(cin, isbn);
                library.searchByISBN(isbn);
                break;

            case 5:
                cout << "Enter ISBN to check out: ";
                getline(cin, isbn);
                library.checkOutBook(isbn);
                break;

            case 6:
                cout << "Enter ISBN to return: ";
                getline(cin, isbn);
                library.returnBook(isbn);
                break;

            case 7:
                library.displayAllBooks();
                break;
                
            case 8:
                cout << "Exiting..." << endl;
                return 0;

            default:
                cout << "Invalid option! Please try again." << endl;
        }
        cout << endl;
    }

    return 0;
}
