#include <iostream>
#include <string>
#include <algorithm>

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

string strWithBlanks(const string& s) {
    if (find(s.begin(), s.end(), ' ') != s.end()) {
        return "\"" + s + "\"";
    }
    return s;
}

ostream& operator<<(ostream& ots, const Word& word) {
    ots << strWithBlanks(word.Chinese) << " " << strWithBlanks(word.English);
    return ots;
}