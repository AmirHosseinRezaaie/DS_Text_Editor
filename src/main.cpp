#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <limits>

using namespace std;

string text;    

void print() {
    cout << text << endl;
}

bool isValidPosition(size_t pos) {
    return pos <= text.size();
}

bool isValidRange(size_t pos, size_t len) {
    return pos <= text.size() && pos + len <= text.size();
}

// Manual insert without using string::insert()
void manual_insert(size_t pos, const string& content) {
    string left = text.substr(0, pos);
    string right = text.substr(pos);
    text = left + content + right;
}

// Manual erase without using string::erase()
void manual_erase(size_t pos, size_t len) {
    string left = text.substr(0, pos);
    string right = text.substr(pos + len);
    text = left + right;
}

void doInsert(size_t pos, const string& content) {
    if (!isValidPosition(pos)) {
        cout << "Invalid position!" << endl;
        return;
    }
    // text.insert(pos, content);
    manual_insert(pos, content);
    print();
}

void doDelete(size_t pos, size_t len) {
    if (!isValidRange(pos, len)) {
        cout << "Invalid range!" << endl;
        return;
    }
    // text.erase(pos, len);
    manual_erase(pos, len);
    print();
}

int main() {

    string line;

    cout << "========= Simple Text Editor - Command Line =======" << endl;
    cout << "--------------- Available commands  ---------------" << endl;
    cout << "  print                   : Show current text" << endl;
    cout << "  insert <pos> <text>     : Insert text at position" << endl;
    cout << "  delete <pos> <length>   : Delete from position, length characters" << endl;
    cout << "  exit / quit             : Exit the program" << endl;
    cout << "  help                    : See this again" << endl;
    cout << "---------------------------------------------------" << endl;

    while (true) {
        cout << "> ";
        getline(cin, line);

        if (line.empty()) continue;

        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "exit" || command == "quit") {
            break;
        }
        else if (command == "print") {
            print();
        }
        else if (command == "insert") {
            size_t pos;
            string content;
            ss >> pos;
            getline(ss, content);    
            if (!content.empty() && content[0] == ' ') content = content.substr(1);
            doInsert(pos, content);
        }
        else if (command == "delete") {
            size_t pos, len;
            ss >> pos >> len;
            doDelete(pos, len);
        }
        else if (command == "help") {
            cout << "========= Simple Text Editor - Command Line =======" << endl;
            cout << "--------------- Available commands  ---------------" << endl;
            cout << "  print                  : Show current text" << endl;
            cout << "  insert <pos> <text>     : Insert text at position" << endl;
            cout << "  delete <pos> <length>   : Delete from position, length characters" << endl;
            cout << "  exit / quit             : Exit the program" << endl;
            cout << "  help                    : See this again" << endl;
            cout << "---------------------------------------------------" << endl;
        }
        else {
            cout << "Unknown command." << endl;
        }
    }

    return 0;
}