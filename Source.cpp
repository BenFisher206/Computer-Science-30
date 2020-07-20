# include "Pokemon.h"
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <vector>
# include <unordered_map>

using namespace std;


typedef vector<Pokemon> Pokedex;

vector<Pokemon> read_pokemons_from_file(const string& fileName); // Reads a txt file and fills the pokedex information
Type convertStringtoType(string value); // converts a string into the Type data structure
Gender convertStringtoGender(string value); // converts a string into the Gender data structure
bool print_pokemon_by_name(const Pokedex& pokedex);
bool print_pokemon_by_number(const Pokedex& pokedex);
bool print_pokemon_by_type(const Pokedex& pokedex);
string convertTypetoString(Type value);
string convertGendertoString(Gender value);

int main() {

    const auto pokedex = read_pokemons_from_file("Pokemon.txt");
    bool repeat = true;
    string input = "";
    string inputType = "";

    //Ask the user which way they would like to search
    while (repeat) {
        cout << "Welcome to the Pokedex! We have the first " << pokedex.size() << " pokemon catalogged!" << endl;
        cout << "Would you like to search by name, number, or type?" << endl;
        input = "";
        cin >> input;

        //make input uppercase
        for (auto& p : input) {
            p = toupper(p);
        }

        if (input == "NAME") {
            system("cls");
            print_pokemon_by_name(pokedex);
        }
        else if (input == "NUMBER") {
            system("cls");
            if (!print_pokemon_by_number(pokedex)) {
                cout << "--------------- ERROR: NO POKEMON IN POKEDEX ---------" << endl << endl;
            }
        }
        else if (input == "TYPE") {
            system("cls");
            if (!print_pokemon_by_type(pokedex)) {
                cout << "--------------- THE GIVEN TYPE HAS NOT BEEN CATALOGED YET ---------" << endl << endl;
            }
        }
        else {
            cout << "Invalid Input" << endl;
            cout << "Would you like to retry? (Y/N)" << endl;
            input = "";
            cin >> input;
            if (input == "Y" || input == "y") { system("cls");  continue; } // continue
            else if (input == "N" || input == "n") { // end
                break;
            }
        }
        while (1) { // repeat until broken out of
            cout << "Would you like to do another search? (Y/N)" << endl;
            input = "";
            cin >> input;
            if (input == "Y" || input == "y") { system("cls");  break; } // continue
            else if (input == "N" || input == "n") { // end
                repeat = false;
                break;
            }
            else { // invalid input
                cout << "Invalid Input" << endl;
            }
        }
    }
    return 0;
}

bool print_pokemon_by_name(const Pokedex& pokedex) {
    // Linear searches the vector to find the inputted Pokemon and then prints out the information found
    int IO = 0; //used to upper case the first character of the input

    //Ask for name
    cout << "Enter the name of the pokemon" << endl;
    string input_name;
    cin >> input_name;

    //make input lowercase
    for (auto& p : input_name) {
        if (IO == 1) { // lower case all non starting characters
            p = tolower(p);
        }
        else { // capitalize starting character
            p = toupper(p);
            IO = 1;
        }
    }

    for (int i = 0; i < pokedex.size(); i++) {
        if (input_name == pokedex[i].name) {
            printf("#%03d\n\n", pokedex[i].ID);
            cout << pokedex[i].name << endl;
            cout << "Type: " << convertTypetoString(pokedex[i].typeMain) << " || " << convertTypetoString(pokedex[i].typeSub) << endl;
            cout << "Gender: " << convertGendertoString(pokedex[i].gender) << endl;
            cout << "Height: " << pokedex[i].height << " || ";
            cout << "Weight: " << pokedex[i].weight << endl;
            cout << "Evolution Stage: " << pokedex[i].evolutionStage << endl;
            if (pokedex[i].evolution != "None") {
                cout << "Evolves at level " << pokedex[i].evolutionLvl << " into " << pokedex[i].evolution << endl << endl;
            }
            else {
                cout << "Does not Evolve" << endl << endl;
            }
            return true;
        }
    }

    cerr << "Pokemon not found!" << endl;
    return false;
}

bool print_pokemon_by_number(const Pokedex& pokedex) {
    // Linear searches for the pokemons ID number and prints out the information upon finding it

    if (pokedex.size() == 0) { return false; }
    //Ask for name
    cout << "Printing Pokemon in order of National Dex ID..." << endl << endl;

    for (int i = 0; i < pokedex.size(); i++) {
        printf("#%03d\t", pokedex[i].ID);
        cout << left << setw(11) << pokedex[i].name << '\t';
        cout << setw(8) << convertTypetoString(pokedex[i].typeMain) << " || " << setw(8) << convertTypetoString(pokedex[i].typeSub) << '\t';
        if (pokedex[i].evolution != "None") {
            cout << "Evolves at level " << pokedex[i].evolutionLvl << " into " << pokedex[i].evolution << endl;
        }
        else {
            cout << "Does not Evolve" << endl;
        }
    }
    return true;
}

bool print_pokemon_by_type(const Pokedex& pokedex) {
    // Linear searches the vector to find the inputted Pokemon and then prints out the information found
    int IO = 0; //used to upper case the first character of the input
    int pokemonFound = 0;
    Type givenType = Type::Error;

    while (givenType == Type::Error) {
        IO = 0;
        //Ask for type
        cout << "Enter a type of pokemon" << endl;
        string input = "";
        cin >> input;

        //make input lowercase
        for (auto& p : input) {
            if (IO == 1) { // lower case all non starting characters
                p = tolower(p);
            }
            else { // capitalize starting character
                p = toupper(p);
                IO = 1;
            }
        }

        givenType = convertStringtoType(input);
        if (givenType == Type::Error) {
            cout << "Please enter one of the 18 pokemon types (caps do not matter)." << endl << endl;
        }
    }
    system("cls");
    cout << "Searching for " << convertTypetoString(givenType) << "..." << endl << endl;

    for (int i = 0; i < pokedex.size(); i++) {
        if (givenType == pokedex[i].typeMain || givenType == pokedex[i].typeSub) {
            printf("#%03d\t", pokedex[i].ID);
            cout << left << setw(11) << pokedex[i].name << '\t';
            cout << setw(8) << convertTypetoString(pokedex[i].typeMain) << " || " << setw(8) << convertTypetoString(pokedex[i].typeSub) << '\t';
            if (pokedex[i].evolution != "None") {
                cout << "Evolves at level " << pokedex[i].evolutionLvl << " into " << pokedex[i].evolution << endl;
            }
            else {
                cout << "Does not Evolve" << endl;
            }
            pokemonFound++;
        }
    }
    if (pokemonFound > 0) {
        cout << endl << pokemonFound << " Pokemon found." << endl << endl;
        return true;
    }
    return false;
}

vector<Pokemon> read_pokemons_from_file(const string& fileName) {
    //Reads Pokemon.txt and gathers the information into a vector
    Pokedex pokedex;
    string line;
    ifstream entries("Pokemon.txt");
    char delimit = '\t';
    vector <string> information;
    Type main, secondary;
    Gender gender;
    int pos = 0, i = 0;

    if (entries.is_open()) {
        while (getline(entries, line)) {
            if (line[0] == '\t') { continue; }
            information.clear();
            while ((pos = line.find(delimit)) != string::npos) {
                information.push_back(line.substr(0, pos)); // store string into array
                line.erase(0, pos + 1); // remove portion from source string along with the \t
            }
            information.push_back(line.substr(0, pos)); // store string into array
            main = convertStringtoType(information[1]);
            secondary = convertStringtoType(information[2]);
            gender = convertStringtoGender(information[5]);
            pokedex.push_back(Pokemon(information[0], main, secondary, stod(information[3]), stod(information[4]), gender, information[9], stoi(information[6]), stoi(information[7]), stoi(information[8])));
        }
        entries.close();
    }
    else { cout << "Unable to open file\n"; }

    return pokedex;
}

Type convertStringtoType(string value) {
    //Converts a given string into its equivalent Type member (or error if no equivalents)
    unordered_map<string, Type> const table = {
        {"None",Type::None}, {"Normal",Type::Normal}, {"Fire",Type::Fire}, {"Water",Type::Water}, {"Grass",Type::Grass}, {"Electric",Type::Electric},
        {"Ground",Type::Ground}, {"Rock",Type::Rock}, {"Steel",Type::Steel}, {"Bug",Type::Bug}, {"Flying",Type::Flying}, {"Fairy",Type::Fairy},
        {"Dragon",Type::Dragon}, {"Dark",Type::Dark}, {"Psychic",Type::Psychic}, {"Ghost",Type::Ghost}, {"Poison",Type::Poison}, {"Ice",Type::Ice},
        {"Fighting",Type::Fighting},
        {"Error",Type::Error}
    };
    auto it = table.find(value); // scan the 1st column of the unordered map
    if (it != table.end()) {
        return it->second; // return the second column
    }
    return Type::Error;
}

string convertTypetoString(Type value) {
    //Converts a given Type member into its equivalent string (or error if no equivalents)
    unordered_map<Type, string> const table = {
        {Type::None, "None"}, {Type::Normal, "Normal"}, {Type::Fire, "Fire"}, {Type::Water, "Water"}, {Type::Grass, "Grass"}, {Type::Electric, "Electric"},
        {Type::Ground, "Ground"}, {Type::Rock, "Rock"}, {Type::Steel, "Steel"}, {Type::Bug,"Bug"}, {Type::Flying, "Flying"}, {Type::Fairy, "Fairy"},
        {Type::Dragon, "Dragon"}, {Type::Dark, "Dark"}, {Type::Psychic, "Psychic"}, {Type::Ghost, "Ghost"}, {Type::Poison, "Poison"}, {Type::Ice, "Ice"},
        {Type::Fighting, "Fighting"}, {Type::Error, "Error"}
    };
    auto it = table.find(value);
    if (it != table.end()) {
        return it->second;
    }
    return "Error";
}


Gender convertStringtoGender(string value) {
    //Converts a given string into its equivalent Gender member (or error if no equivalents)
    unordered_map<string, Gender> const table = { 
        {"Both", Gender::Both}, {"None", Gender::NA}, {"Female", Gender::Female}, {"Male", Gender::Male}, {"Error", Gender::Error}
    };

    auto it = table.find(value);
    if (it != table.end()) {
        return it->second;
    }
    return Gender::Error;
}

string convertGendertoString(Gender value) {
    //Converts a given Gender member into its equivalent string (or error if no equivalents)
    unordered_map<Gender, string> const table = {
        {Gender::Both, "Both"}, {Gender::NA, "None"}, {Gender::Female, "Female"}, {Gender::Male, "Male"}, {Gender::Error, "Error"},
    };
    auto it = table.find(value);
    if (it != table.end()) {
        return it->second;
    }
    return "Error";
}

