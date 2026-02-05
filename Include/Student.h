#ifndef STUDENT_HEADER
#define STUDENT_HEADER

#include <Course.h>
#include <Person.h>
#include <unordered_map>
#include <vector>
#include <StudManager.h>

class StudManager;

class Student : public Person {
  int AccumulatedECTS = 0;
  std::string AM {
    "0000000"};
  // MOVE TO STUDMANAGER
  int Semester = 1;
  // MOVE TO STUDMANAGER
  int PassedMandatorySubjects = 0;
   //FIXME: These should also be moved to the student manager
  // A mapping of Course ID to a pair of (grade, semester)
  std::unordered_map<int, std::pair<float, int>>
      PassedCourses; // the map contains the courses that the student passed
                     // with the grade
   
  std::vector<std::shared_ptr<Course>>
      Courses; // the vector contains  the courses that the student enrolled
   // counts the madatory courses that he passed
public:
  // constructors
  Student ::Student() : Person() {}
  Student ::Student(std::string Name, int Age, std::string Email, Gender Sex,
                    std::string AM, int Semester)
      : Person(std::move(Name), Sex, Age, std::move(Email)), AM(AM),
        Semester(Semester) {}
  // destructor
  ~Student() = default;
  // TODO: Handle Copy constructors and move semantics

  // set functions
  // FIXME: This should be moved to student manager class, as the semester
  // should be updated by the secretary when the semester ends, not by the
  // student itself
  void setSemester(int Semester);
  void setAM(std::string AM);
  //MOVE TO STUDMANAGER void setECTS(int ECTS);

  // get functions
  int getECTS(void) const;
  const std::string& getAM(void) const;
  int getSemester(void) const;
  int getPassedMandatory(void) const;
  // FIXME: Return const reference to avoid unnecessary copying of the vector
  // and to prevent modification of the internal state of the student, also make
  // Course shared ptr to avoid dangling pointers   

  const std::vector<std::shared_ptr<Course>> &
  getSubjects(void) const; // returns the vector with courses he enrolled

   // TODO: Move these to StudManager
  // update functions
  //void updateECTS(Course); // overflow operand +=
  //void updateCourse(Course *, float);

  // functions with different operations
  // FIXME: This should be moved to the student manager class, as the secretary
  // should be responsible for assigning courses to students, not the students
  // themselves
  //void AssignCourse(Course *);
  //void PrintSemester(int);
  //void PrintYear(int);

  // functions that helps with the update of the files
  // FIXME: Remove this and put in manager, these are to be in sql
  //std::vector<std::string> getnamemap(void);
  //std::vector<float> getgrademap(void);
  friend class StudManager;
};
#endif