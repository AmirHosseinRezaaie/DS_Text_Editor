#include "trie.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

// ---------- توابع داخلی ----------

static TrieNode* createNode() {
    TrieNode* node = new TrieNode();
    node->isEnd = false;
    for (int i = 0; i < 26; i++) {
        node->children[i] = nullptr;
    }
    return node;
}

static void collectWordsDFS(TrieNode* node, string current, vector<string>& suggestions, int& count, int limit) {
    if (count >= limit) return;
    
    if (node->isEnd) {
        suggestions.push_back(current);
        count++;
    }
    
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            char nextChar = 'a' + i;
            collectWordsDFS(node->children[i], current + nextChar, suggestions, count, limit);
            if (count >= limit) return;
        }
    }
}

static TrieNode* findPrefixNode(TrieNode* root, const string& prefix) {
    TrieNode* curr = root;
    
    for (char c : prefix) {
        if (c < 'a' || c > 'z') return nullptr;
        
        int idx = c - 'a';
        if (!curr->children[idx]) {
            return nullptr;
        }
        curr = curr->children[idx];
    }
    return curr;
}

// ---------- توابع public ----------

TrieNode* createTrie() {
    return createNode();
}

void destroyTrie(TrieNode* root) {
    if (!root) return;
    
    for (int i = 0; i < 26; i++) {
        if (root->children[i]) {
            destroyTrie(root->children[i]);
        }
    }
    
    delete root;
}

void trieInsert(TrieNode* root, const string& word) {
    if (word.empty()) return;
    
    TrieNode* curr = root;
    
    for (char c : word) {
        if (c < 'a' || c > 'z') continue;
        
        int idx = c - 'a';
        
        if (!curr->children[idx]) {
            curr->children[idx] = createNode();
        }
        
        curr = curr->children[idx];
    }
    
    curr->isEnd = true;
}

vector<string> trieGetSuggestions(TrieNode* root, const string& prefix) {
    vector<string> suggestions;
    
    TrieNode* prefixNode = findPrefixNode(root, prefix);
    
    if (prefixNode) {
        int count = 0;
        const int MAX_SUGGESTIONS = 5; // فقط 5 پیشنهاد
        collectWordsDFS(prefixNode, prefix, suggestions, count, MAX_SUGGESTIONS);
    }
    
    return suggestions;
}

// دیکشنری کوتاه با کلمات پرکاربرد
void loadDefaultDictionary(TrieNode* root) {
    // کلمات پرکاربرد انگلیسی (تعداد محدود)
    const char* commonWords[] = {
        // کلمات پایه
        "the", "and", "you", "that", "for", "are", "with", "this",
        "have", "from", "but", "not", "what", "all", "were", "when",
        
        // کلمات مرتبط با ویرایشگر
        "text", "edit", "editor", "file", "save", "open", "close",
        "copy", "paste", "cut", "undo", "redo", "find", "replace",
        "word", "line", "page", "document", "format", "style",
        "font", "size", "bold", "italic", "underline", "color",
        
        // کلمات برنامه نویسی
        "code", "program", "function", "variable", "string", "int",
        "bool", "char", "array", "list", "stack", "queue", "tree",
        "graph", "class", "object", "method", "return", "if", "else",
        "for", "while", "loop", "break", "continue", "switch", "case",
        
        // کلمات عمومی پرکاربرد
        "hello", "world", "help", "here", "there", "where", "which",
        "their", "about", "would", "could", "should", "make", "like",
        "time", "people", "year", "day", "way", "thing", "work",
        "first", "good", "new", "old", "great", "little", "right",
        "back", "up", "down", "left", "more", "most", "some", "such",
        
        // کلمات فارسی (لاتین شده پرکاربرد)
        "salam", "khoda", "merci", "lotfan", "befarma", "chetori",
        "khoob", "bad", "bozorg", "koochak", "dir", "nazdik",
        "dast", "pa", "sar", "cheshm", "gush", "del", "ghalb"
    };
    
    int totalWords = sizeof(commonWords) / sizeof(commonWords[0]);
    for (int i = 0; i < totalWords; i++) {
        trieInsert(root, commonWords[i]);
    }
    
    cout << "Dictionary loaded with " << totalWords << " common words." << endl;
}