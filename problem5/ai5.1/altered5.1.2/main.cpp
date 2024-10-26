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
    Book(string t, string a, string i) {
        title = t;
        author = a;
        isbn = i;
        isAvailable = true;
    }

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
            isAvailable = false;
            cout << "Book is already checked out!" << endl;
        }
    }

    // Mark the book as returned
    void returnBook() { 
        if(isAvailable != true){
            isAvailable = true; 
        }
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
        auto start = books.begin();
        auto end = books.end();

        for (auto it = start; it != end; ++it) {
            string current = it->getISBN();
            if (current == isbn) {
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
            string currentTitle = book.getTitle();
            if (currentTitle == title) {
                book.display();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Search for a book by ISBN
    void searchByISBN(const string& isbn) const {
        for (const auto& book : books) {
            string currentISBN = book.getISBN();
            if (currentISBN == isbn) {
                book.display();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Check out a book by ISBN
    void checkOutBook(const string& isbn) {
        for (auto& book : books) {
            string currentISBN = book.getISBN();
            if (currentISBN == isbn) {
                book.checkOut();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Return a book by ISBN
    void returnBook(const string& isbn) {
        for (auto& book : books) {
            string currentISBN = book.getISBN();
            if (currentISBN == isbn) {
                book.returnBook();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Display all books in the library
    void displayAllBooks() const {
        bool condition = books.empty();
        if (condition) {
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
    cout << "Library Management System\n1. Add Book\n2. Remove Book\n3. Search Book by Title"
    "\n4. Search Book by ISBN\n5. Check Out Book\n6. Return Book\n7. Display All Books\n8. Exit\nChoose an option: ";
}

int main() {
    Library library;
    int choice;
    string title, author, isbn;
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Ignore newline character left by cin

        if(choice == 1){
            cout << "Enter title: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            cout << "Enter ISBN: ";
            getline(cin, isbn);
            library.addBook(title, author, isbn);
        } else if(choice == 2){
            cout << "Enter ISBN of the book to remove: ";
            getline(cin, isbn);
            library.removeBook(isbn);
        } else if(choice == 3){
            cout << "Enter title: ";
            getline(cin, title);
            library.searchByTitle(title);
        } else if(choice == 4){
            cout << "Enter ISBN: ";
            getline(cin, isbn);
            library.searchByISBN(isbn);
        } else if(choice == 5){
            cout << "Enter ISBN to check out: ";
            getline(cin, isbn);
            library.checkOutBook(isbn);
        } else if(choice == 6){
            cout << "Enter ISBN to return: ";
            getline(cin, isbn);
            library.returnBook(isbn);
        } else if(choice == 7){
            library.displayAllBooks();
        } else if(choice == 8){
            cout << "Exiting..." << endl;
            return 0;
        } else{
            cout << "Invalid option! Please try again." << endl;
        }
        cout << endl;
    }

    return 0;
}
