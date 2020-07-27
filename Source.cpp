// This program is a text based arena which allows you to create a character from 4 different races: Human, Elf, Dwarf, Demon
// Then you can choose between 4 different classes: Paladin, Mage, Ranger, Rogue
// Humans have all around stats but slightly lower wisdom and constitution
// Elves have high intelligence and wisdom and charisma but lower strength and constitution
// Dwarves have high strength, intelligence, and constitution with lower dexterity and wisdom
// Demons have high wisdom, dexterity, and strength but extremely low charisma and constitution

# include "Characters.h" // Includes String and Iostream

using namespace std;

int main() {

	//Helper & buffer variables
	string name;
	bool inputAccepted = false;
	int IO = 0;

	// Race classes
	Human *human = NULL;
	Elf *elf = NULL;
	Dwarf *dwarf = NULL;
	Demon *demon = NULL;
	
	// Role classes
	Paladin* paladin = NULL;
	Mage* mage = NULL;
	Ranger* ranger = NULL;
	Rogue* rogue = NULL;



	while (!inputAccepted) {
		string race;
		cout << "What Race do you wish your character to be?" << endl;
		cout << "Human | Elf | Dwarf | Demon" << endl;
		cin >> race;
		
		//make input lowercase
		for (auto& p : race) {	p = tolower(p);	}
		
		// determine if a correct race was given
		if (race == "human" || race == "elf" || race == "dwarf" || race == "demon"){ 
			if (race == "human") { human = new Human; }
			else if (race == "elf") { elf = new Elf; }
			else if (race == "dwarf") { dwarf= new Dwarf; }
			else if (race == "demon") { demon = new Demon; }
			inputAccepted = true;
			system("cls");
			cout << "What do you wish to name your " << race << "?" << endl;
		}
		else { system("cls"); cout << "Invalid Race" << endl; }
	}
	cin >> name;
	IO = 0;
	//make input lowercase
	for (auto& p : name) {
		if (IO == 1) { // lower case all non starting characters
			p = tolower(p);
		}
		else { // capitalize starting character
			p = toupper(p);
			IO = 1;
		}
	}
	if (human) { human->updateName(name); }
	else if (elf) { elf->updateName(name); }
	else if (dwarf) { dwarf->updateName(name); }
	else if (demon) { demon->updateName(name); }

	inputAccepted = false;
	system("cls");
	while (!inputAccepted) {
		string role;
		cout << "What Role do you wish " << name << " to be?" << endl;
		cout << "Paladin | Mage | Ranger | Rogue" << endl;
		cin >> role;
		//make input lowercase
		for (auto& p : role) { p = tolower(p); }
		if (role == "paladin" || role == "mage" || role == "ranger" || role == "rogue") { 
			if (role == "paladin") { paladin = new Paladin; }
			else if (role == "mage") { mage = new Mage; }
			else if (role == "ranger") { ranger = new Ranger; }
			else if (role == "rogue") { rogue = new Rogue; }
			inputAccepted = true; 
		}
		else { system("cls"); cout << "Invalid Role" << endl; }
	}

	system("cls");
	inputAccepted = false;
	while (!inputAccepted) {
		int option = 0;
		cout << "The possible actions you can take are:" << endl;
		cout << "1. Check stats" << endl;
//		cout << "2. Upgrade stats" << endl; //Removed for now as code will require too many if else statements
		cout << "2. Speak" << endl;
		//cout << "3. Fight" << endl;
		cin >> option;
		if (option == 1 || option == 2) {
			if (option == 1) {
				system("cls");
				if (human) { human->printStats(); }
				else if (elf) { elf->printStats(); }
				else if (dwarf) { dwarf->printStats(); }
				else if (demon) { demon->printStats(); }
				inputAccepted = true;
			}
			/*			else if (option == 2) {
							system("cls");
							cout << "Which stat would you like to upgrade?"
							if (human) { human->Character::printStats(); }
							else if (elf) { elf->Character::printStats(); }
							else if (dwarf) { dwarf->Character::printStats(); }
							else if (demon) { demon->Character::printStats(); }
							inputAccepted = true;
						}
			//*/
			else if (option == 2) {
				system("cls");
				if (human) { human->speak(); }
				else if (elf) { elf->speak(); }
				else if (dwarf) { dwarf->speak(); }
				else if (demon) { demon->speak(); }
				inputAccepted = true;
			}
		/*	else if (option == 3) {
				system("cls");
				if (human) { human->printStats(); }
				else if (elf) { elf->printStats(); }
				else if (dwarf) { dwarf->printStats(); }
				else if (demon) { demon->printStats(); }
				inputAccepted = true;
			}
		//*/
			char retry = NULL;
			while (1) {
				cout << endl << "Would you like to choose another option? (Y/N)" << endl;
				cin >> retry;
				if (tolower(retry) == 'y') { inputAccepted = false; break;  }
				else if (tolower(retry) == 'n') { return 1; }
				else { system("cls"); cout << "Invalid input" << endl; }
			}
		}
		else {
			system("cls");
			cout << "Invalid input!" << endl;
		}
	}

	return 1;
}

