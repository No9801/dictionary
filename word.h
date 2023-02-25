#ifndef _WORD_H_
#define _WORD_H_

#include <iostream>
#include <string>

class Word {
    friend std::ostream& operator<<(std::ostream&, const Word&);
    std::string Chinese;
    std::string English;
public:
    Word(const std::string&, const std::string&);
    bool update(const std::string&);
    bool search(const std::string&);
    bool translate(const std::string&);
    std::string toString();
    const std::string& getChinese();
    const std::string& getEnglish();
};

std::ostream& operator<<(std::ostream&, const Word&);

#endif /* _WORD_H_ */