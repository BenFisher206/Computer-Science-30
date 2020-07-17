// SortAnalyzer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <algorithm>
# include <chrono>

using namespace std;

vector <int> read_file(const string& fileName);
void insertionSort(vector <int> aVector);
void bubbleSort(vector <int> aVector);
void selectionSort(vector <int> aVector);

int main()
{
    vector <int> values[4];
    string valueType;

    values[0] = read_file("few-unique-values.txt");
    values[1] = read_file("nearly-sorted-values.txt");
    values[2] = read_file("random-values.txt");
    values[3] = read_file("reversed-values.txt");

    cout << " Files Loaded. Commencing sorting..." << endl << endl << endl; // for printing operation time

    cout << "Bubble Sort:" << endl << endl;
    for (int i = 0; i < 4; i++) {
        auto t1 = chrono::high_resolution_clock::now(); // for calculating operation time
        bubbleSort(values[i]);
        auto t2 = chrono::high_resolution_clock::now(); // for calculating operation time
        auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count(); // for calculating operation time
        if (i == 0) { valueType = "Few Unique"; }
        else if (i == 1) { valueType = "Nearly Sorted"; }
        else if (i == 2) { valueType = "Random"; }
        else if (i == 3) { valueType = "Reversed"; }
        cout << valueType << " values took " << duration << " microseconds" << endl; // for printing operation time
    }
    cout << endl;

    cout << "Selection Sort:" << endl << endl;
    for (int i = 0; i < 4; i++) {
        auto t1 = chrono::high_resolution_clock::now(); // for calculating operation time
        selectionSort(values[i]);
        auto t2 = chrono::high_resolution_clock::now(); // for calculating operation time
        auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count(); // for calculating operation time
        if (i == 0) { valueType = "Few Unique"; }
        else if (i == 1) { valueType = "Nearly Sorted"; }
        else if (i == 2) { valueType = "Random"; }
        else if (i == 3) { valueType = "Reversed"; }
        cout << valueType << " values took " << duration << " microseconds" << endl; // for printing operation time
    }
    cout << endl;

    cout << "Insertion Sort:" << endl << endl;
    for (int i = 0; i < 4; i++) {
        auto t1 = chrono::high_resolution_clock::now(); // for calculating operation time
        insertionSort(values[i]);
        auto t2 = chrono::high_resolution_clock::now(); // for calculating operation time
        auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count(); // for calculating operation time
        if (i == 0) { valueType = "Few Unique"; }
        else if (i == 1) { valueType = "Nearly Sorted"; }
        else if (i == 2) { valueType = "Random"; }
        else if (i == 3) { valueType = "Reversed"; }
        cout << valueType << " values took " << duration << " microseconds" << endl; // for printing operation time
    }
    cout << endl;
}


vector <int> read_file(const string& fileName) {
    //fills the dictionary vector consisting of all the words (assumed lower cased) in the given dictionary text file
    string line;
    vector <int> words;
    ifstream entries(fileName);
    if (entries.is_open()) {
        while (getline(entries, line)) { //until reaches the ned of the file split the file by delimiting every '\n'
            words.push_back(stoi(line));
        }
        entries.close();
    }
    else { cout << "Unable to open file " << fileName << endl; system("pause"); }

    return words;
}

void bubbleSort(vector <int> aVector) {
    // Use Bubble Sort algorithm to sort the argument array
    int temp;
    for (int i = 0; i < aVector.size() - 1; i++) {
        for (int n = 0; n < aVector.size() - i - 1; n++) {
            if (aVector[n] > aVector[n + 1]) {
                temp = aVector[n];
                aVector[n] = aVector[n + 1];
                aVector[n + 1] = temp;
            }
        }
    }
    return;
}

void selectionSort(vector <int> aVector) {
    int min = 0;
    int temp = 0;
    for (int i = 0; i < aVector.size() - 1; i++) {
        // Search for minimum
        min = i;
        for (int n = i + 1; n < aVector.size(); n++) {
            if (aVector[n] < aVector[min]) {
                min = n;
            }
        }
        temp = aVector[min];
        aVector[min] = aVector[i];
        aVector[i] = temp;
    }
    return;
}

void insertionSort(vector <int> aVector) {
    int insert = 0;
    int pos = 0;
    for (int i = 1; i < aVector.size(); i++) {
        insert = aVector[i];
        pos = i;

        while (pos > 0 && aVector[pos - 1] > insert) {
            aVector[pos] = aVector[pos - 1];
            pos--;
        }

        aVector[pos] = insert;
    }
    return;
}
