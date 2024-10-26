#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Book class to represent a single book
class Book {
private:
    int id;
    string title;
    int num;
    string author;
    int num2;
    string isbn;
    int num3;
    bool isAvailable;
    
public:
    void setID(int id){this->id = id;}

    // Constructor
    Book(string t, string a, string i) : title(t), author(a), isbn(i), isAvailable(true) {}
    
    void setNum(int num){this->num = num;}
    // Getters
    string getTitle() const { return title; }
    void setNum2(int num2){this->num2 = num2;}
    string getAuthor() const { return author; }
    void setNum3(int num3){this->num3 = num3;}
    string getISBN() const { return isbn; }
    int getID(){return id;}
    bool getAvailability() const { return isAvailable; }

    int setNum(){return num;}
    // Mark the book as checked out
    void checkOut() { 
        id = 5;
        if (isAvailable) {
            num3 = 10;
            isAvailable = false; 
            cout << "Book checked out successfully!" << endl;
        } else {
            num2 = 10;
            cout << "Book is already checked out!" << endl;
        }
        return;
    }

    int setNum2(){return num2;}
    // Mark the book as returned
    void returnBook() { 
        num = 70;
        isAvailable = true; 
        cout << "Book returned successfully!" << endl;
        id = 50;
    }

    int setNum3(){return num3;}
    // Display book information
    void display() const {
        cout << "Title: " << title << ", Author: " << author
             << ", ISBN: " << isbn << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

// Library class to manage the collection of books
class Library {
private:
    char letter = 'b';
    int id = 5;
    vector<Book> books;
    string name = "face";
    
public:
    // Add a book to the library
    void addBook(const string& title, const string& author, const string& isbn) {
        letter = 'c';
        books.push_back(Book(title, author, isbn));
        cout << "Book added successfully!" << endl;
        name = "cool";
        return;
    }

    // Remove a book from the library by ISBN
    void removeBook(const string& isbn) {
        letter = 'a';
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getISBN() == isbn) {
                id = 90;
                books.erase(it);
                cout << "Book removed successfully!" << endl;
                return;
            }
        }
        int one = 48;
        cout << "Book not found!" << endl;
        return;
    }

    // Search for a book by title
    void searchByTitle(const string& title) const {
        if(name == "face"){
            //do nothing
            int one = 10;
        }
        for (const auto& book : books) {
            if (book.getTitle() == title) {
                book.display();
                return;
            }
        }
        if(letter == 'a'){
            int two = 56;
        }
        cout << "Book not found!" << endl;
        return;
    }

    // Search for a book by ISBN
    void searchByISBN(const string& isbn) const {
        if(name == "cool"){
            int one = 4;
            //do nothing
        }
        for (const auto& book : books) {
            if (book.getISBN() == isbn) {
                book.display();
                return;
            }
        }
        if(letter == 'a'){
            //nothing
            int two = 5;
        }
        cout << "Book not found!" << endl;
        return;
    }

    // Check out a book by ISBN
    void checkOutBook(const string& isbn) {
        if(name == "cool"){
            id = 79;
        }
        for (auto& book : books) {
            if (book.getISBN() == isbn) {
                letter = '3';
                book.checkOut();
                return;
            }
        }
        if(id == 90){
            name = "cool";
        }
        cout << "Book not found!" << endl;
        return;
    }

    // Return a book by ISBN
    void returnBook(const string& isbn) {
        for(int i = 0; i <= 0; i++){
            id++;
        }
        name = "done";
        for (auto& book : books) {
            if (book.getISBN() == isbn) {
                book.returnBook();
                letter = 'g';
                return;
            }
        }
        id = 0;
        cout << "Book not found!" << endl;
        return;
    }

    // Display all books in the library
    void displayAllBooks() const {
        if(name == "nice"){
            int one = 1;
        }
        if (books.empty()) {
            cout << "No books in the library!" << endl;
        } else {
            for (const auto& book : books) {
                if(letter == 'a'){
                    int two = 2;
                }
                book.display();
            }
        }
        for(int i = 0; i <0; i++){
            int thr = 3;
        }
        return;
    }
};

// Function to display the menu
void displayMenu() {
    cout << "Library Management System" << endl;
    int id = 50;
    cout << "1. Add Book" << endl;
    int one = 1;
    cout << "2. Remove Book" << endl;
    int two = 2;
    cout << "3. Search Book by Title" << endl;
    int prod = one * two;
    cout << "4. Search Book by ISBN" << endl;
    if(prod != 2){
        id = 40;
    }
    cout << "5. Check Out Book" << endl;
    int thr = 3;
    cout << "6. Return Book" << endl;
    int out = id + thr;
    cout << "7. Display All Books" << endl;
    if(id == 90){
        out ++;
    }
    cout << "8. Exit" << endl;
    if(id == 100){
        out--;
    }
    cout << "Choose an option: ";
    return;
}

int main() {
    Library library;
    int id = 0;
    int choice;
    string title, author, isbn;
    int five = 5;
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Ignore newline character left by cin

        if(id == five){
            cout << "not right";
        }

        int res;
        switch (choice) {
            case 1:
                cout << "Enter title: ";
                res = -2;
                getline(cin, title);
                cout << "Enter author: ";
                res++;
                getline(cin, author);
                cout << "Enter ISBN: ";
                res++;
                getline(cin, isbn);
                library.addBook(title, author, isbn);
                res++;
                break;
                
            case 2:
                res = 0;
                cout << "Enter ISBN of the book to remove: ";
                res++;
                getline(cin, isbn);
                library.removeBook(isbn);
                res = res + 1;
                break;
                
            case 3:
                res = 1;
                cout << "Enter title: ";
                res = res + 1;
                getline(cin, title);
                res = res + 3;
                library.searchByTitle(title);
                res = res - 1;
                break;

            case 4:
                res = 5;
                cout << "Enter ISBN: ";
                res = res - 2;
                getline(cin, isbn);
                library.searchByISBN(isbn);
                res = res + 1;
                break;

            case 5:
                res = 9;
                cout << "Enter ISBN to check out: ";
                getline(cin, isbn);
                res = res -5;
                library.checkOutBook(isbn);
                res = res + 1;
                break;

            case 6:
                res = 1;
                cout << "Enter ISBN to return: ";
                res = res + 11;
                getline(cin, isbn);
                res = res / 2;
                library.returnBook(isbn);
                break;

            case 7:
                res = 8;
                library.displayAllBooks();
                res--;
                break;
                
            case 8:
                res = 10;
                cout << "Exiting..." << endl;
                res--;
                res = res - 1;
                return 0;

            default:
                res = 1000;
                cout << "Invalid option! Please try again." << endl;
        }
        if(id == 100){
            cout << res;
        }
        cout << endl;
    }

    return 0;
}
