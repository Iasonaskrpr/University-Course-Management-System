#include <Student.h>
#include <map>
// constructors
Student ::Student() : Person() {
  total_ects = 0;
  AM = "0000000";
  semester = 1;
}

Student ::Student(std::string Name, int age, std::string email, std::string Sex,
                  std::string AM, int semester)
    : Person(Name, Sex, age, email) {

  this->AM = AM;
  this->semester = semester;
}

// destructor
Student ::~Student() {

  // delete map
  PassedCourses.clear();

  // delete vector
  std::vector<Course *>::iterator it = Courses.begin();
  while (it != Courses.end()) {
    delete *it;
    it++; // next object
  }
  Courses.erase(Courses.begin(), Courses.end());
}

// Set functions
void Student ::SetSemester(int semester) { this->semester = semester; }

void Student ::SetAM(std::string AM) { this->AM = AM; }

void Student ::SetECTS(int total_ects) { this->total_ects = total_ects; }

// Get functions
int Student ::GetECTS(void) const { return total_ects; }

std::string Student ::GetAM(void) const { return AM; }

int Student ::GetSemester(void) const { return semester; }

int Student ::GetMandatoryCount(void) const { return countMandatory; }

std::vector<Course *> Student ::GetSubjects(void) const { return Courses; }

// function that updates the total ects of the student
void Student ::UpdateECTS(Course C) { total_ects += C.GetECTS(); }

// we update the course by assigning a grade
void Student ::UpdateCourse(Course *C, float Grade) {
  Grades G;
  // if the grade is greater or equal than five then we have to update the ects
  // ,the counter for the mandatory courses and the data structures we have in
  // the class
  if (Grade >= 5) {
    UpdateECTS(*C);
    if (C->GetMandatory()) {
      countMandatory++;
    }
    G.SetGrade(Grade);
    G.SetSemester(C->GetSemester());
    PassedCourses[C->GetName()] = G;
  }
  C->SetGrade(GetName(), Grade);
}

// we print the grades of every passed course in the specific year
void Student ::PrintYear(int Year) {
  bool flag = false;
  std::unordered_map<std::string, Grades>::iterator it = PassedCourses.begin();
  // if the year is zero then print all the grades of every passed course
  if (Year == 0) {
    while (it != PassedCourses.end()) {
      std::cout << "Course:  " << it->first
                << "    Grade: " << it->second.GetGrade() << std::endl;
      it++;
      flag = true;
    }
  }
  // Otherwise print all the grades of every passed course in the specific year
  else {
    while (it != PassedCourses.end()) {
      if (it->second.GetSemester() == Year * 2 ||
          it->second.GetSemester() == Year * 2 - 1) {
        std::cout << "Course:  " << it->first
                  << "    Grade: " << it->second.GetGrade() << std::endl;
        flag = true;
      }
      it++;
    }
  }
  if (!flag) {
    std::cout << "The student doesn't have any courses in this year"
              << std::endl;
  }
  std::cout << std::endl;
}

// we print the grades of every passed course in the specific semester
void Student ::PrintSemester(int Semester) {
  bool flag = false;
  std::unordered_map<std::string, Grades>::iterator it = PassedCourses.begin();
  while (it != PassedCourses.end()) {
    if (it->second.GetSemester() == Semester) { // we check if the course is in
                                                // the semester we want to print
      std::cout << "Course:  " << it->first
                << "    Grade: " << it->second.GetGrade() << std::endl;
      flag = true;
    }
    it++;
  }
  if (!flag) {
    std::cout << "The student doesn't have any courses in this semester"
              << std::endl;
  }
  std::cout << std::endl;
}

// function that assign a course to the student
void Student ::AssignCourse(Course *C) { Courses.insert(Courses.end(), C); }

// Overload function for the equal operator
void Student ::operator=(const Student &S) {

  // we itialize the private members
  total_ects = S.total_ects;
  AM = S.AM;
  semester = S.semester;
  countMandatory = S.countMandatory;

  // we delete the map with the old data and we insert the new data
  PassedCourses.clear();
  std::unordered_multimap<std::string, Grades>::const_iterator itr =
      S.PassedCourses.begin();
  while (itr != S.PassedCourses.end()) {
    PassedCourses.insert(
        std::pair<std::string, Grades>(itr->first, itr->second));
    itr++;
  }

  // we delete the vector with the old objects and we insert the new objects
  std::vector<Course *>::iterator it = Courses.begin();
  while (it != Courses.end()) {
    delete *it;
    it++;
  }
  Courses.erase(Courses.begin(), Courses.end());
  std::vector<Course *>::const_iterator it1 = S.Courses.begin();
  while (it1 != S.Courses.end()) {
    Course *temp = new Course((*it1)->GetName(), (*it1)->GetSemester(),
                              (*it1)->GetECTS(), (*it1)->GetMandatory());
    Courses.insert(Courses.end(), temp);
    it1++;
  }
}

// Overload function for the input operator
std::istream &operator>>(std::istream &str, Student *S) {
  std::cout << "Give the student's name: ";
  std::getline(str >> std::ws,
               S->Name); // reads a string with the spaces because the name
                         // contains and the surname
  std::cout << "Give the student's age: ";
  str >> S->age;
  std::cout << "Give the student's email: ";
  str >> S->email;
  std::cout << "Give the student's sex: ";
  str >> S->Sex;
  std::cout << "Give the student's total ects: ";
  str >> S->total_ects;
  std::cout << "Give the student's register number: ";
  str >> S->AM;
  std::cout << "Give the student's current semester ";
  str >> S->semester;
  return str;
}

// functions that helps with updating the files
std::vector<std::string> Student ::getnamemap(void) {
  std::vector<std::string> temp;
  std::unordered_map<std::string, Grades>::iterator itr = PassedCourses.begin();
  while (itr != PassedCourses.end()) {
    temp.insert(temp.end(), itr->first);
    itr++;
  }
  return temp;
}
std::vector<float> Student ::getgrademap(void) {
  std::vector<float> temp;
  std::unordered_map<std::string, Grades>::iterator itr = PassedCourses.begin();
  while (itr != PassedCourses.end()) {
    temp.insert(temp.end(), itr->second.GetGrade());
    itr++;
  }
  return temp;
}
