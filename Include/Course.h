#ifndef COURSE_HEADER
#define COURSE_HEADER

#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <span>

// Change it so we can't make changes here, Registry handles assigning a professor, 
class Course {
  std::string Name;
  int CourseID;
  int Semester;
  int ECTS;
  bool Mandatory;  // if the course is mandatory or a course of choise
  int AssignedProfessorID; // the professor who teaches the course
  // Private constructors, only the registry can create a course 
  std::set<int> EnrolledStudents;
  Course(std::string Name, int CourseID, int Semester, int ECTS, bool Mandatory, int ProfessorID) : Name(std::move(Name)), CourseID(CourseID), Semester(Semester), ECTS(ECTS), Mandatory(Mandatory), AssignedProfessorID(ProfessorID) {}

  // set functions
  void setSemester(int Semester) { this->Semester = Semester; }
  void setName(std::string Name) { this->Name = std::move(Name); }
  void setECTS(int ECTS) { this->ECTS = ECTS; }
  void setMandatory(bool Mandatory) { this->Mandatory = Mandatory; }
  // TODO: Pottentially add exception handling here in case student is already enrolled, for now we ignore
  // but we might want to alert the end use later 
  void enrollStudent(int StudentID) { EnrolledStudents.insert(StudentID); }

public:
  // destructor will probably handle updating the db as well, better to seperate the work rather than have one huge monolithic function
  ~Course();
  // get functions
  const std::string& getName(void) const { return Name; }

  int getSemester(void) const { return Semester; }

  int getECTS(void) const { return ECTS; }

  bool getMandatory(void) const { return Mandatory; }

  int getAssignedProfessor(void) const { return AssignedProfessorID; }

  const std::set<int>& getEnrolledStudents(void) const { return EnrolledStudents; }

  // FIXME: We should first refactor the professor class and then implement this method
  // const Professor *getProfessor(void) const;
  operator int(){ return CourseID; } 

  // Delete copy constructor and assignment, we do not want multiple copies of this object
  Course(const Course &C) = delete;
  void operator=(const Course &C) = delete;
  // Secretary will handle enrolling students
  friend class Secretary;
};
#endif