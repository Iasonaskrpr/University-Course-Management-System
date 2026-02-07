#ifndef STUDENT_HEADER
#define STUDENT_HEADER

#include <Course.h>
#include <Person.h>
#include <StudManager.h>
#include <cmath>
#include <ranges>
#include <unordered_map>
#include <vector>
class StudManager;

class Student : public Person {
  int AccumulatedECTS{};
  int ID{};
  int Semester = 1;
  int PassedMandatorySubjects = 0;
  // A mapping of Course ID to a struct containing the grade, semester, and
  // status of the course for the student
  std::unordered_map<int, CourseRecord> Courses;

  // counts the madatory courses that he passed
  // Keep as private so only a manager can create a student, and the manager can
  // ensure that the ID is unique and properly assigned
  Student() : Person() {}
  Student(std::string Name, int Age, std::string Email, Gender Sex, int ID,
          int Semester)
      : Person(std::move(Name), Sex, Age, std::move(Email)), ID(ID),
        Semester(Semester) {}
  std::unordered_map<int, CourseRecord> &getCourses() { return Courses; }

public:
  // destructor
  ~Student() {}
  Student(const Student &) = delete;
  Student &operator=(const Student &) = delete;
  Student(Student &&) = delete;
  Student &operator=(Student &&) = delete;

  // get functions
  int getECTS(void) const;
  int getID(void) const;
  int getSemester(void) const;
  int getPassedMandatory(void) const;
  std::span<const CourseRecord> getCourses(int id, bool IncludeFailed = true,
                                           bool IncludePassed = true,
                                           bool IncludeCurrent = true) const;
  float calculateAverage() const;
  operator int() { return ID; }

  // functions with different operations
  // FIXME: These should change to conform to the new changes
  // void AssignCourse(Course *);
  // void PrintSemester(int);
  // void PrintYear(int);

  friend class StudManager;
};
#endif