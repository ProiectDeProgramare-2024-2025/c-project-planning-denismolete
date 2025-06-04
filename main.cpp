
#include <iostream>
#include <cstdlib>

void show_menu() {
    std::cout << "===== Library System Menu =====\n";
    std::cout << "1. Manage Books (App 1)\n";
    std::cout << "2. Borrow System (App 2)\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter choice: ";
}

int main() {
    int choice;
    while (true) {
        show_menu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Running App 1...\n";
                system("./app1 list_books");
                break;
            case 2:
                std::cout << "Running App 2...\n";
                system("./app2 view_cart");
                break;
            case 0:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
