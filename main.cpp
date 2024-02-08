#include"autoPtr.h"

int main() {
    string filename;
    cout << "Enter the path to the file: ";
    getline(cin, filename);

    TextFile textFile(filename);
    if (!textFile.open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    string choice;
    do {
        cout << "\nChoose an option:\n"
            << "1. Search for a string\n"
            << "2. Replace a string\n"
            << "3. Display file content\n"
            << "4. Reverse file content\n"
            << "5. Exit\n"
            << "Enter your choice: ";
        getline(cin, choice);

        if (choice == "1") {
            string searchString;
            cout << "Enter the string to search: ";
            getline(cin, searchString);
            int occurrences = textFile.search(searchString);
            cout << "Occurrences found: " << occurrences << endl;
        }
        else if (choice == "2") {
            string searchString, replacementString;
            cout << "Enter the string to replace: ";
            getline(cin, searchString);
            cout << "Enter the replacement string: ";
            getline(cin, replacementString);
            int replacements = textFile.replace(searchString, replacementString);
            cout << "Replacements made: " << replacements << endl;
        }
        else if (choice == "3") {
            cout << "File content:\n";
            textFile.display();
        }
        else if (choice == "4") {
            textFile.reverse();
            cout << "File content reversed." << endl;
        }
        else if (choice != "5") {
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
        }

    } while (choice != "5");

    textFile.close();
    return 0;
}