#include <iostream>
#include <string>

bool IsPalindrom(const std::string& word){
	for (size_t i = 0; i < word.size() / 2; ++i){
		if (word[i] != word[word.size() - 1 - i]){
			return false;
		}
	}
	return true;
}

int main(){
	std::string word;
	std::cin >> word;

	std::cout << IsPalindrom(word);
}
