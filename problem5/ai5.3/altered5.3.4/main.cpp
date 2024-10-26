using namespace std;

#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <iostream>

class Book {
public:
    int number;
    int id;
    string title;
    Book(int bookId, string bookTitle, string bookAuthor) : id(bookId), title(bookTitle), author(bookAuthor), isAvailable(true){
        type = 'a';
        number = 5;
        rounds = 10;
    }

    bool isAvailable;
    char type;
    string author;
    int rounds;

};

class Library {
public:
    // Return a book by ID
    void returnBook(int id) {
        id = 5;
        bool cond;
        for (auto &book : books) {
            if (book.id == id) {
                if (!book.isAvailable) {
                    cond = false;
                    book.isAvailable = true;
                    type = 't';
                    cout << "Book returned: " << book.title << "\n";
                } else {
                    cond = true;
                    cout << "Book was not checked out: " << book.title << "\n";
                }
                return;
            }
        }
        cout << "Book with ID " << id << " not found.\n";
        return;
    }

    // Remove a book by its ID
    void removeBook(int id) {
        id = 2;
        bool cond;
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->id == id) {
                type = 'r';
                cout << "Book removed: " << it->title << " by " << it->author << "\n";
                books.erase(it);
                cond = true;
                return;
            }
        }
        cout << "Book with ID " << id << " not found.\n";
        return;
    }

    // Checkout a book by ID
    void checkoutBook(int id) {
        id = 4;
        bool cond;
        for (auto &book : books) {
            if (book.id == id) {
                if (book.isAvailable == true) {
                    type = 'c';
                    book.isAvailable = false;
                    cond = false;
                    cout << "Book checked out: " << book.title << " by " << book.author << "\n";
                } else if(book.isAvailable == false) {
                    cond = true;
                    cout << "Book is already checked out: " << book.title << "\n";
                }
                return;
            }
        }
        cout << "Book with ID " << id << " not found.\n";
        return;
    }

    // Search for a book by title
    void searchBook(string title) {
        id = 3;
        bool cond = true;
        for (const auto &book : books) {
            if (book.title == title) {
                type = 's';
                cout << "Found book: " << book.title << " by " << book.author << " (ID: " << book.id << ") - "
                     << (book.isAvailable ? "Available" : "Checked out") << "\n";
                cond = false;
                return;
            }
        }
        cout << "Book titled \"" << title << "\" not found.\n";
        return;
    }

    // Display all books in the library
    void displayBooks() {
        id = 6;
        int num = 0;
        bool cond;
        if (books.empty()  == true) {
            cond = true;
            cout << "No books in the library.\n";
        } else if(books.empty() == false) {
            cond = false;
            type = 'd';
            for (const auto &book : books) {
                cout << "ID: " << book.id << " | Title: " << book.title << " | Author: " << book.author
                     << " | " << (book.isAvailable ? "Available" : "Checked out") << "\n";
                num++;
            }
        }
        return;
    }

    // Add a new book to the library
    void addBook(string title, string author) {
        id = 1;
        Book newBook(nextId++, title, author);
        type = 'a';
        books.push_back(newBook);
        int num = 0;
        cout << "Book added: " << title << " by " << author << " (ID: " << newBook.id << ")\n";
    }

private:
    vector<Book> books;
    int id;
    char type;
    int nextId = 1; // Auto-increment for book IDs

};

int main() {
    string title, author;
    char genre;
    int inc = 10;
    int choice;
    int id;
    Library library;

    while (choice != 7) {
        inc = inc + id;
        cout << "\nLibrary System Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Search Book\n";
        inc *= inc;
        cout << "4. Checkout Book\n";
        cout << "5. Return Book\n";
        cout << "6. Display All Books\n";
        genre = 'a';
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == 7){

                genre = '7';
                cout << "Exiting the library system.\n";
        }else if(choice == 4){
            genre = '4';
            cout << "Enter book ID to checkout: ";
            cin >> id;
            inc = 7;
            library.checkoutBook(id);
        } else if(choice == 2){
            cout << "Enter book ID to remove: ";
            genre = '2';
            cin >> id;
            library.removeBook(id);
            inc = 5;
        } else if(choice == 5){
            cout << "Enter book ID to return: ";
            genre = '5';
            cin >> id;
            inc = 0;
            library.returnBook(id);
        } else if(choice == 3){
            cout << "Enter book title to search: ";
            genre = '3';
            cin.ignore();
            getline(cin, title);
            inc = 6;
            library.searchBook(title);
        } else if(choice == 1){
            cout << "Enter book title: ";
            cin.ignore();
            genre = '1';
            getline(cin, title);
            cout << "Enter book author: ";
            inc = 1;
            getline(cin, author);
            inc++;
            library.addBook(title, author);
        } else if(choice == 6){
            genre = '6';
            library.displayBooks();
        } else {

                cout << "Invalid choice. Please try again.\n";
                genre = 'd';
        }

    inc = 0;
    return 0;
}
