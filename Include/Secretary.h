#ifndef SECRETARY_HEADER
#define SECRETARY_HEADER

#include <Course.h>
#include <Professor.h>
#include <Student.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Secretary {
  Secretary();
  std::unordered_map<int, std::shared_ptr<Student>>
      Students; // Mapping of student ID to Student object
  std::unordered_map<int, std::shared_ptr<Professor>>
      Professors; // Mapping of professor ID to Professor object
  std::unordered_map<int, std::shared_ptr<Course>>
      Courses;        // Mapping of course ID to Course object
  int MandatoryCount;            // the number of the mandatory courses
public:
  // This is the static method that controls the access to the singleton
  // instance
  static Secretary &getInstance() {
    static Secretary instance; 
    return instance;
  }

  // Delete copy and assignment constructor to avoid creation of multiple Secretary instances
  Secretary(const Secretary &S) = delete;
  void operator=(const Secretary &S) = delete;

  // set and get function
  void SetMandatoryCount(int);
  int GetMandatoryCount(void) const;

  // Overload fuctions of the operators
  void operator+(Student *S);
  void operator+(Professor *P);
  void operator+(Course *C);

  // finds the object based on its name
  std::shared_ptr<Course> FindCourse(int);
  std::shared_ptr<Professor> FindProf(int);
  std::shared_ptr<Student> FindStud(int);

  // delete functions
  void DeleteStud(int);
  void DeleteProf(int);
  void DeleteCourse(int);

  // returns a vector with all the students that can get a degree
  std::vector<Student *> Degree(void);

  // functions with different operations
  void PrintStats(const std::string&);
  bool RegisterStudent(const std::string &, const std::string &);
  bool AssignProf(const std::string &, const std::string &);
  void PassCourse(Student *, Course *, float);
  void PrintDetailedSemester(const std::string &, int);
  void PrintDetailedYear(const std::string &, int);
  void StartSemester(void);
  void EndSemester(void);

  // function that update files
  void printfiles(void);
};
#endif