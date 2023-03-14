#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdexcept>

#include "dictionaryFunction.h"
#include "word.h"

#define isHelp(command) strcmp(command, "help") == 0 \
|| strcmp(command, "-h") == 0 \
|| strcmp(command, "--help") == 0 \
|| strcmp(command, "/?") == 0
#define DataExt ".data"
#define CommandExt ".command"

using namespace std;

// #define DEBUG

void getHelp() {
    cout << "Help of this program:" << endl
    << "\tinsert\t\t<Chinese>\t<English>" << endl
    << "\tdelete\t\t<Chinese>" << endl
    << "\tdeleteAll" << endl
    << "\tupdate\t\t<Chinese>\t<English>" << endl
    << "\tsearch\t\t<Chinese>" << endl
    << "\ttranslate\t<English>" << endl
#ifdef DEBUG
    << "\tshow\t\t<number>" << endl
#endif
    << "\talias\t\t<alias>\t\t<command>" << endl
    << "\tload\t\t<file>" << endl
    << "\tsave\t\t<file>" << endl
#ifdef DEBUG
    << "\tshow\t\t< $count | $alias | $word >" << endl
    << "\tlist" << endl
#endif
    << "\thelp" << endl
    << "\texit" << endl;
}

void parser(Word** dic, int& dicCount, Word** alias, int& aliasCount, 
        istream& ins = cin, ostream& ots = cout, ostream& ers = cerr) {
    string command;
    string argument1;
    string argument2;
    while ((ots << "command > ", readString(ins, command))) {
        Word* cmd;
        if ((cmd = search(command, alias, aliasCount)) != nullptr) {
            command = cmd->getEnglish();
        }
        if (command == "insert") {
            readString(readString(ins, argument1), argument2);
            if (!insert(argument1, argument2, dic, dicCount)) {
                ers << "Insert Failed" << endl;
            } else {
                ots << "Insert Complete" << endl;
            }
        } else if (command == "delete") {
            readString(ins, argument1);
            if (!delete_(argument1, dic, dicCount)) {
                ers << "Delete Failed" << endl;
            } else {
                ots << "Delete Complete" << endl;
            }
        } else if (command == "update") {
            readString(readString(ins, argument1), argument2);
            if (!update(argument1, argument2, dic, dicCount)) {
                ers << "Update Failed" << endl;
            } else {
                ots << "Update Complete" << endl;
            }
        } else if (command == "search") {
            readString(ins, argument1);
            Word* result;
            if ((result = search(argument1, dic, dicCount)) != nullptr) {
                ots << "Search Result: " << result -> getEnglish() << endl;
            } else {
                ers << "Not Found!" << endl;
            }
#ifdef DEBUG
        } else if (command == "show") {
            readString(ins, argument1);
            int i = -1;
            if (argument1[0] == '$') {
                if (argument1 == "$count") {
                    ots << dicCount << endl;
                } else if (argument1 == "$alias") {
                    for (int i = 0; i != aliasCount; ++i) {
                        ots << (alias[i]) -> getChinese() << " -> " << (alias[i]) -> getEnglish() << "\n"; 
                    }
                    ots << flush;
                } else if (argument1 == "$word") {
                    for (int i = 0; i != dicCount; ++i) {
                        ots << (dic[i])->toString() << "\n";
                    }
                    ots << flush;
                }
            } else {
                try {
                    i = stoi(argument1);
                } catch (invalid_argument iaerr) {
                    ers << "Invalid Argument: " << argument1 << endl;
                    continue;
                } catch (out_of_range oorerr) {
                    ers << "Invalid Argument: " << argument1 << endl;
                    continue;
                }
                if (i < 0 || i >= dicCount) {
                    ers << "Out Of Range: " << i << endl;
                    continue;
                }
                ots << dic[i] -> toString() << endl;
            }
#endif
        } else if (command == "help") {
            getHelp();
        } else if (command == "exit") {
            return;
        } else if (command == "load") {
            readString(ins, argument1);
            ifstream ifs(argument1, ios_base::in);
            ofstream ofs("units000", ios_base::out);
            parser(dic, dicCount, alias, aliasCount, ifs, ofs, ofs);
            ots << "Load Complete" << endl;
        } else if (command == "save") {
            readString(ins, argument1);
            ofstream dataOfs(argument1 + DataExt, ios_base::out);
            ofstream commandOfs(argument1 + CommandExt, ios_base::out);
            for (int i = 0; i != dicCount; ++i) {
                dataOfs << "insert " << *(dic[i]) << "\n";
            }
            for (int i = 0; i != aliasCount; ++i) {
                commandOfs << "alias " << *(alias[i]) << "\n";
            }
            dataOfs << flush;
            commandOfs << flush;
            dataOfs.close();
            commandOfs.close();
            ots << "Save Complete" << endl;
#ifdef DEBUG
        } else if (command == "list") {
            for (int i = 0; i != dicCount; ++i) {
                ots << (dic[i])->toString() << "\n";
            }
            ots << flush;
#endif
        } else if (command == "translate") {
            readString(ins, argument1);
            Word* result;
            if ((result = translate(argument1, dic, dicCount)) != nullptr) {
                ots << "Translate Result: " << result -> getChinese() << endl;
            } else {
                ers << "Not Found!" << endl;
            }
        } else if (command == "alias") {
            readString(readString(ins, argument1), argument2);
            if ((cmd = search(argument1, alias, aliasCount)) != nullptr) {
                update(argument1, argument2, alias, aliasCount);
            } else {
                insert(argument1, argument2, alias, aliasCount);
            }
            ots << "Set Alias Complete" << endl;
        } else if (command == "deleteAll") {
            for (int i = 0; i != dicCount; ++i) {
                delete dic[i];
            }
            dicCount = 0;
            ots << "Delete Complete" << endl;
#ifdef DEBUG
        } else if (command == "_insert") {
            readString(readString(ins, argument1), argument2);
            if (!insert(argument1, argument2, dic, dicCount)) {
                ers << "Insert Failed" << endl;
            }
        } else if (command == "_alias") {
            readString(readString(ins, argument1), argument2);
            if ((cmd = search(argument1, alias, aliasCount)) != nullptr) {
                update(argument1, argument2, alias, aliasCount);
            } else {
                insert(argument1, argument2, alias, aliasCount);
            }
#endif
        }
    }
}

int main(int argn, const char* argv[]) {
    Word* dic[maxDictionarySize];
    int dicCount = 0;
    Word* alias[maxDictionarySize];
    int aliasCount = 0;
    if (argn > 1) {
        if (argn == 2) {
            if (isHelp(argv[1])) {
                getHelp();
            }
        }
        return 0;
    }
    parser(dic, dicCount, alias, aliasCount);
    return 0;
}
