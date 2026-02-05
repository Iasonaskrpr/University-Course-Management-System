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
  int age;
  std::string email;

public:
  // constructors
  Person();
  Person(const std::string& name, Gender sex, int age, const std::string& email);

  // destructor
  // If you intend Person to be abstract, a pure virtual destructor is fine,
  // but it still needs an out-of-line definition.
  virtual ~Person() = 0;

  // we need set functions (members are protected)
  void SetAge(int age);
  void SetSex(Gender sex);
  void SetName(const std::string& name);
  void Setemail(const std::string& email);

  // we need get functions (members are protected)
  const std::string& Getemail() const;
  int GetAge() const;
  Gender GetSex() const;
  const std::string& GetName() const;

  // Functions for the counter
  void printCount() const;
};

// Definition for the (pure) virtual destructor to satisfy the linker.
inline Person::~Person() {}

#endif