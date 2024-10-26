#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool is_checked_out;

    Book(int bookId, string bookTitle, string bookAuthor) {
        id = bookId;
        title = bookTitle;
        author = bookAuthor;
        is_checked_out = false;
    }

    void displayInfo() const {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author
             << ", Status: " << (is_checked_out ? "Checked Out" : "Available") << endl;
        return;
    }
};

class Library {
private:
    unordered_map<int, Book> books; // Book ID as key, Book object as value

public:
    void addBook(int id, const string &title, const string &author) {
        if (books.find(id) == books.end()) {
            books[id] = Book(id, title, author);
            cout << "Book added: " << title << endl;
        } else {
            cout << "Book with ID " << id << " already exists." << endl;
        }
        return;
    }

    void removeBook(int id) {
        if (books.erase(id)) {
            cout << "Book with ID " << id << " removed." << endl;
        } else {
            cout << "No book found with ID " << id << endl;
        }
        return;
    }

    void searchBook(int id) const {
        auto it = books.find(id);
        if (it != books.end()) {
            it->second.displayInfo();
        } else {
            cout << "No book found with ID " << id << endl;
        }
        return;
    }

    void listAllBooks() const {
        if (books.empty()) {
            cout << "No books in the library." << endl;
            return;
        }
        for (const auto &pair : books) {
            pair.second.displayInfo();
        }
        return;
    }

    void checkoutBook(int id) {
        auto it = books.find(id);
        if (it != books.end()) {
            if (!it->second.is_checked_out) {
                it->second.is_checked_out = true;
                cout << "Book checked out: " << it->second.title << endl;
            } else {
                cout << "Book is already checked out." << endl;
            }
        } else {
            cout << "No book found with ID " << id << endl;
        }
        return;
    }

    void returnBook(int id) {
        auto it = books.find(id);
        if (it != books.end()) {
            if (it->second.is_checked_out) {
                it->second.is_checked_out = false;
                cout << "Book returned: " << it->second.title << endl;
            } else {
                cout << "Book was not checked out." << endl;
            }
        } else {
            cout << "No book found with ID " << id << endl;
        }
        return;
    }
};

int main() {
    Library library;
    int choice;
    int id;
    string title;
    string author;

    while (true) {
        cout << "\nLibrary Inventory System\n1. Add Book\n2. Remove Book\n3. Search Book\n4. List All Books\n5. Checkout Book\n6. Return Book\n7. Exit\nEnter choice: ";
        cin >> choice;

        if(choice == 1){
            cout << "Enter Book ID: ";
            cin >> id;
            cout << "Enter Book Title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter Book Author: ";
            getline(cin, author);
            library.addBook(id, title, author);
        } else if(choice == 2){
            cout << "Enter Book ID to remove: ";
            cin >> id;
            library.removeBook(id);
        } else if(choice == 3){
            cout << "Enter Book ID to search: ";
            cin >> id;
            library.searchBook(id);
        }else if(choice == 4){
            library.listAllBooks();
        } else if(choice == 5){
            cout << "Enter Book ID to checkout: ";
            cin >> id;
            library.checkoutBook(id);
        } else if(choice == 6){
            cout << "Enter Book ID to return: ";
            cin >> id;
            library.returnBook(id);
        } else if(choice == 7){
            cout << "Exiting program." << endl;
            return 0;
        } else{
            cout << "Invalid choice. Please try again." << endl;
        }

    }
}
