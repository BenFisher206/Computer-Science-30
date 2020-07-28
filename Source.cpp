#include "People.h"

int main() {
	Student* student1 = new Student("Lucy", "123 Ave", "555-5555", 12, 1);
	Student* student2 = new Student("Ben", "456 Ave", "777-7777", 11, 2);

	Guardian* guard1 = new Guardian("David", "789 Ave", "333-3333", true);
	Guardian* guard2 = new Guardian("Becky", "123 Street", "444-4444", false);

	Teacher* teach1 = new Teacher("Francis", "456 Street", "222-2222", "Math");
	Teacher* teach2 = new Teacher("Jane", "789 Street", "888-8888", "Science");

	student1->printCallingInfo();
	guard1->printAllInfo();
	teach2->printAllInfo();

	student1->advanceGrade();
	teach2->reassign("English");
	teach2->printAllInfo();

	return 1;
}