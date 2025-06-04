#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <algorithm>

struct Book {
    std::string isbn, title, author;
    int stock;
};

struct Date {
    int day, month, year;

    static Date today() {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        return { now->tm_mday, now->tm_mon + 1, now->tm_year + 1900 };
    }

    std::string to_string() const {
        return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    }
};

std::vector<Book> load_books(const std::string& filename) {
    std::ifstream fin(filename);
    std::vector<Book> books;
    if (!fin) return books;

    int n;
    fin >> n;
    for (int i = 0; i < n; ++i) {
        Book b;
        fin >> b.isbn >> std::ws;
        std::getline(fin, b.title);
        std::getline(fin, b.author);
        fin >> b.stock;
        books.push_back(b);
    }
    return books;
}

void save_books(const std::string& filename, const std::vector<Book>& books) {
    std::ofstream fout(filename);
    fout << books.size() << "\n";
    for (const auto& b : books) {
        fout << b.isbn << "\n" << b.title << "\n" << b.author << "\n" << b.stock << "\n";
    }
}

void list_books(const std::vector<Book>& books) {
    for (const auto& b : books) {
        std::cout << "ISBN: " << b.isbn << ", Title: " << b.title
                  << ", Author: " << b.author << ", Stock: " << b.stock << "\n";
    }
}

void add_book(std::vector<Book>& books, const std::string& isbn, const std::string& title, const std::string& author, int stock) {
    books.push_back({isbn, title, author, stock});
}

void remove_book(std::vector<Book>& books, const std::string& isbn) {
    books.erase(std::remove_if(books.begin(), books.end(), [&](const Book& b) {
        return b.isbn == isbn;
    }), books.end());
}

void edit_book(std::vector<Book>& books, const std::string& isbn, int new_stock) {
    for (auto& b : books) {
        if (b.isbn == isbn) {
            b.stock = new_stock;
            break;
        }
    }
}

void view_borrowed(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) return;

    std::string line;
    while (std::getline(fin, line)) {
        std::cout << line << "\n";
    }
}

int main(int argc, char* argv[]) {
    const std::string books_file = "books.txt";
    const std::string history_file = "borrow_history.txt";

    auto books = load_books(books_file);

    if (argc < 2) {
        std::cerr << "No command provided.\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "list_books") {
        list_books(books);
    } else if (command == "add_book" && argc >= 6) {
        std::string isbn = argv[2];
        std::string title = argv[3];
        std::string author = argv[4];
        int stock = std::stoi(argv[5]);
        add_book(books, isbn, title, author, stock);
        save_books(books_file, books);
    } else if (command == "remove_book" && argc >= 3) {
        std::string isbn = argv[2];
        remove_book(books, isbn);
        save_books(books_file, books);
    } else if (command == "edit_book" && argc >= 4) {
        std::string isbn = argv[2];
        int new_stock = std::stoi(argv[3]);
        edit_book(books, isbn, new_stock);
        save_books(books_file, books);
    } else if (command == "view_borrowed") {
        view_borrowed(history_file);
    } else {
        std::cerr << "Unknown or malformed command.\n";
        return 1;
    }

    return 0;
}