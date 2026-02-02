#include <iostream>
#include <string>
#include <stack>
#include <vector> // برای struct Action اگر لازم

struct Action {
    std::string type; // "insert" یا "delete" یا "paste"
    size_t pos;
    std::string content; // متن درج/حذف‌شده
    size_t length; // برای delete
};

int main() {
    std::string text_buffer; // متن اصلی
    std::stack<Action> undo_stack;
    std::stack<Action> redo_stack;
    std::string clipboard;

    std::string command;
    while (std::getline(std::cin, command)) { // خواندن دستور کامل
        // پارس دستور (در مراحل بعدی توضیح می‌دهم)
        if (command == "print") {
            std::cout << text_buffer << std::endl;
        }
        // ... بقیه عملیات
    }
    return 0;
}