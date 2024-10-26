#include <iostream>
#include <vector>
#include <string>

class Book {
public:
    std::string title;
    std::string author;
    int publicationYear;
    bool isAvailable;

    Book(std::string t, std::string a, int year) 
        : title(t), author(a), publicationYear(year), isAvailable(true) {}

    void display() const {
        std::cout << "Title: " << title << ", Author: " << author 
                  << ", Year: " << publicationYear 
                  << ", Available: " << (isAvailable ? "Yes" : "No") << std::endl;
    }
};

class Library {
private:
    std::vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
        std::cout << "Book added: " << book.title << std::endl;
    }

    void removeBook(const std::string& title) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->title == title) {
                std::cout << "Removing book: " << it->title << std::endl;
                books.erase(it);
                return;
            }
        }
        std::cout << "Book not found." << std::endl;
    }

    void searchBook(const std::string& title) const {
        for (const auto& book : books) {
            if (book.title == title) {
                book.display();
                return;
            }
        }
        std::cout << "Book not found." << std::endl;
    }

    void checkoutBook(const std::string& title) {
        for (auto& book : books) {
            if (book.title == title) {
                if (book.isAvailable) {
                    book.isAvailable = false;
                    std::cout << "Book checked out: " << book.title << std::endl;
                } else {
                    std::cout << "Book is already checked out." << std::endl;
                }
                return;
            }
        }
        std::cout << "Book not found." << std::endl;
    }

    void returnBook(const std::string& title) {
        for (auto& book : books) {
            if (book.title == title) {
                if (!book.isAvailable) {
                    book.isAvailable = true;
                    std::cout << "Book returned: " << book.title << std::endl;
                } else {
                    std::cout << "Book was not checked out." << std::endl;
                }
                return;
            }
        }
        std::cout << "Book not found." << std::endl;
    }

    void displayInventory() const {
        std::cout << "\nLibrary Inventory:\n";
        for (const auto& book : books) {
            book.display();
        }
    }
};

int main() {
    Library library;
    int choice;
    std::string title, author;
    int year;

    while (true) {
        std::cout << "\nLibrary Management System:\n";
        std::cout << "1. Add a Book\n";
        std::cout << "2. Remove a Book\n";
        std::cout << "3. Search for a Book\n";
        std::cout << "4. Checkout a Book\n";
        std::cout << "5. Return a Book\n";
        std::cout << "6. Display Inventory\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                std::cout << "Enter publication year: ";
                std::cin >> year;
                library.addBook(Book(title, author, year));
                break;

            case 2:
                std::cout << "Enter title of the book to remove: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                library.removeBook(title);
                break;

            case 3:
                std::cout << "Enter title to search for: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                library.searchBook(title);
                break;

            case 4:
                std::cout << "Enter title of the book to checkout: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                library.checkoutBook(title);
                break;

            case 5:
                std::cout << "Enter title of the book to return: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                library.returnBook(title);
                break;

            case 6:
                library.displayInventory();
                break;

            case 7:
                std::cout << "Exiting the program." << std::endl;
                return 0;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}