#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include "trie.h"

using namespace std;

/* ---------- Data Structures ---------- */

struct Action {
    string type;
    size_t position;
    vector<char> content;
};

vector<char> text;
stack<Action> undoStack;
stack<Action> redoStack;
vector<char> clipboard;

/* ---------- Utility ---------- */

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

void showHelp() {
    cout << "========= Simple Text Editor - Command Line =======" << endl;
    cout << "--------------- Available commands  ---------------" << endl;
    cout << "  print                   : Show current text" << endl;
    cout << "  insert <pos> <text>     : Insert text at position" << endl;
    cout << "  delete <pos> <length>   : Delete from position, length characters" << endl;
    cout << "  undo                    : Undo last action" << endl;
    cout << "  redo                    : Redo last undone action" << endl;
    cout << "  copy <pos> <length>     : Copy text to clipboard" << endl;
    cout << "  paste <pos>             : Paste clipboard content at position" << endl;
    cout << "  auto <prefix>           : Suggestion for complete"<< endl;
    cout << "  showtrie [-a]           : Display Trie structure" << endl;
    cout << "    -a or --all           : Show full tree (verbose)" << endl;
    cout << "  exit / quit             : Exit the program" << endl;
    cout << "  help                    : See this again" << endl;
    cout << "---------------------------------------------------" << endl;
}

/* ---------- Manual Vector Operations ---------- */

void manual_insert(size_t pos, const vector<char>& content) {
    size_t oldSize = text.size();
    size_t len = content.size();

    text.resize(oldSize + len);

    for (int i = oldSize - 1; i >= (int)pos; i--) {
        text[i + len] = text[i];
    }

    for (size_t i = 0; i < len; i++) {
        text[pos + i] = content[i];
    }
}

void manual_erase(size_t pos, size_t len) {
    size_t size = text.size();

    for (size_t i = pos + len; i < size; i++) {
        text[i - len] = text[i];
    }

    text.resize(size - len);
}

/* ---- Global Trie instance ---- */

   TrieNode* trieRoot = nullptr;

/* ---------- Commands ---------- */

void doInsert(size_t pos, const string& input) {
    if (!isValidPosition(pos)) {
        cout << "Invalid position!" << endl;
        return;
    }

    vector<char> content;
    for (char c : input)
        content.push_back(c);

    Action act;
    act.type = "insert";
    act.position = pos;
    act.content = content;

    undoStack.push(act);
    redoStack = stack<Action>();

    manual_insert(pos, content);
    print();
}

void doDelete(size_t pos, size_t len) {
    if (!isValidRange(pos, len)) {
        cout << "Invalid range!" << endl;
        return;
    }

    vector<char> removed;
    for (size_t i = 0; i < len; i++) {
        removed.push_back(text[pos + i]);
    }

    Action act;
    act.type = "delete";
    act.position = pos;
    act.content = removed;

    undoStack.push(act);
    redoStack = stack<Action>();

    manual_erase(pos, len);
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
    }
    else if (act.type == "delete") {
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
    }
    else if (act.type == "delete") {
        manual_erase(act.position, act.content.size());
    }

    print();
}

void doCopy(size_t pos, size_t len) {
    if (!isValidRange(pos, len)) {
        cout << "Invalid range!" << endl;
        return;
    }

    clipboard.clear();
    for (size_t i = 0; i < len; i++) {
        clipboard.push_back(text[pos + i]);
    }

    cout << "Copied: \"";
    for (char c : clipboard) cout << c;
    cout << "\"" << endl;
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

/* ---------- Main ---------- */

int main() {
    // ایجاد و راه‌اندازی Trie
    trieRoot = createTrie();
    loadDefaultDictionary(trieRoot);

    string line;

    showHelp();

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
        else if (command == "help") {
            showHelp();
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
        else if (command == "undo") {
            doUndo();
        }
        else if (command == "redo") {
            doRedo();
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
