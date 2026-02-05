#ifndef PERSON_HEADER
#define PERSON_HEADER

#include "Counter.h"
#include <string>

enum class Gender {
  Unspecified = 0,
  Male,
  Female,
  Other
};

// We use CRTP to keep a counter on the total instances of Person
class Person : public Counter<Person> {

protected:
  std::string Name;
  Gender Sex;
  int Age;
  std::string Email;

public:
  // constructors
  Person();
  Person(const std::string Name, Gender Sex, int Age, const std::string Email);

  // destructor
  // If you intend Person to be abstract, a pure virtual destructor is fine,
  // but it still needs an out-of-line definition.
  virtual ~Person() = 0;

  // we need set functions (members are protected)
  void setAge(int Age);
  void setSex(Gender Sex);
  void setName(std::string Name);
  void setEmail(std::string Email);

  // we need get functions (members are protected)
  const std::string& getEmail() const;
  int getAge() const;
  Gender getSex() const;
  const std::string& getName() const;

  // Functions for the counter
  void printCount() const;
};

// Definition for the (pure) virtual destructor to satisfy the linker.
inline Person::~Person() {}

#endif