#ifndef PIGLATIN_H
#define PIGLATIN_H

#include <string>

bool isVowel(char c);

std::string translate(std::string message);

std::string pigLatin(std::string word);

std::string whisperModifier(std::string message);

#endif