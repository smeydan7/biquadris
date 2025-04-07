#include <string>

class TrieNode {
  int size;           // size of the trie rooted at this node
  int words;          // number of words that go through this node of the trie
  bool isWord;        // is this particular prefix a word itself?
  TrieNode **letters; // array of TrieNode pointers

  // Add private helper methods if needed
  std::string all_combinations(std::string sofar, std::string prefix) const;
 public:
  // Initializes an "empty" node. size = 1 (only root node), words = 0, isWord = false.
  // Creates array of NUM_CHARS TrieNode pointers, each set to nullptr.
  TrieNode();
  ~TrieNode();

  // Inserts word in this node if it does not already exist.
  void insert(const std::string &word);

  // Removes the word from this node, if applicable, by marking word as no
  // longer being a word.
  void remove(const std::string &word);

  // Recalculates the size of the trie by counting all of the nodes.
  void updateSize();

  // Returns all of the autocompletions for the specified string.
  // If there is more than one, each is separated by a single space.
  // If there are none, an empty string is returned.
  std::string find(const std::string &word) const;

  // returns the size of the trie rooted at this node
  int getSize() const;

  void insert_update(const std::string &word);
};
