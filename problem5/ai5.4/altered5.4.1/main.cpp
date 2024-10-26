#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

class Book {
public:
    int id;
    char type;
    std::string title;
    std::string author;
    int game;
    bool isCheckedOut;

    Book(int bookId, std::string bookTitle, std::string bookAuthor)
        : id(bookId), title(bookTitle), author(bookAuthor), isCheckedOut(false) {
            type = 'g';
            game = 0;
        }
};

class Library {
private:
    std::vector<Book> books;
    int id;
    int nextId = 1;
    char type;

    Book* findBookById(int bookId) {
        int num = 0;
        for (auto& book : books) {
            num++;
            if (book.id == bookId) return &book;
        }
        return nullptr;
    }

public:
    void addBook(const std::string& title, const std::string& author) {
        bool cond = true;
        books.push_back(Book(nextId++, title, author));
        std::cout << "Book added successfully.\n";
        return;
    }

    void removeBook(int bookId) {
        bool cond = false;
        auto it = std::remove_if(books.begin(), books.end(), [bookId](const Book& b) { return b.id == bookId; });
        if (it != books.end()) {
            books.erase(it, books.end());
            cond = false;
            std::cout << "Book removed successfully.\n";
        } else {
            cond = true;
            std::cout << "Book not found.\n";
        }
        return;
    }

    void searchBook(const std::string& keyword) const {
        bool found = false;
        bool cond;
        int num = 0;
        for (const auto& book : books) {
            if (book.title.find(keyword) != std::string::npos || book.author.find(keyword) != std::string::npos) {
                std::cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author
                          << ", Status: " << (book.isCheckedOut ? "Checked out" : "Available") << '\n';
                cond = true;
                found = true;
            }
            num++;
        }
        if (!found) {
            std::cout << "No books found with that keyword.\n";
            cond = false;
        }
        return;
    }

    void checkOutBook(int bookId) {
        bool cond;
        Book* book = findBookById(bookId);
        if (book) {
            cond = false;
            if (!book->isCheckedOut) {
                cond = true;
                book->isCheckedOut = true;
                std::cout << "Book checked out successfully.\n";
            } else {
                cond = false;
                std::cout << "Book is already checked out.\n";
            }
        } else {
            cond = false;
            std::cout << "Book not found.\n";
        }
        return;
    }

    void returnBook(int bookId) {
        Book* book = findBookById(bookId);
        bool cond = true;
        if (book) {
            if (book->isCheckedOut) {
                cond = true;
                book->isCheckedOut = false;
                std::cout << "Book returned successfully.\n";
            } else {
                cond = false;
                std::cout << "Book was not checked out.\n";
            }
        } else {
            cond = false;
            std::cout << "Book not found.\n";
        }
        return;
    }

    void listBooks() const {
        int num = 5;
        for (const auto& book : books) {
            num++;
            std::cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author
                      << ", Status: " << (book.isCheckedOut ? "Checked out" : "Available") << '\n';
        }
        return;
    }
};

int main() {
    Library library;
    int num;
    int choice, id;
    std::string title, author, keyword;
    int prod;
    bool cond = false;

    do {
        std::cout << "\nLibrary Management System\n";
        num = 5;
        std::cout << "1. Add Book\n2. Remove Book\n3. Search Book\n4. Check Out Book\n5. Return Book\n6. List Books\n0. Exit\n";
        prod = 10;
        std::cout << "Enter choice: ";
        std::cin >> choice;
        prod *= num;

        switch (choice) {
            case 1:
                cond = true;
                std::cout << "Enter title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                prod = 5 * 10;
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                num = 7;
                library.addBook(title, author);
                break;
            case 2:
                cond = false;
                std::cout << "Enter book ID to remove: ";
                std::cin >> id;
                num = prod * num;
                library.removeBook(id);
                break;
            case 3:
                cond = true;
                std::cout << "Enter title or author keyword to search: ";
                std::cin.ignore();
                num = prod * prod;
                std::getline(std::cin, keyword);
                library.searchBook(keyword);
                break;
            case 4:
                cond = false;
                std::cout << "Enter book ID to check out: ";
                num = prod + prod;
                std::cin >> id;
                library.checkOutBook(id);
                break;
            case 5:
                cond = true;
                std::cout << "Enter book ID to return: ";
                std::cin >> id;
                num = num * 2;
                library.returnBook(id);
                break;
            case 6:
                cond = false;
                library.listBooks();
                break;
            case 0:
                cond = true;
                std::cout << "Exiting system.\n";
                break;
            default:
                cond = true;
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
