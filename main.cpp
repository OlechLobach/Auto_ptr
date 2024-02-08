#include"autoPtr.h"

int main() {
    string filename;
    cout << "Enter the path to the HTML file: ";
    getline(cin, filename);

    HTMLValidator validator(filename);
    if (!validator.openFile()) {
        return 1;
    }

    if (validator.validate()) {
        cout << "The HTML file is valid." << endl;
    }
    else {
        cout << "The HTML file is not valid." << endl;
    }

    return 0;
}