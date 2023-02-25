#ifndef _DICTIONARYFUNCTION_H_
#define _DICTIONATYFUNCTION_H_

#include <string>

#include "word.h"

const int maxDictionarySize = 65536;

bool insert(const std::string&, const std::string&, Word**, int&);
bool delete_(const std::string&, Word**, int&);
bool update(const std::string&, const std::string&, Word**, const int&);
Word* search(const std::string&, Word**, const int&);
Word* translate(const std::string&, Word**, const int&);


#endif /* _DICTIONARYFUNCTION_H_ */