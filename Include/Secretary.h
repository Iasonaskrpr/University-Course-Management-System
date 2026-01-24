#ifndef SECRETARY_HEADER
#define SECRETARY_HEADER

#include <Course.h>
#include <Professor.h>
#include <Student.h>
#include <iostream>
#include <string>
#include <vector>

class Secretary {

  std::vector<Student *> Students; // vector of all students in the university
  std::vector<Professor *>
      Professors;                // vector of all professors in the university
  std::vector<Course *> Courses; // vector of all courses in the university
  int MandatoryCount;            // the number of the mandatory courses
public:
  // constructor
  Secretary();

  // destructor
  ~Secretary();

  // copy constructor
  Secretary(const Secretary &S);

  // set and get function
  void SetMandatoryCount(int);
  int GetMandatoryCount(void) const;

  // Overload fuctions of the operators
  void operator+(Student *S);
  void operator+(Professor *P);
  void operator+(Course *C);
  void operator=(const Secretary &S);

  // finds the object based on its name
  Course *FindCourse(std::string);
  Professor *FindProf(std::string);
  Student *FindStud(std::string);

  // delete functions
  void DeleteStudent(std::string);
  void DeleteProf(std::string);
  void DeleteCourse(std::string);

  // returns a vector with all the students that can get a degree
  std::vector<Student *> Degree(void);

  // functions with different operations
  void PrintStats(std::string);
  bool RegisterStudent(std::string, std::string);
  bool AssignProf(std::string, std::string);
  void PassCourse(Student *, Course *, float);
  void PrintDetailedSemester(std::string, int);
  void PrintDetailedYear(std::string, int);
  void StartSemester(void);
  void EndSemester(void);

  // function that update files
  void printfiles(void);
};
#endif