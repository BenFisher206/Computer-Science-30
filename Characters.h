#include <iostream>
#include <string>

class Character {
public:
	std::string name = "";
	int strength = 0;
	int dexterity = 0;
	int constitution = 0;
	int intelligence = 0;
	int wisdom = 0;
	int charisma = 0;
	int level = 1;

	Character() {};

	// Update information
	void updateName(std::string name) { this->name = name; }
	void updateStrength(int n) { strength += n; }
	void updateDexterity(int n) { dexterity += n; }
	void updateConstitution(int n) { constitution += n; }
	void updateIntelligence(int n) { intelligence += n; }
	void updateWisdom(int n) { wisdom += n; }
	void updateCharisma(int n) { charisma += n; }
	void updateLevel(int n) { level += n; }

	void printStats() {
		std::cout << "Name: " << name << std::endl;
		std::cout << "Level " << level << std::endl;
		std::cout << "Strenght: " << strength << std::endl;
		std::cout << "Dexterity: " << dexterity << std::endl;
		std::cout << "Constitution: " << constitution << std::endl;
		std::cout << "Intelligence: " << intelligence << std::endl;
		std::cout << "Wisdom: " << wisdom << std::endl;
		std::cout << "Charisma: " << charisma << std::endl;
	}
};

// ---------------------------------------
// ---------------------------------------
// ------------- Races -------------------
// ---------------------------------------
// ---------------------------------------

class Human : public Character {
public:

	Human() {
		strength++;
		dexterity++;
		intelligence++;
		charisma++;
	}

	void speak() {
		std::cout << "Hello!" << std::endl;
	}

};

class Elf : public Character {
public:

	Elf() {
		intelligence += 2;
		wisdom += 2;
		charisma++;
		strength--;
		constitution--;
	}

	void speak() {
		std::cout << "Leave me alone..." << std::endl;
	}

};

class Dwarf : public Character {
public:

	Dwarf() {
		strength+=2;
		dexterity--;
		intelligence++;
		constitution+=2;
		wisdom--;
	}

	void speak() {
		std::cout << "Cheers!" << std::endl;
	}

};

class Demon : public Character {
public:

	Demon() {
		strength += 3;
		dexterity += 3;
		wisdom += 3;
		charisma -= 3;
		constitution -= 2;
	}

	void speak() {
		std::cout << "Die!" << std::endl;
	}

};

// ---------------------------------------
// ---------------------------------------
// ------------- Roles -------------------
// ---------------------------------------
// ---------------------------------------

class Paladin{
public:

	Paladin() {}
};

class Mage {
public:

	Mage() {}
};

class Ranger {
public:

	Ranger() {}
};

class Rogue {
public:

	Rogue() {}
};
