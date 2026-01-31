#include "sorter.h"

void WordSorter::inputWords() {
    std::string word;
    std::cout << "Write your words (end with Ctrl+D or Ctrl+Z):" << std::endl;
    while (std::cin >> word) {
        wordsList.push_back(word);
    }
}

void WordSorter::sortWords() {
    std::sort(wordsList.begin(), wordsList.end());
}

void WordSorter::displayWords() const {
    std::cout << "Sorted words: " << std::endl;
    for (const auto& word : wordsList) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}
