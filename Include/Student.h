#ifndef STUDENT_HEADER
#define STUDENT_HEADER

#include <Course.h>
#include <Grades.h>
#include <Person.h>
#include <unordered_map>
#include <vector>

class Student : public Person {
  int total_ects;
  std::string AM;
  int semester;

  std::unordered_map<std::string, Grades>
      PassedCourses; // the map contains the courses that the student passed
                     // with the grade
  std::vector<Course *>
      Courses; // the vector contains  the courses that the student enrolled
  int countMandatory = 0; // counts the madatory courses that he passed
public:
  // constructors
  Student();
  Student(std::string, int, std::string, std::string, std::string, int);

  // destructor
  ~Student();

  // set functions
  void SetSemester(int);
  void SetAM(std::string);
  void SetECTS(int);

  // get functions
  int GetECTS(void) const;
  std::string GetAM(void) const;
  int GetSemester(void) const;
  int GetMandatoryCount(void) const;
  std::vector<Course *>
  GetSubjects(void) const; // returns the vector with courses he enrolled

  // overload functions of the operators
  void operator=(const Student &S);
  friend std::istream &operator>>(std::istream &str, Student *S);

  // update functions
  void UpdateECTS(Course); // overflow operand +=
  void UpdateCourse(Course *, float);

  // functions with different operations
  void AssignCourse(Course *);
  void PrintSemester(int);
  void PrintYear(int);

  // functions that helps with the update of the files
  std::vector<std::string> getnamemap(void);
  std::vector<float> getgrademap(void);
};
#endif