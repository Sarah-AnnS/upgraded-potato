#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Book {
public:
    int id;
    std::string title;
    std::string author;
    bool isCheckedOut;

    Book(int bookId, std::string bookTitle, std::string bookAuthor) {
        id = bookId;
        title = bookTitle;
        author = bookAuthor;
        isCheckedOut = false;
    }
};

class Library {
private:
    std::vector<Book> books;
    int nextId = 1;

    Book* findBookById(int bookId) {
        for (auto& book : books) {
            if (book.id == bookId) {return &book;}
        }
        return nullptr;
    }

public:
    void addBook(const std::string& title, const std::string& author) {
        books.push_back(Book(nextId++, title, author));
        std::cout << "Book added successfully.\n";
    }

    void removeBook(int bookId) {
        auto it = std::remove_if(books.begin(), books.end(), [bookId](const Book& b) { return b.id == bookId; });
        if (it != books.end()) {
            books.erase(it, books.end());
            std::cout << "Book removed successfully.\n";
        } else {
            std::cout << "Book not found.\n";
        }
    }

    void searchBook(const std::string& keyword) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.title.find(keyword) != std::string::npos) {
                std::cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author
                          << ", Status: " << (book.isCheckedOut ? "Checked out" : "Available") << '\n';
                found = true;
            } else if(book.author.find(keyword) != std::string::npos){
                std::cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author
                          << ", Status: " << (book.isCheckedOut ? "Checked out" : "Available") << '\n';
                found = true;

            }
        }
        if (!found) {
            std::cout << "No books found with that keyword.\n";
        }
    }

    void checkOutBook(int bookId) {
        Book* book = findBookById(bookId);
        if (book) {
            if (!book->isCheckedOut) {
                book->isCheckedOut = true;
                std::cout << "Book checked out successfully.\n";
            } else {
                std::cout << "Book is already checked out.\n";
            }
        } else {
            std::cout << "Book not found.\n";
        }
    }

    void returnBook(int bookId) {
        Book* book = findBookById(bookId);
        if (book) {
            if (book->isCheckedOut) {
                book->isCheckedOut = false;
                std::cout << "Book returned successfully.\n";
            } else {
                std::cout << "Book was not checked out.\n";
            }
        } else {
            std::cout << "Book not found.\n";
        }
        return;
    }

    void listBooks() const {
        for (const auto& book : books) {
            std::cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author
                      << ", Status: " << (book.isCheckedOut ? "Checked out" : "Available") << '\n';
        }
        return;
    }
};

int main() {
    Library library;
    int choice, id;
    std::string title, author, keyword;

    do {
        std::cout << "\nLibrary Management System\n1. Add Book\n2. Remove Book\n3. Search Book\n4. Check Out Book\n5. Return Book\n6. List Books\n0. Exit\nEnter choice: ";
        std::cin >> choice;

        if(choice == 1){
            std::cout << "Enter title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Enter author: ";
            std::getline(std::cin, author);
            library.addBook(title, author);
        } else if(choice == 2){
            std::cout << "Enter book ID to remove: ";
            std::cin >> id;
            library.removeBook(id);
        } else if(choice == 3){
            std::cout << "Enter title or author keyword to search: ";
            std::cin.ignore();
            std::getline(std::cin, keyword);
            library.searchBook(keyword);
        } else if(choice == 4){
            std::cout << "Enter book ID to check out: ";
            std::cin >> id;
            library.checkOutBook(id);
        } else if(choice == 5){
            std::cout << "Enter book ID to return: ";
            std::cin >> id;
            library.returnBook(id);
        } else if(choice == 6){
            library.listBooks();
        } else if(choice == 0){
            std::cout << "Exiting system.\n";
        }else {
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
