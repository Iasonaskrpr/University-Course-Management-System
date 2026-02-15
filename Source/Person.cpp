#include <Person.h>
#include <iostream>
// pure vitual destructor
Person ::~Person() {}

// Set functions for the private members of the class Person
void Person::setAge(int Age) { this->Age = Age; }

void Person ::setSex(Gender Sex) { this->Sex = Sex; }

void Person ::setName(std::string Name) { this->Name = std::move(Name); }

void Person ::setEmail(std::string Email) { this->Email = std::move(Email); }

// Get functions for the private members of the class Person
int Person::getAge(void) const { return Age; }

Gender Person ::getSex(void) const { return Sex; }

const std::string &Person ::getName(void) const { return Name; }

const std::string &Person ::getEmail(void) const { return Email; }

// Functions for the counter
void Person ::printCount() const {
  std::cout << "We have this ammount of people: " << get_count() << std::endl;
}