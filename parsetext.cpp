/*Name: Neoma Reza
Email: nareza@crimson.ua.edu
Course Section: Fall 2024 CS 201 - 001
Homework#: 1
To Compile: Click "Terminal", then "New Terminal" and enter this: g++ -std=c++20 parsetext.cpp -o parsetext.exe
To Run: Click "Terminal", then "New Terminal" and enter this (change the inputName to the name of text file): ./parsetext.exe inputName.txt
*/
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <regex>
#include <algorithm>
#include <chrono> //for timing

//define a structure to store word counts for sorting
struct WordCount {
    std::string word;
    int count;
    WordCount(const std::string& w, int c) : word(w), count(c) {}
};

// Comparison function for sorting
bool comp(const WordCount& x, const WordCount& y) {
    if (x.count == y.count) { //if frequency are equal
        return x.word < y.word; //sort alphabetically (a - z)
    } else { 
        return x.count > y.count; //sort by frequency (from highest to lowest of frequency the word)
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) { //check file
        return 1;
    }
    std::ifstream file(argv[1]); //open input file
    if (!file) { //file can't open
        return 1;
    }
    auto start = std::chrono::high_resolution_clock::now(); //for timing

    //--------------------------------------------------------------------
    std::string text;
    std::unordered_map<std::string, int> word_counts_map; //map to store word counts
    const std::regex delim("\\s+"); //regex for splitting the whitespace

    //read file by each line
    while (std::getline(file, text)) {
        //tokenize the line into words
        auto begin = std::sregex_token_iterator(text.begin(), text.end(), delim, -1);
        auto end = std::sregex_token_iterator();
        for (std::sregex_token_iterator word = begin; word != end; word++) {
            std::string token = *word;
            if (!token.empty()) {
                word_counts_map[token]++; //increment count or insert if there is a new word
            }
        }
    }
    file.close(); //close file

    //transfer data from 'unordered_map' to vector 'WordCount'
    std::vector<WordCount> word_counts;
    for (const auto& pair : word_counts_map) {
        word_counts.emplace_back(pair.first, pair.second);
    }

    std::sort(word_counts.begin(), word_counts.end(), comp); //sort vector by count and words with the same count for alphabetically
    //-----------------------------------------------------------------------------------------
    auto end_time = std::chrono::high_resolution_clock::now(); //stop timing
    std::chrono::duration<double> duration = end_time - start;
    //------------------------------------------------------------------------------------------
    for (const auto& wc : word_counts) {
        std::cout << wc.word << ": " << wc.count << std::endl; //output the words with the frequency of the words
    }
    std::cout << "\nTime taken: " << duration.count() << " seconds" << std::endl; //output time taken
    return 0;
}