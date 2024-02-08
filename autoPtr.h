#ifndef autoptr_h
#define autoptr_h
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <memory>
using namespace std;
class HTMLValidator {
private:
    string filename;
    unique_ptr<ifstream> fileStream;

public:
    HTMLValidator(const string& filename) : filename(filename) {}

    bool openFile() {
        fileStream = make_unique<ifstream>(filename);
        return fileStream->is_open();
    }

    bool validate() {
        if (!fileStream || !fileStream->is_open()) {
            cerr << "Error: Unable to open file." << endl;
            return false;
        }

        stack<string> tagStack;
        string line;
        while (getline(*fileStream, line)) {
            cout << "Read line from file: " << line << endl;

            size_t pos = 0;
            while ((pos = line.find('<', pos)) != string::npos) {
                size_t endPos = line.find('>', pos);
                if (endPos == string::npos) {
                   cerr << "Error: Invalid tag - opening tag without closing tag." << endl;
                    return false;
                }
                string tag = line.substr(pos + 1, endPos - pos - 1);
                if (tag[0] != '/') {
                    tagStack.push(tag);
                }
                else {
                    if (tagStack.empty()) {
                        cerr << "Error: Invalid tag - closing tag without corresponding opening tag." << endl;
                        return false;
                    }
                    string openingTag = tagStack.top();
                    tagStack.pop();
                    if (openingTag != tag.substr(1)) {
                        cerr << "Error: Invalid tag - closing tag does not match opening tag." << endl;
                        return false;
                    }
                }
                pos = endPos + 1;
            }
        }

        if (!tagStack.empty()) {
            cerr << "Error: Invalid HTML structure - some opening tags are not closed." << endl;
            return false;
        }

        return true;
    }
};
#endif