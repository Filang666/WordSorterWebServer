#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::string words;
    std::cin >> words;
    char letter = ' ';
    int newpos = 0;
    std::vector<std::string> wordslist = {};
    for(int i = 0; i < sizeof(words); i++){
        letter = words[i];
        if(letter == ' '){
            wordslist.push_back(words.substr(newpos, i));
            newpos = i;
        }
    }

    std::sort(wordslist.begin(), wordslist.end());

    for (const std::string& word : wordslist) {
        std::cout << word << " ";
    }

    return 0;
}
