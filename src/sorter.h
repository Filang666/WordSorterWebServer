#ifndef WORDSORTER_H
#define WORDSORTER_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class WordSorter {
public:
    void inputWords();
    void sortWords();
    void displayWords() const;

private:
    std::vector<std::string> wordsList;
};

#endif
