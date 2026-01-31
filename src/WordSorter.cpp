#include "WordSorter.h"

void WordSorter::inputWords(const std::string& input) {
    size_t pos = 0;
    std::string word;
    std::string inputCopy = input;

    // Split input based on spaces
    while ((pos = inputCopy.find(' ')) != std::string::npos) {
        word = inputCopy.substr(0, pos);
        wordsList.push_back(word);
        inputCopy.erase(0, pos + 1);
    }

    if (!inputCopy.empty()) {
        wordsList.push_back(inputCopy);
    }
}

void WordSorter::sortWords() {
    std::sort(wordsList.begin(), wordsList.end());
}

std::string WordSorter::displayWords() const {
    std::string output;
    for (const auto& word : wordsList) {
        output += word + " ";
    }
    return output;
}
