#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include "trie.cc"   // Implementation file
using namespace std;	

const int NUM_CHARS = 26;

// Initializes an "empty" node. size = 1 (only root node), words = 0, isWord = false.
// Creates array of NUM_CHARS TrieNode pointers, each set to nullptr.
TrieNode::TrieNode() {
  size = 1;
  words = 0;
  isWord = false;
  letters = new TrieNode*[NUM_CHARS];
  for (int i = 0; i < NUM_CHARS; i++ ) {
    letters[i] = nullptr;  // each set to nullptr.
  }
}

TrieNode::~TrieNode() {
  if (letters) {  // not nullptr, otherwise letters[i] would cause issue
    for (int i = 0; i < NUM_CHARS; i++ ) {
      delete letters[i];  // free each pointer to TrieNode inside the array
    }
  }
  delete [] letters;
}

void TrieNode::insert_update(const std::string &word) {
  this->insert(word);  // insert
  this->updateSize();  // then update
}

// Inserts word in this node if it does not already exist.
void TrieNode::insert(const string &word) {
  TrieNode *cur = this;
  for (string::size_type index = 0; index < word.length(); ++index) {
    int i = word[index]-'a';
    if (!cur->letters[i]) {  // nullptr
      cur->letters[i] = new TrieNode();
    } else if (index + 1 == word.length() && cur->isWord) {  // already exists
      break;   // break
    }
    cur = cur->letters[i];
  }  

  cur = this;  // reset back
  for (string::size_type index = 0; index < word.length(); ++index) {
    int i = word[index]-'a';
    if (!cur->letters[i]) {  // nullptr
      cur->letters[i] = new TrieNode();
    }   
    cur->words++;   // only add word count
    cur = cur->letters[i];
  }  
  cur->isWord = true;  // last node marked true
}

// Removes the word from this node, if applicable, by marking word as no
// longer being a word.
void TrieNode::remove(const string &word) {
  TrieNode *cur = this;
  for (string::size_type index = 0; index < word.length(); ++index) {
    int i = word[index]-'a';
    if (!cur->letters[i]) {  // nullptr
      break;  // N/A
    } 
    cur = cur->letters[i];
  }
  cur->isWord = false;
}

// Recalculates the size of the trie by counting all of the nodes.
void TrieNode::updateSize() {
  size = 1;  // always start from 1 since update called multiple times
  for (int index = 0; index < NUM_CHARS; index++) {
    if (letters[index]) {  // not nullptr
      int add = letters[index]->getSize();
      size += add;
    }   
  }
}

string TrieNode::all_combinations(string sofar, string prefix) const {
  if (this->isWord) {    
    sofar += (sofar == "") ? prefix : (" " + prefix);
  }
  for (int x = 0; x < NUM_CHARS; x++) {
    if (this->letters[x]) {  // exists
      char letter = 'a' + x;   // based on posn convert to character
      sofar = (this->letters[x])->all_combinations(sofar, prefix + letter);
    }
  }
  return sofar;
}

// Returns all of the autocompletions for the specified string.
// If there is more than one, each is separated by a single space.
// If there are none, an empty string is returned.
string TrieNode::find(const string &word) const {
  const TrieNode *cur = this;   // need to add const
  string strs = "";
  for (string::size_type index = 0; index < word.length(); ++index) {
    int i = word[index]-'a';
    if (!cur->letters[i]) {  // nullptr
      return strs;    // none
    } 
    cur = cur->letters[i];
  }
  strs = cur->all_combinations(strs, word);
  if (strs.find(' ') != std::string::npos) {  // contains space
    return "";  // more than one, can't identify
  } 
  return strs;   // unique
}

// returns the size of the trie rooted at this node
int TrieNode::getSize() const {
  int s = 1; // always start at 1
  for (int i = 0; i < NUM_CHARS; i++) {
      if (letters[i]) {  // not nullptr
        s += letters[i]->getSize();  // recursion
    } 
  }
  return s;
}
