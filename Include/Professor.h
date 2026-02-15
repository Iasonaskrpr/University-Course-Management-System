#ifndef PROFESSOR_HEADER
#define PROFESSOR_HEADER

#include <Course.h>
#include <Person.h>
#include <iostream>
#include <string>
#include <vector>
#include <span>
#include <algorithm>

class Course;

class Professor : public Person {
  id_t ProfessorID;
  std::vector<int> AssignedCourses; // a vector of course IDs that the professor is assigned to teach
  Professor(std::string Name, std::string email, uint8_t age,
                        Gender Sex, id_t ProfessorID)
      : Person(Name, Sex, age, email), ProfessorID(ProfessorID) {}

  Professor(std::string Name, std::string email, uint8_t age,
                        Gender Sex, id_t ProfessorID, std::vector<int> Courses)
      : Person(Name, Sex, age, email), ProfessorID(ProfessorID), AssignedCourses(std::move(Courses)) {}
  void removeCourse(id_t courseID);
  void RemoveAllCourses(void);
  void setCourses(std::vector<int> courses) { AssignedCourses = std::move(courses); }
  void addCourse(int courseID) { AssignedCourses.push_back(courseID); }
  
public:
  // destructor
  ~Professor(){}
  Professor(const Professor &) = delete;
  Professor &operator=(const Professor &) = delete;
  Professor(Professor &&) = delete;
  Professor &operator=(Professor &&) = delete;
  std::span<const int> GetCourses(void) const { return AssignedCourses; }
  void printStats(void);
};
#endif