#include <Person.h>

// constructors
Person::Person() {
  Name = "undefined";
  Sex = "Undefined";
  age = 0;
  email = "undefined";
}

Person ::Person(std::string Name, std::string Sex, int age, std::string email) {
  this->Name = Name;
  this->age = age;
  this->email = email;
  this->Sex = Sex;
}

// pure vitual destructor
Person ::~Person() {}

// Set functions for the private members of the class Person
void Person::SetAge(int age) { this->age = age; }

void Person ::SetSex(std::string Sex) { this->Sex = Sex; }

void Person ::SetName(std::string Name) { this->Name = Name; }

void Person ::Setemail(std::string email) { this->email = email; }

// Get functions for the private members of the class Person
int Person::GetAge(void) const { return age; }

std::string Person ::GetSex(void) const { return Sex; }

std::string Person ::GetName(void) const { return Name; }

std::string Person ::Getemail(void) const { return email; }

// Functions for the counter
void Person ::printCount() {
  cout << "We have this ammount of people: " << get_count() << endl;
}

void Person ::decreaseCount() { count--; }