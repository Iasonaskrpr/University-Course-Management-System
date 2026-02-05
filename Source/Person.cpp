#include <Person.h>
#include <iostream>

// constructors
Person::Person() : Name(std::string{}), Sex(Gender::Unspecified), age(-1), email(std::string{}) {
}

Person ::Person(const std::string& Name, Gender Sex, int age, const std::string& email) : Name(Name), Sex(Sex), age(age), email(email) {
}

// pure vitual destructor
Person ::~Person() {}

// Set functions for the private members of the class Person
void Person::SetAge(int age) { this->age = age; }

void Person ::SetSex(Gender Sex) { this->Sex = Sex; }

void Person ::SetName(const std::string& Name) { this->Name = Name; }

void Person ::Setemail(const std::string& email) { this->email = email; }

// Get functions for the private members of the class Person
int Person::GetAge(void) const { return age; }

Gender Person ::GetSex(void) const { return Sex; }

const std::string& Person ::GetName(void) const { return Name; }

const std::string& Person ::Getemail(void) const { return email; }

// Functions for the counter
void Person ::printCount() const {
  std::cout << "We have this ammount of people: " << get_count() << std::endl;
}