#include <string>
#include <iostream>
#include <algorithm>
// #include <sstream>

#include "dictionaryFunction.h"
#include "word.h"

using namespace std;

bool insert(const string& chinese, const string& english, Word** dic, int& dicCount) {
    Word* word = search(chinese, dic, dicCount);
    if (word != nullptr || dicCount == maxDictionarySize) {
        return false;
    }
    word = new Word(chinese, english);
    dic[dicCount] = word;
    ++dicCount;
    return true;
}

bool delete_(const string& chinese, Word** dic, int& dicCount) {
    Word** word = find_if(dic, dic + dicCount, 
        [&chinese](Word* w) -> bool {return w -> search(chinese);});
    if (word == dic + dicCount) {
        return false;
    }
    delete *word;
    for (unsigned i = 0; word + i != dic + dicCount; ++i) {
        word[i] = word[i + 1];
    }
    --dicCount;
    return true;
}

bool update(const string& chinese, const string& english, Word** dic, const int& dicCount) {
    Word** word = find_if(dic, dic + dicCount,
        [&chinese](Word* w) -> bool {return w -> search(chinese);});
    if (word == dic + dicCount) {
        return false;
    }
    return (*word) -> update(english);
}

Word* search(const string& chinese, Word** dic, const int& dicCount) {
    Word** word = find_if(dic, dic + dicCount,
        [&chinese](Word* w) -> bool {return w -> search(chinese);});
    if (word == dic + dicCount) {
        return nullptr;
    }
    return *word;
}

Word* translate(const string& english, Word** dic, const int& dicCount) {
    Word** word = find_if(dic, dic + dicCount,
        [&english](Word* w) -> bool {return w -> translate(english);});
    if (word == dic + dicCount) {
        return nullptr;
    }
    return *word;
}

istream& readString(istream& ins, string& str) {
    str = "";
    // ostringstream oss(str);
    string buff;
    if (ins >> buff && buff.front() == '"') {
        (str += buff.substr(1)) += " ";
        while (ins >> buff) {
            if (buff.back() == '"') {
                str += buff.substr(0, buff.size() - 1);
                return ins;
            }
            (str += buff) += " ";
        }
        return ins;
    }
    str += buff;
    return ins;
}