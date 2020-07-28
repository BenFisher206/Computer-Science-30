#pragma once
#include <string>
#include <iostream>

//Base Parent Class
class Person {
public:
	std::string name;
	std::string address;
	std::string phoneNumber;

	Person() {}

	Person(std::string name, std::string address, std::string phoneNumber) {
		this->name = name;
		this->address = address;
		this->phoneNumber = phoneNumber;
	}

	void printCallingInfo() {
		std::cout << "\nName: " << name << std::endl;
		std::cout << "Phone #: " << phoneNumber << std::endl;
	}

	void printAllInfo() {
		std::cout << "\nName: " << name << std::endl;
		std::cout << "Address: " << address << std::endl;
		std::cout << "Phone #: " << phoneNumber << std::endl;
	}
};



// Child Classes

class Student : public Person {
public:
	int grade = 0;
	int id = 0;

	Student(std::string name, std::string address, std::string phoneNumber, int grade, int id) : Person(name, address, phoneNumber) {
		this->grade = grade;
		this->id = id;
	}

	void printAllInfo() {
		Person::printAllInfo();
		std::cout << "Grade: " << grade << std::endl;
		std::cout << "ID #: " << id << std::endl;
	}

	void advanceGrade() {
		grade++;
		if (grade > 12) {
			std::cout << "\nName: " << name << std::endl;
			std::cout << "Graduated from High School." << std::endl;
		}
		else {
			std::cout << "\nName: " << name << std::endl;
			std::cout << "\nAdvanced to Grade " << grade << '.' << std::endl;
		}
	}
};




class Guardian : public Person {
public:
	bool registered;

	Guardian(std::string name, std::string address, std::string phoneNumber, bool registered) : Person(name, address, phoneNumber) {
		this->registered = registered;
	}

	void printAllInfo() {
		Person::printAllInfo();
		std::cout << "Registered: " << registered << std::endl;
	}
};





class Teacher : public Person {
public:
	std::string assignment;

	Teacher(std::string name, std::string address, std::string phoneNumber, std::string assignment) : Person(name, address, phoneNumber) {
		this->assignment = assignment;
	}

	void printAllInfo() {
		Person::printAllInfo();
		std::cout << "Assignment: " << assignment << std::endl;

	}

	void reassign(std::string assignment) {
		this->assignment = assignment;
		std::cout << "\nName: " << name << std::endl;
		std::cout << "Reassigned to: " << assignment << std::endl;
	}
};
