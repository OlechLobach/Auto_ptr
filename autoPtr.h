#ifndef autoptr_h
#define autoptr_h

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sstream>
#include <algorithm>
#include<vector>
using namespace std;

class FileException : public exception {
private:
    string fileName;

public:
    FileException(const string& filename) : fileName(filename) {}

    virtual const char* what() const noexcept override {
        return ("File Exception: Error while processing file '" + fileName + "'").c_str();
    }
};


class TextFile {
private:
    string filename;
    unique_ptr<ifstream> fileStream;

public:
    TextFile(const string& filename) : filename(filename) {}

    bool open() {
        fileStream = make_unique<ifstream>(filename);
        return fileStream->is_open();
    }

    void close() {
        if (fileStream) {
            fileStream->close();
        }
    }

    int search(const string& searchString) {
        if (!fileStream || !fileStream->is_open()) {
            throw FileException(filename);
        }

        string line;
        int occurrences = 0;
        while (getline(*fileStream, line)) {
            if (line.find(searchString) != string::npos) {
                ++occurrences;
            }
        }

        return occurrences;
    }

    int replace(const string& searchString, const string& replacementString) {
        if (!fileStream || !fileStream->is_open()) {
            throw FileException(filename);
        }

        stringstream tempFilename;
        tempFilename << filename << ".tmp";
        ofstream tempFile(tempFilename.str());

        string line;
        int replacements = 0;
        while (getline(*fileStream, line)) {
            size_t pos = 0;
            while ((pos = line.find(searchString, pos)) != string::npos) {
                line.replace(pos, searchString.length(), replacementString);
                pos += replacementString.length();
                ++replacements;
            }
            tempFile << line << endl;
        }

        tempFile.close();
        fileStream->close();
        remove(filename.c_str());
        rename(tempFilename.str().c_str(), filename.c_str());

        open();

        return replacements;
    }

    void display() {
        if (!fileStream || !fileStream->is_open()) {
            throw FileException(filename);
        }

        string line;
        while (getline(*fileStream, line)) {
            cout << line << endl;
        }
    }

    void reverse() {
        if (!fileStream || !fileStream->is_open()) {
            throw FileException(filename);
        }

        vector<string> lines;
        string line;
        while (getline(*fileStream, line)) {
            lines.push_back(line);
        }

        std::reverse(lines.begin(), lines.end());

        fileStream->close();
        ofstream outFile(filename);
        for (const auto& l : lines) {
            outFile << l << endl;
        }

        open();
    }
};


#endif