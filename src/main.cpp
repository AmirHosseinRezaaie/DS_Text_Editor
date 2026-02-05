#include <iostream>
#include <string>
#include <deque>  
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
deque<Action> undoHistory;    // به جای stack
deque<Action> redoHistory;    // به جای stack
const size_t MAX_HISTORY = 3;  // حداکثر 3 عمل ذخیره شود

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
    cout << "  history                 : Show undo/redo history status" << endl;
    cout << "  help                    : Show again this help menu" << endl;
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

    // اضافه کردن به تاریخچه
    undoHistory.push_back(act);
    
    // مدیریت محدودیت تاریخچه
    if (undoHistory.size() > MAX_HISTORY) {
        cout << "[History] Oldest action removed (limit: " 
             << MAX_HISTORY << " operations)" << endl;
        undoHistory.pop_front();  // حذف قدیمی‌ترین عمل
    }
    
    // پاک کردن redo هنگام عمل جدید
    redoHistory.clear();

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

    // اضافه کردن به تاریخچه
    undoHistory.push_back(act);
    
    // مدیریت محدودیت تاریخچه
    if (undoHistory.size() > MAX_HISTORY) {
        cout << "[History] Oldest action removed (limit: " 
             << MAX_HISTORY << " operations)" << endl;
        undoHistory.pop_front();  // حذف قدیمی‌ترین عمل
    }
    
    // پاک کردن redo هنگام عمل جدید
    redoHistory.clear();

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

    // اضافه کردن به تاریخچه
    undoHistory.push_back(act);
    
    // مدیریت محدودیت تاریخچه
    if (undoHistory.size() > MAX_HISTORY) {
        cout << "[History] Oldest action removed (limit: " 
             << MAX_HISTORY << " operations)" << endl;
        undoHistory.pop_front();  // حذف قدیمی‌ترین عمل
    }
    
    // پاک کردن redo هنگام عمل جدید
    redoHistory.clear();

    manual_insert(pos, clipboard);
    print();
}

void doUndo() {
    if (undoHistory.empty()) {
        cout << "Nothing to undo." << endl;
        return;
    }

    Action act = undoHistory.back();  // آخرین عمل
    undoHistory.pop_back();
    redoHistory.push_back(act);
    
    // محدودیت redo هم اعمال کنیم
    if (redoHistory.size() > MAX_HISTORY) {
        redoHistory.pop_front();
    }

    if (act.type == "insert" || act.type == "paste") {
        manual_erase(act.position, act.content.size());
    } else if (act.type == "delete") {
        manual_insert(act.position, act.content);
    }

    cout << "[Undo] " << act.type << " operation undone" << endl;
    print();
}

void doRedo() {
    if (redoHistory.empty()) {
        cout << "Nothing to redo." << endl;
        return;
    }

    Action act = redoHistory.back();  // آخرین عمل
    redoHistory.pop_back();
    undoHistory.push_back(act);
    
    // محدودیت undo هم اعمال کنیم
    if (undoHistory.size() > MAX_HISTORY) {
        cout << "[History] Oldest action removed (limit: " 
             << MAX_HISTORY << " operations)" << endl;
        undoHistory.pop_front();
    }

    if (act.type == "insert" || act.type == "paste") {
        manual_insert(act.position, act.content);
    } else if (act.type == "delete") {
        manual_erase(act.position, act.content.size());
    }

    cout << "[Redo] " << act.type << " operation redone" << endl;
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

void showHistoryStatus() {
    cout << "\n=== HISTORY STATUS ===" << endl;
    cout << "Undo stack: " << undoHistory.size() << "/" << MAX_HISTORY << " operations" << endl;
    cout << "Redo stack: " << redoHistory.size() << "/" << MAX_HISTORY << " operations" << endl;
    
    if (!undoHistory.empty()) {
        cout << "\nUndo history (oldest to newest):" << endl;
        int index = 1;
        for (const auto& act : undoHistory) {
            cout << "  " << index << ". " << act.type;
            if (act.type == "insert") {
                cout << " at " << act.position << " (+" << act.content.length() << " chars)";
            } else if (act.type == "delete") {
                cout << " at " << act.position << " (-" << act.content.length() << " chars)";
            } else if (act.type == "paste") {
                cout << " at " << act.position << " (+" << act.content.length() << " chars from clipboard)";
            }
            cout << endl;
            index++;
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
        else if (command == "history") {
            showHistoryStatus();
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