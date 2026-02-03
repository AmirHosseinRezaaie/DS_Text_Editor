#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <limits>

using namespace std;

struct Action {
    string type; 
    size_t position;
    string content;
    size_t length;      
};

string text;  
stack<Action> undoStack;
stack<Action> redoStack;
string clipboard;       

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

    Action act;
    act.type = "insert";
    act.position = pos;
    act.content = content;
    undoStack.push(act);
    redoStack = stack<Action>();

    text.insert(pos, content);
    print();
}

void doDelete(size_t pos, size_t len) {
    if (!isValidRange(pos, len)) {
        cout << "Invalid range!" << endl;
        return;
    }

    string deleted = text.substr(pos, len);

    Action act;
    act.type = "delete";
    act.position = pos;
    act.content = deleted;
    act.length = len;
    undoStack.push(act);
    redoStack = stack<Action>();

    text.erase(pos, len);
    print();
}

void doCopy(size_t pos, size_t len) {
    if (!isValidRange(pos, len)) {
        cout << "Invalid range!" << endl;
        return;
    }
    clipboard = text.substr(pos, len);
    cout << "Copied: \"" << clipboard << "\"" << endl;
}

void doPaste(size_t pos) {
    if (clipboard.empty()) {
        cout << "Clipboard is empty!" << endl;
        return;
    }
    if (!isValidPosition(pos)) {
        cout << "Invalid position!" << endl;
        return;
    }

    Action act;
    act.type = "paste";
    act.position = pos;
    act.content = clipboard;
    undoStack.push(act);
    redoStack = stack<Action>();

    text.insert(pos, clipboard);
    print();
}

void doUndo() {
    if (undoStack.empty()) {
        cout << "Nothing to undo." << endl;
        return;
    }

    Action act = undoStack.top();
    undoStack.pop();
    redoStack.push(act);

    if (act.type == "insert" || act.type == "paste") {
        text.erase(act.position, act.content.size());
    } else if (act.type == "delete") {
        text.insert(act.position, act.content);
    }

    print();
}

void doRedo() {
    if (redoStack.empty()) {
        cout << "Nothing to redo." << endl;
        return;
    }

    Action act = redoStack.top();
    redoStack.pop();
    undoStack.push(act);

    if (act.type == "insert" || act.type == "paste") {
        text.insert(act.position, act.content);
    } else if (act.type == "delete") {
        text.erase(act.position, act.content.size());
    }

    print();
}

int main() {
    string line;

    cout << "========= Simple Text Editor - Command Line =======" << endl;
    cout << "--------------- Available commands  ---------------" << endl;
    cout << "  print                   : Show current text" << endl;
    cout << "  insert <pos> <text>     : Insert text at position" << endl;
    cout << "  delete <pos> <length>   : Delete from position, length characters" << endl;
    cout << "  copy <pos> <length>     : Copy text to clipboard" << endl;
    cout << "  paste <pos>             : Paste clipboard content at position" << endl;
    cout << "  undo                    : Undo last action" << endl;
    cout << "  redo                    : Redo last undone action" << endl;
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
        else if (command == "copy") {
            size_t pos, len;
            ss >> pos >> len;
            doCopy(pos, len);
        }
        else if (command == "paste") {
            size_t pos;
            ss >> pos;
            doPaste(pos);
        }
        else if (command == "undo") {
            doUndo();
        }
        else if (command == "redo") {
            doRedo();
        }
        else if (command == "help") {
            cout << "========= Simple Text Editor - Command Line =======" << endl;
            cout << "--------------- Available commands  ---------------" << endl;
            cout << "  print                  : Show current text" << endl;
            cout << "  insert <pos> <text>     : Insert text at position" << endl;
            cout << "  delete <pos> <length>   : Delete from position, length characters" << endl;
            cout << "  copy <pos> <length>     : Copy text to clipboard" << endl;
            cout << "  paste <pos>             : Paste clipboard content at position" << endl;
            cout << "  undo                    : Undo last action" << endl;
            cout << "  redo                    : Redo last undone action" << endl;
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