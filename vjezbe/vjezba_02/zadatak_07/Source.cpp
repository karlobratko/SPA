#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

void InputFileName(std::string& p_Str);
void InputWord(std::string& p_Word);
std::size_t CountWordsInFile(const std::string& p_FileName);
void CopyWordsToVector(const std::string& p_FileName, std::vector<std::string>& p_Dst);
std::size_t CountWordInVector(const std::string& p_Word, const std::vector<std::string>& p_Src);

int main() {
	std::string file_name{};
	InputFileName(file_name);

	std::string word{};
	InputWord(word);

	std::size_t len{ CountWordsInFile(file_name) };
	std::vector<std::string> words{ len };

	CopyWordsToVector(file_name, words);
	// std::for_each(words.begin(), words.end(), [](const std::string& s) -> void { std::cout << s << std::endl; });

	std::size_t word_count{ CountWordInVector(word, words) };
	std::cout << "count: " << word_count << std::endl;

	return 0;
}

void InputFileName(std::string& p_Str) {
	std::cout << "file: ";
	std::getline(std::cin, p_Str);
}

void InputWord(std::string& p_Word) {
	std::cout << "word: ";
	std::getline(std::cin, p_Word);
}

std::size_t CountWordsInFile(const std::string& p_FileName) {
	std::ifstream file_reader{ p_FileName };
	if (!file_reader)
		throw std::runtime_error("COUNTWORDSINFILE::IFSTREAM::RUNTIME_ERROR::could not open file");
	std::size_t count{};
	std::string temp{};
	while (file_reader >> temp) ++count;
	file_reader.close();
	return count;
}

void CopyWordsToVector(const std::string& p_FileName, std::vector<std::string>& p_Dst) {
	std::ifstream file_reader{ p_FileName };
	if (!file_reader)
		throw std::runtime_error("COUNTWORDSINFILE::IFSTREAM::RUNTIME_ERROR::could not open file");
	std::size_t i{};
	std::string temp{};
	while (file_reader >> temp)
		p_Dst[i++] = std::move(temp);
	file_reader.close();
}

std::size_t CountWordInVector(const std::string& p_Word, const std::vector<std::string>& p_Src) {
	return std::count(p_Src.begin(), p_Src.end(), p_Word);
}
