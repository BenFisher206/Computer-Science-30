# include "pokemon.h"
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
string convertTypetoString(Type value);
string convertGendertoString(Gender value);

int main() {

    const auto pokedex = read_pokemons_from_file("Pokemon.txt");
    bool repeat = true;
    string input = "";

    //Ask the user which way they would like to search
    while (repeat) {
        cout << "Welcome to the Pokedex! We have the first " << pokedex.size() << " pokemon indexed!" << endl;
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
            print_pokemon_by_number(pokedex);
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

    for (int i = 0; i<pokedex.size(); i++) {
        if (input_name == pokedex[i].name) {
            cout << endl << endl << "#" << setfill('0') << setw(3) << pokedex[i].ID << endl << endl;
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
    return true;
}

vector<Pokemon> read_pokemons_from_file(const string& fileName) {
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
    std::unordered_map<std::string, Type> const table = { 
        {"None",Type::None}, {"Normal",Type::Normal}, {"Fire",Type::Fire}, {"Water",Type::Water}, {"Grass",Type::Grass}, {"Electric",Type::Electric}, 
        {"Ground",Type::Ground}, {"Rock",Type::Rock}, {"Steel",Type::Steel}, {"Bug",Type::Bug}, {"Flying",Type::Flying}, {"Fairy",Type::Fairy},
        {"Dragon",Type::Dragon}, {"Dark",Type::Dark}, {"Psychic",Type::Psychic}, {"Ghost",Type::Ghost}, {"Poison",Type::Poison}, {"Ice",Type::Ice}
    };
    auto it = table.find(value);
    if (it != table.end()) {
        return it->second;
    }
    return Type::Error;
}

string convertTypetoString(Type value) {
    unordered_map<Type, string> const table = {
        {Type::None, "None"}, {Type::Normal, "Normal"}, {Type::Fire, "Fire"}, {Type::Water, "Water"}, {Type::Grass, "Grass"}, {Type::Electric, "Electric"},
        {Type::Ground, "Ground"}, {Type::Rock, "Rock"}, {Type::Steel, "Steel"}, {Type::Bug,"Bug"}, {Type::Flying, "Flying"}, {Type::Fairy, "Fairy"},
        {Type::Dragon, "Dragon"}, {Type::Dark, "Dark"}, {Type::Psychic, "Psychic"}, {Type::Ghost, "Ghost"}, {Type::Poison, "Poison"}, {Type::Ice, "Ice"}
    };
    auto it = table.find(value);
    if (it != table.end()) {
        return it->second;
    }
    return "Error";
}


Gender convertStringtoGender(string value) {
    std::unordered_map<std::string, Gender> const table = { {"Both",Gender::Both}, {"None",Gender::NA}, {"Female",Gender::Female}, {"Male",Gender::Male} };
    auto it = table.find(value);
    if (it != table.end()) {
        return it->second;
    }
    return Gender::Error;
}

string convertGendertoString(Gender value) {
    unordered_map<Gender, string> const table = {
        {Gender::Both, "Both"}, {Gender::NA, "None"}, {Gender::Female, "Female"}, {Gender::Male, "Male"}
    };
    auto it = table.find(value);
    if (it != table.end()) {
        return it->second;
    }
    return "Error";
}

