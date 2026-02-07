#include <Person.h>
#include <iostream>

Person ::Person(std::string Name, Gender Sex, uint8_t Age, std::string Email)
    : Name(std::move(Name)), Sex(Sex), Age(Age), Email(std::move(Email)) {}

// Set functions for the private members of the class Person
void Person::setAge(uint8_t Age) { this->Age = Age; }

void Person ::setSex(Gender Sex) { this->Sex = Sex; }

void Person ::setName(std::string Name) { this->Name = std::move(Name); }

void Person ::setEmail(std::string Email) { this->Email = std::move(Email); }

// Get functions for the private members of the class Person
uint8_t Person::getAge(void) const { return Age; }

Gender Person ::getSex(void) const { return Sex; }

const std::string &Person ::getName(void) const { return Name; }

const std::string &Person ::getEmail(void) const { return Email; }

// Functions for the counter
void Person ::printCount() const {
  std::cout << get_count() << " are either staff or students in the system." << std::endl;
}