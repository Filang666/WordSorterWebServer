#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::string words;
    std::cout << "write ur words" << std::endl;
    char letter;
    int newpos = 0;
    std::vector<std::string> wordslist = {};
    while (std::cin >> words) {
        wordslist.push_back(words);
    }
   std::sort(wordslist.begin(), wordslist.end());
   std::cout << "         " << std::endl;
   for(int i = 0; i < wordslist.size(); i++){
       std::cout << wordslist[i] << " ";
   }

    return 0;
}
