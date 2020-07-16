//Program for a simple spell check using a dictionary and Binary/Linear search
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <algorithm>
# include <chrono>

using namespace std;

int read_dictionary(const string& fileName);
vector <string> read_book(const string& fileName);
string removeNonAlphaNumeric(string value);
int linearSearch(string input);
int binarySearch(string input);

vector <string> dictionary;

int main() {

    vector <string> book;
    string input;
    string searchValue;
    int result;
    int errorValues = 0;

    read_dictionary("dictionary.txt");
    book = read_book("AliceInWonderland.txt");
    for (unsigned int i = 0; i < book.size(); i++) { // remove all non letters but keep words such as don't...
        book[i] = removeNonAlphaNumeric(book[i]);
    }

    // Give user option between searching a word or searching the alice in wonderland book
    cout << "Choose one of the 2 options (input 1 or 2):" << endl;
    cout << "1. Single Word Spellcheck" << endl;
    cout << "2. Alice in Wonderland spellcheck" << endl;
    cin >> searchValue;
    while (searchValue != "1" && searchValue != "2") {
        system("cls");
        cout << "Invalid arguement please choose either 1 or 2" << endl;
        cout << "Choose one of the 2 options (input 1 or 2):" << endl;
        cout << "1. Single Word Spellcheck" << endl;
        cout << "2. Alice in Wonderland spellcheck" << endl;
        cin >> searchValue;
    }
    if (searchValue == "1") {
        // Single word option has been selected
        cout << "Please enter a word to search the dictionary with..." << endl;
        cin >> input;
        system("cls");
        for (auto& p : input) { // lower case input
            p = tolower(p);
        }
        cout << "Please choose a search method (input 1 or 2):" << endl;
        cout << "1. Linear Search" << endl;
        cout << "2. Binary Search" << endl;
        cin >> searchValue;
        while (searchValue != "1" && searchValue != "2") {
            system("cls");
            cout << "Invalid arguement please choose either 1 or 2" << endl;
            cout << "Please choose a search method (input 1 or 2):" << endl;
            cout << "1. Linear Search" << endl;
            cout << "2. Binary Search" << endl;
            cin >> searchValue;
        }
        if (searchValue == "1") { // linear search
            auto t1 = chrono::high_resolution_clock::now(); // for calculating operation time
            result = linearSearch(input);
            auto t2 = chrono::high_resolution_clock::now(); // for calculating operation time
            auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count(); // for calculating operation time
            cout << "Operation took " << duration << " microseconds" << endl; // for printing operation time
        }
        else { // binary search
            auto t1 = chrono::high_resolution_clock::now(); // for calculating operation time
            result = binarySearch(input);
            auto t2 = chrono::high_resolution_clock::now(); // for calculating operation time
            auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count(); // for calculating operation time
            cout << "Operation took " << duration << " microseconds" << endl; // for printing operation time
        }
        if (result == -1) {
            cout << "The word " << input << " was not found in the dictionary." << endl; return 1;
        }
        cout << "The word " << input << " was found at line " << result << endl;

    }
 
    else { // Alice in Wonderland option has been selected
        system("cls");
        cout << "Please choose a search method (input 1 or 2):" << endl;
        cout << "1. Linear Search" << endl;
        cout << "2. Binary Search" << endl;
        cin >> searchValue;
        while (searchValue != "1" && searchValue != "2") {
            system("cls");
            cout << "Invalid arguement please choose either 1 or 2" << endl;
            cout << "Please choose a search method (input 1 or 2):" << endl;
            cout << "1. Linear Search" << endl;
            cout << "2. Binary Search" << endl;
            cin >> searchValue;
        }
        errorValues = 0;
        if (searchValue == "1") { // linear search
            auto t1 = chrono::high_resolution_clock::now(); // for calculating operation time
            for (int i = 0; i < book.size(); i++) {
                if (book[i].size() == 0) { continue; }
                result = linearSearch(book[i]);
                if (result == -1) {
                    cout << "The word " << book[i] << " was not found in the dictionary." << endl;
                    errorValues++;
                }
            }
            auto t2 = chrono::high_resolution_clock::now(); // for calculating operation time
            auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count(); // for calculating operation time
            cout << "Operation took " << duration << " microseconds" << endl; // for printing operation time
        }
        else { // binary search
            auto t1 = chrono::high_resolution_clock::now(); // for calculating operation time
            for (unsigned int i = 0; i < book.size(); i++) {
                if (book[i].size() == 0) { continue; }
                result = binarySearch(book[i]);
                if (result == -1) {
                    cout << "The word " << book[i] << " was not found in the dictionary." << endl;
                    errorValues++;
                }
            }
            auto t2 = chrono::high_resolution_clock::now(); // for calculating operation time
            auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count(); // for calculating operation time
            cout << "Operation took " << duration << " microseconds" << endl; // for printing operation time
        }

        cout << "There were " << errorValues << " words not found in the dictionary!";
    }


    return 0;
}


int read_dictionary(const string& fileName) {
    //fills the dictionary vector consisting of all the words (assumed lower cased) in the given dictionary text file
    string line;
    ifstream entries(fileName);
    if (entries.is_open()) {
        while (getline(entries, line)) { //until reaches the ned of the file split the file by delimiting every '\n'
            // cout << line << "\t" << line.size() << endl; // For debugging purposes
            dictionary.push_back(line);
        }
        entries.close();
    }
    else { cout << "Unable to open file " << fileName << endl; system("pause"); }

    return 0;
}

vector <string> read_book(const string& fileName) {
    //Returns a vector consisting of all the words (lower cased) in the given text file
    string line;
    ifstream entries(fileName);
    char delimit = ' ';
    vector <string> words;
    int pos = 0, i = 0;

    if (entries.is_open()) {
        i = 0;
        while (getline(entries, line)) { //until reaches the ned of the file split the file by delimiting every '\n'
            if (line.size() < 1) { continue;  }
            replace(line.begin(), line.end(), '-', ' ');
            while ((pos = line.find(delimit)) != string::npos) {
                words.push_back(line.substr(0, pos)); // store string into array
                line.erase(0, pos + 1); // remove portion from source string along with the \t
                for (auto& p : words[i]) {
                    p = tolower(p);
                }
                i++;
            }
            words.push_back(line.substr(0, pos)); // store string into array
            //*/
            //words.push_back(line); // store string into array
            for (auto& p : words[i]) {
                p = tolower(p);
            }
            i++;
        }
        //cout << words.size() << endl; // For debugging purposes
        entries.close();
    }
    else { cout << "Unable to open file " << fileName << endl; system("pause"); }

    return words;

}


string removeNonAlphaNumeric(string value) {
    int index = 0;
    vector <int> remove;
    for (auto& p : value) {
        if (isalpha(p)) { } // Do nothing
        else {
            if (p == '\'') {
                if (index == 0) { remove.push_back(0); } // prevents from passing isalpha value[-1] as it may cause errors
                else if (index == value.size() - 1) { remove.push_back(value.size() - 1); } // prevents from passing isalpha value[max + 1] as it may cause errors
                else if (isalpha(value[index - 1]) && isalpha(value[index + 1])) { continue; } // the apostrophe is a part of a word as it has letters on both sides
                else { remove.push_back(index); }
            }
            else { remove.push_back(index); }
        }
        index++;
    }
    for (int i = remove.size() - 1; i >= 0; i--) { // as the remove vector stores the largest indexes at the end in order to prevent skipping we read the vector backwards
        value.erase(value.begin() + remove[i]);
    }

    return value;
}

int linearSearch(string input) { // Code for linear search
    for (unsigned int i = 0; i < dictionary.size(); i++) {
        if (dictionary[i] == input) {
            return i + 1;
        }
    }
    return -1;
}

int binarySearch(string input) { // cocde for binary search
    int lowerIndex = 0;
    int upperIndex = dictionary.size() - 1;
    int middleIndex = 0;
    string middleString;
    if (input.size() == 0) { return -1; }
    while (lowerIndex <= upperIndex) { //while all elements have not been checked
        middleIndex = floor((lowerIndex + upperIndex) / 2);
        middleString = dictionary[middleIndex]; // store value in middle
        if (input == middleString) {
            return middleIndex + 1; // vector starts with 0 while dictionary starts with line 1
        }
        else if (input < middleString) { // compare alphabetically middleString and input
            upperIndex = middleIndex - 1;
        }
        else { // item > than the value at the middle index
            lowerIndex = middleIndex + 1;
        }
    }

    // Went through loop without finding item, so... 
    return -1;
}
