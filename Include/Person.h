#ifndef PERSON_HEADER
#define PERSON_HEADER
#include "Counter.h"
#include <string>

// We use CRTP to keep a counter on the total instances of Person
class Person : public Counter<Person> {

protected:
  std::string Name;
  std::string Sex;
  int age;
  std::string email;

public:
  // constructors
  Person();
  Person(std::string, std::string, int, std::string);

  // destructor
  virtual ~Person() = 0;

  // we need set functions because the members of the class are private
  void SetAge(int age);
  void SetSex(std::string Sex);
  void SetName(std::string Name);
  void Setemail(std::string email);

  // we need get functions because the members of the class are private
  std::string Getemail(void) const;
  int GetAge(void) const;
  std::string GetSex(void) const;
  std::string GetName(void) const;

  // Functions for the counter
  void printCount();
  void decreaseCount();
};
#endif