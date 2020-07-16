# include <string>

#pragma once
enum class Type {
	None = 0,
	Normal = 1,
	Fire = 2,
	Water = 3,
	Grass = 4,
	Electric = 5,
	Ground = 6,
	Rock = 7,
	Steel = 8,
	Bug = 9,
	Flying = 10,
	Fairy = 11,
	Dragon = 12,
	Dark = 13,
	Psychic = 14,
	Ghost = 15,
	Fighting = 16,
	Poison = 17,
	Ice = 18,
	Error = 19
};

enum class Gender {
	NA = 0,
	Male = 1,
	Female = 2,
	Both = 3,
	Error = 4
	
};

class Pokemon {
	public:
		std::string name;
		Type typeMain;
		Type typeSub;
		double weight;
		double height;
		Gender gender;
		std::string evolution;
		int evolutionLvl;
		int evolutionStage;
		int ID;




		Pokemon(std::string name, Type typeMain, Type typeSub, double weight, double height, Gender gender, std::string evolution, int evolutionLvl, int evolutionStage, int ID) {
			this->name = name;
			this->typeMain = typeMain;
			this->typeSub = typeSub;
			this->weight = weight;
			this->height = height;
			this->gender = gender;
			this->evolution = evolution;
			this->evolutionLvl = evolutionLvl;
			this->evolutionStage = evolutionStage;
			this->ID = ID;
		}
};