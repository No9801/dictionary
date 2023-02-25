#include <iostream>
#include <string>

#include "word.h"

using namespace std;

Word::Word(const string& chinese, const string& english)
    : Chinese(chinese), English(english) { /* void */ }

bool Word::update(const string& english) {
    this -> English = english;
    return true;
}

bool Word::search(const string& chinese) {
    return this -> Chinese == chinese;
}

bool Word::translate(const string& english) {
    return this -> English == english;
}

string Word::toString() {
    string s;
    return s + "Word [ Chinese: " + this -> Chinese + "  English: " + this -> English + " ]";
}

const string& Word::getChinese() {
    return this -> Chinese;
}

const string& Word::getEnglish() {
    return this -> English;
}

ostream& operator<<(ostream& ots, const Word& word) {
    ots << word.Chinese << " " << word.English;
    return ots;
}