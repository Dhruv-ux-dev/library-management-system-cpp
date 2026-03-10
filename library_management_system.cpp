#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book() {}

    Book(int i, string t, string a, bool iss) {
        id = i;
        title = t;
        author = a;
        issued = iss;
    }
};

class Library {
private:
    vector<Book> books;

public:

    void loadFromFile() {
        ifstream file("library.txt");

        if (!file)
            return;

        Book b;
        while (file >> b.id >> b.title >> b.author >> b.issued) {
            books.push_back(b);
        }

        file.close();
    }

    void saveToFile() {
        ofstream file("library.txt");

        for (auto &b : books) {
            file << b.id << " "
                 << b.title << " "
                 << b.author << " "
                 << b.issued << endl;
        }

        file.close();
    }

    void addBook() {

        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;

        cout << "Enter Title: ";
        cin >> title;

        cout << "Enter Author: ";
        cin >> author;

        books.push_back(Book(id, title, author, false));

        saveToFile();

        cout << "Book Added Successfully\n";
    }

    void displayBooks() {

        cout << "\nLibrary Books:\n";

        for (auto &b : books) {

            cout << "ID: " << b.id << endl;
            cout << "Title: " << b.title << endl;
            cout << "Author: " << b.author << endl;

            if (b.issued)
                cout << "Status: Issued\n";
            else
                cout << "Status: Available\n";

            cout << "------------------\n";
        }
    }

    void searchBook() {

        int id;
        cout << "Enter Book ID: ";
        cin >> id;

        for (auto &b : books) {

            if (b.id == id) {

                cout << "Book Found\n";
                cout << "Title: " << b.title << endl;
                cout << "Author: " << b.author << endl;

                return;
            }
        }

        cout << "Book Not Found\n";
    }

    void deleteBook() {

        int id;
        cout << "Enter Book ID to delete: ";
        cin >> id;

        for (int i = 0; i < books.size(); i++) {

            if (books[i].id == id) {

                books.erase(books.begin() + i);

                saveToFile();

                cout << "Book Deleted\n";
                return;
            }
        }

        cout << "Book Not Found\n";
    }

    void issueBook() {

        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;

        for (auto &b : books) {

            if (b.id == id) {

                if (b.issued) {
                    cout << "Book already issued\n";
                    return;
                }

                b.issued = true;

                saveToFile();

                cout << "Book Issued\n";
                return;
            }
        }

        cout << "Book Not Found\n";
    }

    void returnBook() {

        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        for (auto &b : books) {

            if (b.id == id) {

                if (!b.issued) {
                    cout << "Book was not issued\n";
                    return;
                }

                b.issued = false;

                saveToFile();

                cout << "Book Returned\n";
                return;
            }
        }

        cout << "Book Not Found\n";
    }
};

int main() {

    Library library;

    library.loadFromFile();

    int choice;

    while (true) {

        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                library.addBook();
                break;

            case 2:
                library.displayBooks();
                break;

            case 3:
                library.searchBook();
                break;

            case 4:
                library.deleteBook();
                break;

            case 5:
                library.issueBook();
                break;

            case 6:
                library.returnBook();
                break;

            case 7:
                return 0;

            default:
                cout << "Invalid choice\n";
        }
    }
}
