#ifndef STUDENT_HEADER
#define STUDENT_HEADER

#include <Course.h>
#include <Person.h>
#include <unordered_map>
#include <vector>
#include <StudManager.h>

class StudManager;

class Student : public Person {
  int total_ects;
  std::string AM;
  int semester;
   
   //FIXME: These should also be moved to the student manager
  // A mapping of Course ID to a pair of (grade, semester)
  std::unordered_map<int, std::pair<float, int>>
      PassedCourses; // the map contains the courses that the student passed
                     // with the grade
  std::vector<Course *>
      Courses; // the vector contains  the courses that the student enrolled
  int countMandatory = 0; // counts the madatory courses that he passed
public:
  // constructors
  Student();
  Student(const std::string&,const int, const std::string&, const std::string&,const std::string&, int);

  // destructor
  ~Student();

  // set functions
  // FIXME: This should be moved to student manager class, as the semester
  // should be updated by the secretary when the semester ends, not by the
  // student itself
  void SetSemester(int);
  void SetAM(std::string);
  void SetECTS(int);

  // get functions
  int GetECTS(void) const;
  std::string GetAM(void) const;
  int GetSemester(void) const;
  int GetMandatoryCount(void) const;
  // FIXME: Return const reference to avoid unnecessary copying of the vector
  // and to prevent modification of the internal state of the student, also make
  // Course shared ptr to avoid dangling pointers   

  std::vector<Course *>
  GetSubjects(void) const; // returns the vector with courses he enrolled


  // update functions
  void UpdateECTS(Course); // overflow operand +=
  void UpdateCourse(Course *, float);

  // functions with different operations
  // FIXME: This should be moved to the student manager class, as the secretary
  // should be responsible for assigning courses to students, not the students
  // themselves
  void AssignCourse(Course *);
  void PrintSemester(int);
  void PrintYear(int);

  // functions that helps with the update of the files
  // FIXME: Remove this and put in manager, these are to be in sql
  std::vector<std::string> getnamemap(void);
  std::vector<float> getgrademap(void);
  friend class StudManager;
};
#endif