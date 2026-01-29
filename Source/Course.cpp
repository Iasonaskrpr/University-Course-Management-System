#include <Course.h>
#include <string>

// constructors
Course ::Course() {
  Name = "undefined";
  semester = 0;
  ects = 0;
  mandatory = 0;
  Prof = new Professor();
}

Course ::Course(std::string Name, int semester, int ects, bool mandatory) {
  this->Name = Name;
  this->semester = semester;
  this->ects = ects;
  this->mandatory = mandatory;
}

// destructor
Course ::~Course() { Grades.clear(); }

// set functions
void Course ::SetSemester(int semester) { this->semester = semester; }

void Course::SetName(std::string Name) { this->Name = Name; }

void Course ::SetECTS(int ects) { this->ects = ects; }

void Course ::SetMandatory(bool mandatory) { this->mandatory = mandatory; }

void Course ::SetProfessor(Professor *Prof) {
  this->Prof = Prof;
  Prof->SetCourses(this);
}

void Course ::SetGrade(std::string S, int G) { Grades[S] = G; }

// get functions
std::string Course ::GetName(void) const { return Name; }

int Course ::GetSemester(void) const { return semester; }

int Course ::GetECTS(void) const { return ects; }

bool Course ::GetMandatory(void) const { return mandatory; }

Professor *Course::GetProfessor(void) const { return Prof; }

std::unordered_map<std::string, float> Course ::GetMap(void) const {
  return Grades;
}

// Overload function for the output operator that prints the courses with the
// grades that she passed in that semester
std::ostream &operator<<(std::ostream &str, Course *C) {
  std::unordered_map<std::string, float>::iterator it = C->Grades.begin();
  str << "The students that passed " << C->Name << " are:" << std::endl;
  while (it != C->Grades.end()) {
    if (it->second >= 5) {
      str << "Name:   " << it->first << "   Grade:" << it->second << std::endl;
    }
    it++;
  }
  return str;
}

// Overload function for the input operator
std::istream &operator>>(std::istream &str, Course *C) {
  std::string temp;
  std::cout << "Give the course's name: ";
  std::getline(str >> std::ws,
               C->Name); // reads a string with the spaces because the
                         // course can contain two words
  std::cout << "Give the course's semester: ";
  str >> C->semester;
  std::cout << "Give the course's ects: ";
  str >> C->ects;
  std::cout << "Is this course mandatory? (True/False): ";
  str >> temp;
  if (temp == "True" || temp == "true")
    C->mandatory = 1;
  else
    C->mandatory = 0;

  return str;
}

// Overload function for the equal operator
void Course ::operator=(const Course &C) {

  // we itialize the private members
  Name = C.Name;
  semester = C.semester;
  ects = C.ects;
  mandatory = C.mandatory;

  // we delete the old professor and initialize the new one
  delete Prof;
  Prof = C.Prof;

  // we delete the map with the old data and we insert the new data
  Grades.clear();
  std::unordered_multimap<std::string, float>::const_iterator itr =
      C.Grades.begin();
  while (itr != C.Grades.end()) {
    Grades.insert(std::pair<std::string, float>(itr->first, itr->second));
    itr++;
  }
}