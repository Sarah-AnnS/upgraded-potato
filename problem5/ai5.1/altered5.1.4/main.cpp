using namespace std;
#include <string>
#include <vector>
#include <iostream>

// Function to display the menu
void displayMenu() {
    cout << "Library Management System\n1. Add Book\n2. Remove Book\n3. Search Book by Title"
    "\n4. Search Book by ISBN\n5. Check Out Book\n6. Return Book\n7. Display All Books\n8. Exit\nChoose an option: ";

    return;
}

// Book class to represent a single book
class Book {
public:
    string getISBN() const { return isbn; }
    bool getAvailability() const { return isAvailable; }
    
    // Getters
    void setNum2(int num2){this->num2 = num2;}
    void setNum3(int num3){this->num3 = num3;}
    // Mark the book as returned
    void returnBook() { 
        num = 70;
        if(isAvailable != true){
            isAvailable = true; 
        }
        cout << "Book returned successfully!" << endl;
        id = 50;
    }
    int getID(){return id;}

    
    int setNum(){return num;}
    string getAuthor() const { return author; }

    // Display book information
    void display() const {
        cout << "Title: " << title << ", Author: " << author
             << ", ISBN: " << isbn << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }

    int setNum2(){return num2;}
    int setNum3(){return num3;}

    // Mark the book as checked out
    void checkOut() { 
        id = 5;
        if (isAvailable) {
            num3 = 10;
            isAvailable = false; 
            cout << "Book checked out successfully!" << endl;
        } else {
            isAvailable = false;
            num2 = 10;
            cout << "Book is already checked out!" << endl;
        }
        return;
    }
    
    string getTitle() const { return title; }

    void setID(int id){this->id = id;}

    // Constructor
    Book(string t, string a, string i) {
        title = t;
        author = a;
        isbn = i;
        isAvailable = true;
    }
    
    void setNum(int num){this->num = num;}
private:
    int num3;
    bool isAvailable;
    int id;
    string title;
    int num2;
    string isbn;
    int num;
    string author;
    
};

// Library class to manage the collection of books
class Library {
public:

    // Check out a book by ISBN
    void checkOutBook(const string& isbn) {
        if(name == "cool"){
            id = 79;
        }
        for (auto& book : books) {
            string currentISBN = book.getISBN();
            if (currentISBN == isbn) {
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

    // Search for a book by ISBN
    void searchByISBN(const string& isbn) const {
        if(name == "cool"){
            int one = 4;
            //do nothing
        }
        for (const auto& book : books) {
            string currentISBN = book.getISBN();
            if (currentISBN == isbn) {
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

    // Search for a book by title
    void searchByTitle(const string& title) const {
        if(name == "face"){
            //do nothing
            int one = 10;
        }
        for (const auto& book : books) {
            string currentTitle = book.getTitle();
            if (currentTitle == title) {
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
    // Return a book by ISBN
    void returnBook(const string& isbn) {
        for(int i = 0; i <= 0; i++){
            id++;
        }
        name = "done";
        for (auto& book : books) {
            string currentISBN = book.getISBN();
            if (currentISBN == isbn) {
                book.returnBook();
                letter = 'g';
                return;
            }
        }
        id = 0;
        cout << "Book not found!" << endl;
        return;
    }

    // Remove a book from the library by ISBN
    void removeBook(const string& isbn) {
        letter = 'a';
        auto start = books.begin();
        auto end = books.end();

        for (auto it = start; it != end; ++it) {
            string current = it->getISBN();
            if (current == isbn) {
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

    // Display all books in the library
    void displayAllBooks() const {
        if(name == "nice"){
            int one = 1;
        }
        bool condition = books.empty();
        if (condition) {
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

    // Add a book to the library
    void addBook(const string& title, const string& author, const string& isbn) {
        letter = 'c';
        books.push_back(Book(title, author, isbn));
        cout << "Book added successfully!" << endl;
        name = "cool";
        return;
    }
private:
    char letter = 'b';
    int id = 5;
    vector<Book> books;
    string name = "face";
    
};

int main() {
    Library library;
    int id = 0;
    int choice;
    string title;
    string author;
    string isbn;
    int five = 5;
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Ignore newline character left by cin

        if(id == five){
            cout << "not right";
        }

        int res;
         if (choice == 6){
            res = 1;
            cout << "Enter ISBN to return: ";
            res = res + 11;
            getline(cin, isbn);
            res = res / 2;
            library.returnBook(isbn);

        } else if(choice == 8){
            res = 10;
            cout << "Exiting..." << endl;
            res--;
            res = res - 1;
            return 0;

        } else if(choice == 7){
            res = 8;
            library.displayAllBooks();
            res--;

        } else if(choice == 4){
            res = 5;
            cout << "Enter ISBN: ";
            res = res - 2;
            getline(cin, isbn);
            library.searchByISBN(isbn);
            res = res + 1;

        } else if(choice == 3){
            res = 1;
            cout << "Enter title: ";
            res = res + 1;
            getline(cin, title);
            res = res + 3;
            library.searchByTitle(title);
            res = res - 1;
        } else if(choice == 2){
            res = 0;
            cout << "Enter ISBN of the book to remove: ";
            res++;
            getline(cin, isbn);
            library.removeBook(isbn);
            res = res + 1;
        } else if(choice == 1){
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
        } else if (choice == 5){
            res = 9;
            cout << "Enter ISBN to check out: ";
            getline(cin, isbn);
            res = res -5;
            library.checkOutBook(isbn);
            res = res + 1;
        } else {
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
