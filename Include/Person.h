#ifndef PERSON_HEADER
#define PERSON_HEADER

#include "Counter.h"
#include <string>

enum class Gender { Unspecified = 0, Male, Female, Other };

// We use CRTP to keep a counter on the total instances of Person
class Person : public Counter<Person> {

protected:
  std::string Name;
  Gender Sex;
  uint8_t Age;
  std::string Email;
  // constructors
  template <typename T1, typename T2>
  requires(!std::is_same_v<std::remove_cvref_t<T1>, Person>)
  Person(T1&& Name, Gender Sex, uint8_t Age, T2&& Email) 
	  : Name(std::forward<T1>(Name)), Sex(Sex), Age(Age), Email(std::forward<T2>(Email)) {}

public:
  // constructors
  Person(std::string Name, Gender Sex, uint8_t Age, std::string Email);

  // destructor
  // If you intend Person to be abstract, a pure virtual destructor is fine,
  // but it still needs an out-of-line definition.
  virtual ~Person() = 0;

  // we need set functions (members are protected)
  void setAge(uint8_t Age);
  void setSex(Gender Sex);
  void setName(std::string Name);
  void setEmail(std::string Email);

  // we need get functions (members are protected)
  const std::string &getEmail() const;
  uint8_t getAge() const;
  Gender getSex() const;
  const std::string &getName() const;

  // Functions for the counter
  void printCount() const;
};
#endif