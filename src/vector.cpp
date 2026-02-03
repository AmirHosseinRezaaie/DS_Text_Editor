#include <iostream>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

struct Action {
    string type;
    size_t position;
    vector<char> content;
    size_t length;
};

vector<char> text;

void print() {
    for (char c : text)
        cout << c;
    cout << endl;
}

bool isValidPosition(size_t pos) {
    return pos <= text.size();
}

bool isValidRange(size_t pos, size_t len) {
    return pos <= text.size() && pos + len <= text.size();
}

// Manual insert without vector::insert
void manual_insert(size_t pos, const vector<char>& content) {
    size_t oldSize = text.size();
    size_t len = content.size();

    // resize vector
    text.resize(oldSize + len);

    // shift right
    for (int i = oldSize - 1; i >= (int)pos; i--) {
        text[i + len] = text[i];
    }

    // copy new content
    for (size_t i = 0; i < len; i++) {
        text[pos + i] = content[i];
    }
}

// Manual erase without vector::erase
void manual_erase(size_t pos, size_t len) {
    size_t size = text.size();

    // shift left
    for (size_t i = pos + len; i < size; i++) {
        text[i - len] = text[i];
    }

    text.resize(size - len);
}

void doInsert(size_t pos, const string& input) {
    if (!isValidPosition(pos)) {
        cout << "Invalid position!" << endl;
        return;
    }

    vector<char> content;
    for (char c : input)
        content.push_back(c);

    manual_insert(pos, content);
    print();
}

void doDelete(size_t pos, size_t len) {
    if (!isValidRange(pos, len)) {
        cout << "Invalid range!" << endl;
        return;
    }

    manual_erase(pos, len);
    print();
}

int main() {
    
    string line;

    cout << "========= Vector Text Editor - Insert/Delete =======" << endl;
    cout << "Commands:" << endl;
    cout << "  print" << endl;
    cout << "  insert <pos> <text>" << endl;
    cout << "  delete <pos> <length>" << endl;
    cout << "  exit" << endl;
    cout << "---------------------------------------------------" << endl;

    while (true) {
        cout << "> ";
        getline(cin, line);

        if (line.empty()) continue;

        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "exit") {
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
            if (!content.empty() && content[0] == ' ')
                content = content.substr(1);

            doInsert(pos, content);
        }
        else if (command == "delete") {
            size_t pos, len;
            ss >> pos >> len;
            doDelete(pos, len);
        }
        else {
            cout << "Unknown command." << endl;
        }
    }

    return 0;
}
