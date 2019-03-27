// Used the pig latin converter from Geeks-for-Geeks:
// https://www.geeksforgeeks.org/encoding-word-pig-latin/

#include <stringModifier.h>
#include <Utility.h>
#include <sstream>

bool isVowel(char c){
	return (c == 'A' || c == 'E' || c == 'I' ||  
            c == 'O' || c == 'U' || c == 'a' ||  
            c == 'e' || c == 'i' || c == 'o' || 
            c == 'u'); 
}

std::string translate(std::string message){
    std::vector<std::string> split = utility::popFront(message);
    std::vector<std::string> tokens = utility::tokenizeString(split.at(1));
    std::stringstream retString;

    retString << split.at(0) << " ";
    for(auto &token : tokens) {
        retString << pigLatin(token) << " ";
    }

    return retString.str();
}

std::string pigLatin(std::string word) { 
    // the index of the first vowel is stored. 
    int len = word.length(); 
    int index = -1; 
    for (int i = 0; i < len; i++) { 
        if (isVowel(word[i])) { 
            index = i; 
            break; 
        } 
    } 
  
    // Pig Latin is possible only if vowels 
    // is present 
    if (index == -1) 
        return word; 
  
    // Take all characters after index (including 
    // index). Append all characters which are before 
    // index. Finally append "ay" 
    return word.substr(index) + word.substr(0, index) + "ay"; 
}

std::string whisperModifier(std::string message) {
    std::stringstream s(message);
    std::stringstream retString;
    std::string word;

    while(s >> word){
        std::replace_if( word.begin( ), word.end( ), [] ( const char c ) {
            return std::string( "etanidufkqETANIDUFKQ" ).find( c ) != std::string::npos;
        }, '.');

        retString << word << " ";
    }

    return retString.str();
}