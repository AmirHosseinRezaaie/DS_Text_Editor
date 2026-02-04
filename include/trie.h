#ifndef TRIE_SUGGESTIONS_H
#define TRIE_SUGGESTIONS_H

#include <string>
#include <vector>

struct TrieNode {
    bool isEnd;
    TrieNode* children[26];
};

// فقط توابع اصلی
TrieNode* createTrie();
void destroyTrie(TrieNode* root);
void trieInsert(TrieNode* root, const std::string& word);
std::vector<std::string> trieGetSuggestions(TrieNode* root, const std::string& prefix);
void loadDefaultDictionary(TrieNode* root);
// تابع برای نمایش درخت
void trieShow(TrieNode* root, bool showAll = false);

#endif