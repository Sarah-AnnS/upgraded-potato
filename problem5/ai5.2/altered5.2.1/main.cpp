#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <string>

class Book {
public:
    std::string title;
    int id;
    std::string author;
    char type;
    int publicationYear;
    bool isAvailable;

    char getType(){return type;}

    Book(std::string t, std::string a, int year) 
        : title(t), author(a), publicationYear(year), isAvailable(true) {}

    int getId(){return id;}

    void display() const {
        std::cout << "Title: " << title << ", Author: " << author 
                  << ", Year: " << publicationYear 
                  << ", Available: " << (isAvailable ? "Yes" : "No") << std::endl;
    }

    void setId(int id){this->id = id;}
};

class Library {
private:
    int id;
    std::vector<Book> books;
    char type;

public:
    void addBook(const Book& book) {
        books.push_back(book);
        std::cout << "Book added: " << book.title << std::endl;
    }

    int getId(){return id;}

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

    char getType(){return type;}

    void searchBook(const std::string& title) const {
        for (const auto& book : books) {
            if (book.title == title) {
                book.display();
                return;
            }
        }
        std::cout << "Book not found." << std::endl;
    }

    void setId(int id){this->id = id;}

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

    void setType(char type){this->type = type;}

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

    void function(int arg){return;}

    void displayInventory() const {
        std::cout << "\nLibrary Inventory:\n";
        for (const auto& book : books) {
            book.display();
        }
    }
};

int main() {
    Library library;
    int index =5;
    int choice;
    std::string title, author;
    char type = 'a';
    int year;
    int option = 0;

    while (true) {
        std::cout << "\nLibrary Management System:\n";
        index++;
        std::cout << "1. Add a Book\n";
        index++;
        std::cout << "2. Remove a Book\n";
        index++;
        std::cout << "3. Search for a Book\n";
        index++;
        std::cout << "4. Checkout a Book\n";
        index++;
        std::cout << "5. Return a Book\n";
        index++;
        std::cout << "6. Display Inventory\n";
        index++;
        std::cout << "7. Exit\n";
        index++;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter title: ";
                option = 10;
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                index = 50;
                std::getline(std::cin, author);
                std::cout << "Enter publication year: ";
                if(index == 0){option = 1;}
                std::cin >> year;
                library.addBook(Book(title, author, year));
                break;

            case 2:
                std::cout << "Enter title of the book to remove: ";
                option = 20;
                std::cin.ignore();
                std::getline(std::cin, title);
                index = 30;
                library.removeBook(title);
                break;

            case 3:
                std::cout << "Enter title to search for: ";
                option = 30;
                std::cin.ignore();
                std::getline(std::cin, title);
                index = 20;
                library.searchBook(title);
                break;

            case 4:
                std::cout << "Enter title of the book to checkout: ";
                option = 40;
                std::cin.ignore();
                std::getline(std::cin, title);
                index = 66;
                library.checkoutBook(title);
                break;

            case 5:
                std::cout << "Enter title of the book to return: ";
                option = 50;
                std::cin.ignore();
                std::getline(std::cin, title);
                index = 80;
                library.returnBook(title);
                break;

            case 6:
                library.displayInventory();
                option = 60;
                break;

            case 7:
                std::cout << "Exiting the program." << std::endl;
                option = 70;
                return 0;

            default:
                option = 80;
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
