#ifndef PROFESSOR_HEADER
#define PROFESSOR_HEADER

#include <Course.h>
#include <Person.h>
#include <iostream>
#include <string>
#include <vector>

class Professor : public Person {

  std::vector<Course *>
      Courses; // the vector contains the courses that the professor teaches

public:
  // constructors
  Professor();
  Professor(std::string, std::string, int, std::string);
  Professor(std::string, std::string, int, std::string, std::vector<Course *>);

  // destructor
  ~Professor();

  // set and get function
  void SetCourses(Course *); // Two set courses functions one to delete a course
                             // and one to add
  std::vector<Course *> GetCourses(void) const;

  // overload functions of the operators
  void operator=(const Professor &P);
  friend std::istream &operator>>(std::istream &str, Professor *P);

  // functions with different operations
  void RemoveCourse(std::string);
  void RemoveAllCourses(void);
  void PrintStats(void);
};
#endif