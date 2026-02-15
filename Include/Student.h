#ifndef STUDENT_HEADER
#define STUDENT_HEADER

#include <Course.h>
#include <Person.h>
#include <StudManager.h>
#include <cmath>
#include <ranges>
#include <unordered_map>
#include <vector>
#include <concepts>
#include <type_traits>
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
  template <typename T1, typename T2>
  requires(!std::is_same_v<std::remove_cvref_t<T1>, Student>)
  Student(T1&& Name, int Age, T2&& Email, Gender Sex, int ID,
          int Semester)
      : Person(std::forward<T1>(Name), Sex, Age, std::forward<T2>(Email)), ID(ID),
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
  void enrollCourse(int courseID);
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