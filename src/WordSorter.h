#ifndef WORDSORTER_H
#define WORDSORTER_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class WordSorter {
public:
    void inputWords(const std::string& input);
    void sortWords();
    std::string displayWords() const;

private:
    std::vector<std::string> wordsList;
};

#endif // WORDSORTER_H
