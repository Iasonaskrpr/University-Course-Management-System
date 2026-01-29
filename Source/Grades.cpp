#include <Grades.h>

Grades::Grades() {
  semester = 0;
  grade = 0;
}
Grades::Grades(int semester, int grade) {
  this->semester = semester;
  this->grade = grade;
}
Grades ::~Grades() {}

// set and get functions
void Grades ::SetGrade(float grade) { this->grade = grade; }
void Grades ::SetSemester(int semester) { this->semester = semester; }
float Grades ::GetGrade(void) const { return grade; }
int Grades ::GetSemester(void) const { return semester; }
