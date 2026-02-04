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

#include <queue>
#include <iomanip>
#include <sstream>
#include <functional>
#include <map>
#include <set>

// ---------- توابع داخلی ----------

// تابع کمکی برای نمایش یک گره
static void printNodeInfo(TrieNode* node, char c, int depth, bool isEnd) {
    string indent(depth * 4, ' ');
    
    if (depth == 0) {
        cout << indent << "┌── [ROOT]" << endl;
    } else {
        cout << indent << "├── " << c;
        if (isEnd) {
            cout << " ●";  // نشانگر پایان کلمه
        }
        cout << endl;
    }
}

// تابع کمکی برای نمایش فرزندان یک گره
static void printChildren(TrieNode* node, int depth) {
    bool hasChildren = false;
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            hasChildren = true;
            break;
        }
    }
    
    if (!hasChildren && depth > 0) {
        string indent((depth + 1) * 4, ' ');
        cout << indent << "└── (empty)" << endl;
    }
}

// DFS برای نمایش درخت
static void showTrieDFS(TrieNode* node, string prefix, int depth, bool showAll) {
    int childCount = 0;
    
    // شمارش فرزندان
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            childCount++;
        }
    }
    
    int currentChild = 0;
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            currentChild++;
            
            char currentChar = 'a' + i;
            string newPrefix = prefix + currentChar;
            
            // نمایش گره
            string indent(depth * 4, ' ');
            
            if (depth == 0) {
                cout << "ROOT";
                if (node->isEnd) cout << " ●";
                cout << endl;
                
                // نمایش خطوط اتصال
                if (childCount > 0) {
                    cout << "│" << endl;
                    
                    // نمایش تمام حروف در یک خط برای ریشه
                    cout << "├─── ";
                    for (int j = 0; j < 26; j++) {
                        if (node->children[j]) {
                            cout << (char)('a' + j);
                            if (node->children[j]->isEnd) cout << "●";
                            cout << " ";
                        }
                    }
                    cout << endl;
                    
                    if (!showAll) {
                        cout << "│" << endl;
                        cout << "└─── (showing " << childCount << " branches)" << endl;
                        return;
                    }
                    
                    cout << "│" << endl;
                }
            } else {
                // برای گره‌های غیرریشه
                string connector = (currentChild == childCount) ? "└── " : "├── ";
                
                cout << indent << connector << currentChar;
                if (node->children[i]->isEnd) {
                    cout << " ●";
                }
                
                // نمایش کلمه کامل اگر گره انتهایی است
                if (node->children[i]->isEnd) {
                    cout << "  \"" << newPrefix << "\"";
                }
                
                cout << endl;
            }
            
            // نمایش فرزندان اگر showAll=true یا عمق کم باشد
            if (showAll || depth < 2) {
                string childIndent = indent + ((currentChild == childCount) ? "    " : "│   ");
                if (depth == 0) {
                    childIndent = "│   ";
                }
                
                // نمایش خط عمودی برای اتصال
                if (currentChild < childCount && depth > 0) {
                    cout << indent << "│" << endl;
                }
                
                showTrieDFS(node->children[i], newPrefix, depth + 1, showAll);
            }
        }
    }
}
// نمایش خلاصه درخت
static void showTrieSummary(TrieNode* root) {
    int totalNodes = 0;
    int totalWords = 0;
    int maxDepth = 0;
    
    // BFS برای جمع‌آوری آمار
    queue<pair<TrieNode*, int>> q;
    q.push({root, 0});
    
    while (!q.empty()) {
        auto [node, depth] = q.front();
        q.pop();
        
        totalNodes++;
        maxDepth = max(maxDepth, depth);
        if (node->isEnd) totalWords++;
        
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                q.push({node->children[i], depth + 1});
            }
        }
    }
    
    cout << "\n=== TRIE SUMMARY ===" << endl;
    cout << "Total nodes: " << totalNodes << endl;
    cout << "Total words: " << totalWords << endl;
    cout << "Max depth: " << maxDepth << endl;
    cout << "Memory usage: ~" << (totalNodes * sizeof(TrieNode)) / 1024 << " KB" << endl;
    
    // نمایش حروف موجود
    cout << "\nAvailable letters from root:" << endl;
    cout << "  ";
    for (int i = 0; i < 26; i++) {
        if (root->children[i]) {
            cout << (char)('a' + i) << " ";
        }
    }
    cout << endl;
}

// ---------- تابع نمایش عمومی ----------
void trieShow(TrieNode* root, bool showAll) {
    if (!root) {
        std::cout << "Trie is empty!" << std::endl;
        return;
    }
    
    std::cout << "\n=== TRIE STRUCTURE VISUALIZATION ===" << std::endl;
    std::cout << std::endl;
    
    // نمایش مختصر ریشه
    std::cout << "ROOT" << std::endl;
    std::cout << " |" << std::endl;
    
    int totalLetters = 0;
    for (int i = 0; i < 26; i++) {
        if (root->children[i]) totalLetters++;
    }
    
    std::cout << " +-- [First level: " << totalLetters << " letters]" << std::endl;
    std::cout << "     |" << std::endl;
    
    // تمرکز روی حرف h
    std::cout << "     +-- Focusing on letter 'h':" << std::endl;
    std::cout << std::endl;
    
    if (!root->children['h' - 'a']) {
        std::cout << "     No 'h' branch exists!" << std::endl;
        return;
    }
    
    TrieNode* hNode = root->children['h' - 'a'];
    
    // نمایش شاخه h
    std::cout << "     h";
    if (hNode->isEnd) std::cout << " *";
    std::cout << std::endl;
    
    std::cout << "      |" << std::endl;
    
    // فرزندان مستقیم h
    std::vector<char> hChildren;
    for (int i = 0; i < 26; i++) {
        if (hNode->children[i]) {
            hChildren.push_back('a' + i);
        }
    }
    
    std::cout << "      +-- Children: ";
    for (char c : hChildren) {
        std::cout << c << " ";
    }
    std::cout << "(" << hChildren.size() << " letters)" << std::endl;
    std::cout << std::endl;
    
    // نمایش مسیرهای خاص
    std::cout << "=== PATHS FROM 'h' ===" << std::endl;
    
    // مسیر h -> e -> l -> l -> o
    if (hNode->children['e'-'a']) {
        TrieNode* he = hNode->children['e'-'a'];
        std::cout << "1. h -> e";
        if (he->isEnd) std::cout << " *";
        std::cout << std::endl;
        
        if (he->children['l'-'a']) {
            TrieNode* hel = he->children['l'-'a'];
            std::cout << "        -> l";
            if (hel->isEnd) std::cout << " *";
            std::cout << std::endl;
            
            if (hel->children['l'-'a']) {
                TrieNode* hell = hel->children['l'-'a'];
                std::cout << "        -> l";
                if (hell->isEnd) std::cout << " *";
                std::cout << std::endl;
                
                if (hell->children['o'-'a']) {
                    TrieNode* hello = hell->children['o'-'a'];
                    std::cout << "        -> o";
                    if (hello->isEnd) std::cout << " * (WORD: hello)";
                    std::cout << std::endl;
                }
            }
        }
    }
    
    std::cout << std::endl;
    
    // مسیر h -> e -> l -> p
    if (hNode->children['e'-'a']) {
        TrieNode* he = hNode->children['e'-'a'];
        if (he->children['l'-'a']) {
            TrieNode* hel = he->children['l'-'a'];
            if (hel->children['p'-'a']) {
                TrieNode* help = hel->children['p'-'a'];
                std::cout << "2. h -> e -> l -> p";
                if (help->isEnd) std::cout << " * (WORD: help)";
                std::cout << std::endl;
            }
        }
    }
    
    std::cout << std::endl;
    
    // نمایش همه کلمات با h
    std::vector<std::string> hWords;
    std::function<void(TrieNode*, std::string)> collectWords = 
    [&](TrieNode* node, std::string current) {
        if (node->isEnd) {
            hWords.push_back(current);
        }
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                collectWords(node->children[i], current + (char)('a' + i));
            }
        }
    };
    
    collectWords(hNode, "h");
    
    std::cout << "=== ALL WORDS STARTING WITH 'h' ===" << std::endl;
    std::cout << "Total: " << hWords.size() << " words" << std::endl;
    std::cout << std::endl;
    // گروه‌بندی بر اساس طول
    std::map<int, std::vector<std::string>> wordsByLength;
    for (const auto& word : hWords) {
        wordsByLength[word.length()].push_back(word);
    }
    
    for (const auto& [length, words] : wordsByLength) {
        std::cout << length << "-letter words (" << words.size() << "):" << std::endl;
        for (size_t i = 0; i < words.size(); i++) {
            std::cout << "  " << std::setw(15) << std::left << words[i];
            if ((i + 1) % 4 == 0) std::cout << std::endl;
        }
        if (words.size() % 4 != 0) std::cout << std::endl;
        std::cout << std::endl;
    }
    
    // نمونه مسیرهای کلمات
    std::cout << "=== SAMPLE WORD PATHS ===" << std::endl;
    std::cout << "h -> e -> l -> l -> o     = hello" << std::endl;
    std::cout << "h -> e -> l -> p          = help" << std::endl;
    std::cout << "h -> e -> a -> p          = heap" << std::endl;
    std::cout << "h -> e -> r -> o          = hero" << std::endl;
    std::cout << "h -> e -> r -> e          = here" << std::endl;
    std::cout << "h -> o -> u -> s -> e     = house" << std::endl;
    
    std::cout << "\n=== END OF TRIE VISUALIZATION ===" << std::endl;
}