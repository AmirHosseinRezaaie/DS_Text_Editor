#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include "trie.h"

using namespace std;

/* =======================
   Undo / Redo structures
   ======================= */

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

/* =======================
   Editor utility functions
   ======================= */

void print() {
    if (text.empty()) {
        cout << "(empty)" << endl;
    } else {
        cout << "Text: \"" << text << "\"" << endl;
    }
}

bool isValidPosition(size_t pos) {
    return pos <= text.size();
}

bool isValidRange(size_t pos, size_t len) {
    return pos <= text.size() && pos + len <= text.size();
}

void showHelp() {
    cout << "========= Simple Text Editor - Command Line =======" << endl;
    cout << "--------------- Available commands  ---------------" << endl;
    cout << "  print                   : Show current text" << endl;
    cout << "  insert <pos> <text>     : Insert text at position" << endl;
    cout << "  delete <pos> <length>   : Delete from position" << endl;
    cout << "  copy <pos> <length>     : Copy text" << endl;
    cout << "  paste <pos>             : Paste clipboard" << endl;
    cout << "  undo / redo             : Undo / Redo" << endl;
    cout << "  auto <prefix>           : Word suggestion" << endl;
    cout << "  showtrie [-a]           : Display Trie structure" << endl;
    cout << "    -a or --all           : Show full tree (verbose)" << endl;
    cout << "  exit / quit             : Exit" << endl;
    cout << "---------------------------------------------------" << endl;
}

// Manual insert (بدون string::insert)
void manual_insert(size_t pos, const string& content) {
    string left = text.substr(0, pos);
    string right = text.substr(pos);
    text = left + content + right;
}

// Manual erase (بدون string::erase)
void manual_erase(size_t pos, size_t len) {
    string left = text.substr(0, pos);
    string right = text.substr(pos + len);
    text = left + right;
}

/* =======================
   Global Trie instance
   ======================= */
TrieNode* trieRoot = nullptr;

/* =======================
   Editor commands
   ======================= */

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

    manual_insert(pos, content);

    // اضافه کردن کلمات جدید به دیکشنری
    stringstream ss(content);
    string word;
    while (ss >> word) {
        // فقط حروف کوچک اضافه کن
        string cleanWord;
        for (char c : word) {
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
            if (c >= 'a' && c <= 'z') cleanWord += c;
        }
        if (!cleanWord.empty()) {
            trieInsert(trieRoot, cleanWord);
        }
    }

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

    manual_erase(pos, len);
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

    manual_insert(pos, clipboard);
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
        manual_erase(act.position, act.content.size());
    } else if (act.type == "delete") {
        manual_insert(act.position, act.content);
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
        manual_insert(act.position, act.content);
    } else if (act.type == "delete") {
        manual_erase(act.position, act.content.size());
    }

    print();
}

void doAutoComplete(const string& prefix) {
    if (prefix.empty()) {
        cout << "Please enter a prefix." << endl;
        return;
    }
    
    vector<string> suggestions = trieGetSuggestions(trieRoot, prefix);
    
    if (suggestions.empty()) {
        cout << "No suggestions for \"" << prefix << "\"" << endl;
    } else {
        cout << "Suggestions:" << endl;
        for (const string& word : suggestions) {
            cout << "  " << word << endl;
        }
    }
}

/* =======================
   Main
   ======================= */

int main() {
    // ایجاد و راه‌اندازی Trie
    trieRoot = createTrie();
    loadDefaultDictionary(trieRoot);

    showHelp();
    
    string line;

    while (true) {
        cout << "> ";
        getline(cin, line);
        if (line.empty()) continue;

        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "exit" || command == "quit") break;
        else if (command == "print") print();
        else if (command == "insert") {
            size_t pos;
            string content;
            if (!(ss >> pos)) {
                cout << "Invalid position!" << endl;
                continue;
            }
            getline(ss, content);
            if (!content.empty() && content[0] == ' ')
                content = content.substr(1);
            doInsert(pos, content);
        }
        else if (command == "delete") {
            size_t pos, len;
            if (!(ss >> pos >> len)) {
                cout << "Invalid parameters!" << endl;
                continue;
            }
            doDelete(pos, len);
        }
        else if (command == "copy") {
            size_t pos, len;
            if (!(ss >> pos >> len)) {
                cout << "Invalid parameters!" << endl;
                continue;
            }
            doCopy(pos, len);
        }
        else if (command == "paste") {
            size_t pos;
            if (!(ss >> pos)) {
                cout << "Invalid position!" << endl;
                continue;
            }
            doPaste(pos);
        }
        else if (command == "undo") doUndo();
        else if (command == "redo") doRedo();
        else if (command == "auto") {
            string prefix;
            if (!(ss >> prefix)) {
                cout << "Enter prefix!" << endl;
                continue;
            }
            doAutoComplete(prefix);
        }
        else if (command == "showtrie") {
            bool showAll = false;
            string option;
            if (ss >> option && (option == "-a" || option == "--all")) {
                showAll = true;
            }
            trieShow(trieRoot, showAll);
        }else if (command == "showtrie") {
            bool showAll = false;
            string option;
            if (ss >> option && (option == "-a" || option == "--all")) {
                showAll = true;
            }
            trieShow(trieRoot, showAll);
        }
        else if (command == "help") {
            showHelp();
        }
        else {
            cout << "Unknown command." << endl;
        }
    }

    // پاکسازی حافظه
    destroyTrie(trieRoot);
    
    cout << "Goodbye!" << endl;
    return 0;
}