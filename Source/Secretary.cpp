#include <Secretary.h>
#include <fstream>
int ReqECTS = 90;
// constructor
Secretary ::Secretary() {}

// destructor
Secretary ::~Secretary() {

  // delete vector with students
  std::vector<Student *>::iterator it1 = Students.begin();
  while (it1 != Students.end()) {
    delete *it1;
    it1++;
  }
  Students.erase(Students.begin(), Students.end());

  // delete vector with Professors
  std::vector<Professor *>::iterator it2 = Professors.begin();
  while (it2 != Professors.end()) {
    delete *it2;
    it2++;
  }
  Professors.erase(Professors.begin(), Professors.end());

  // delete vector with courses
  std::vector<Course *>::iterator it3 = Courses.begin();
  while (it3 != Courses.end()) {
    delete *it3;
    it3++;
  }
  Courses.erase(Courses.begin(), Courses.end());
}

// Copy contructor
Secretary ::Secretary(const Secretary &S) {

  // we initialize every vector of the class Secretary
  std::vector<Student *>::const_iterator itr1 =
      S.Students
          .begin(); // Const iterator because secretary S is a const variable
  while (itr1 != S.Students.end()) {

    Student *temp1 = new Student((*itr1)->GetName(), (*itr1)->GetAge(),
                                 (*itr1)->Getemail(), (*itr1)->GetSex(),
                                 (*itr1)->GetAM(), (*itr1)->GetSemester());
    Students.insert(Students.end(), temp1);
    itr1++; // next object
  }

  // we initialize every vector of the class Professor
  std::vector<Professor *>::const_iterator itr2 = S.Professors.begin();
  while (itr2 != S.Professors.end()) {

    Professor *temp2 = new Professor((*itr2)->GetName(), (*itr2)->Getemail(),
                                     (*itr2)->GetAge(), (*itr2)->GetSex(),
                                     (*itr2)->GetCourses());
    Professors.insert(Professors.end(), temp2);
    itr2++; // next object
  }

  // we initialize every vector of the class Course
  std::vector<Course *>::const_iterator itr3 = S.Courses.begin();
  while (itr3 != S.Courses.end()) {

    Course *temp3 = new Course((*itr3)->GetName(), (*itr3)->GetSemester(),
                               (*itr3)->GetECTS(), (*itr3)->GetMandatory());
    Courses.insert(Courses.end(), temp3);
    itr3++; // next object
  }

  MandatoryCount = S.MandatoryCount;
}

// set and get function
void Secretary ::SetMandatoryCount(int MandatoryCount) {
  this->MandatoryCount = MandatoryCount;
}
int Secretary ::GetMandatoryCount(void) const { return MandatoryCount; }

// find the Student in the vector based on the name and if he/she doesn't exist
// return NULL
Student *Secretary ::FindStud(std::string S) {
  std::vector<Student *>::iterator it = Students.begin();
  while (it != Students.end()) {
    if ((*it)->GetName() == S) {
      return (*it);
    }
    it++;
  }
  return NULL;
}

// find the Professor in the vector based on the name and if he/she doesn't
// exist return NULL
Professor *Secretary ::FindProf(std::string P) {
  std::vector<Professor *>::iterator it = Professors.begin();
  while (it != Professors.end()) {
    if ((*it)->GetName() == P) {
      return *it;
    }

    it++;
  }
  return NULL;
}

// find the Course in the vector based on the name and if it doesn't exist
// return NULL
Course *Secretary ::FindCourse(std::string C) {
  std::vector<Course *>::iterator it = Courses.begin();
  while (it != Courses.end()) {
    if ((*it)->GetName() == C) {
      return *it;
    }
    it++;
  }
  return NULL;
}

// returns a vector with all the students that can get a degree and prints them
std::vector<Student *> Secretary ::Degree(void) {
  std::cout << "These are the students that can get a degree: " << std::endl;
  std::vector<Student *> DegreeReady; // the vector that will contain the
                                      // students ready to get a degree
  std::vector<Student *>::iterator it = Students.begin();
  while (it != Students.end()) {
    // the student can get a degree if he has the required amount of ects ,
    // studied 4 years (8 semesters) and has passed all the mandatory courses
    if ((*it)->GetECTS() >= ReqECTS && (*it)->GetSemester() >= 8 &&
        (*it)->GetMandatoryCount() >= MandatoryCount) {
      DegreeReady.insert(DegreeReady.end(), *it);
      std::cout << (*it)->GetName() << " can get a degree!" << std::endl;
    }
    it++;
  }
  return DegreeReady;
}

// we print the statistics of the teacher if he exists
void Secretary ::PrintStats(std::string P) {
  Professor *Prof = FindProf(P);
  Prof->PrintStats();
}

// the function enrolls a student to a course
bool Secretary ::RegisterStudent(std::string S, std::string C) {
  Student *Stud = FindStud(S);
  if (Stud == NULL) {
    return false;
  }
  Course *Cs = FindCourse(C);
  if (Cs == NULL) {
    return false;
  }
  // we have to check if the semester of the course is in the same season with
  // the semester of the student and the student can enroll to a course of the
  // same semester or greater
  if (((Cs->GetSemester() % 2) != (Stud->GetSemester() % 2)) ||
      Stud->GetSemester() < Cs->GetSemester()) {
    return false;
  }
  Stud->AssignCourse(Cs);
  return true;
}

// the function assigns a course to a professor
bool Secretary ::AssignProf(std::string P, std::string C) {
  Professor *Prof = FindProf(P);
  if (Prof == NULL) {
    return false;
  }
  Course *CS = FindCourse(C);
  if (CS == NULL) {
    return false;
  }
  CS->SetProfessor(Prof);
  return true;
}

// We delete a student from the vector
void Secretary ::DeleteStudent(std::string S) {
  std::vector<Student *>::iterator it = Students.begin();
  while (it != Students.end()) {
    if ((*it)->GetName() == S) {
      Student *temp = *it;
      Students.erase(it);
      delete temp;
      return;
    }
    it++;
  }
}

// we delete a professor from the vector
void Secretary ::DeleteProf(std::string P) {
  std::vector<Professor *>::iterator it = Professors.begin();
  while (it != Professors.end()) {
    if ((*it)->GetName() == P) {
      Professor *temp = *it;
      Professors.erase(it);
      delete temp;
      return;
    }
    it++;
  }
}

// we delete a course from the vector
void Secretary::DeleteCourse(std::string C) {
  std::vector<Course *>::iterator it = Courses.begin();
  while (it != Courses.end()) {
    if ((*it)->GetName() == C) {
      Course *temp = *it;
      Courses.erase(it);
      delete temp;
      return;
    }
    it++;
  }
}

// function that updates all the datas when a student pass a course
void Secretary ::PassCourse(Student *S, Course *C, float Grade) {
  S->UpdateCourse(C, Grade);
}

// we print the all the grades of the student in the specific semester
void Secretary ::PrintDetailedSemester(std::string S, int semester) {
  Student *Stud = FindStud(S);
  Stud->PrintSemester(semester);
}

// we print the all the grades of the student in the specific year
void Secretary ::PrintDetailedYear(std::string S, int Year) {
  Student *Stud = FindStud(S);
  Stud->PrintYear(Year);
}

// Each overload function adds every member to the right vector
void Secretary ::operator+(Student *S) { Students.insert(Students.end(), S); }
void Secretary ::operator+(Course *C) { Courses.insert(Courses.end(), C); }
void Secretary ::operator+(Professor *P) {
  Professors.insert(Professors.end(), P);
}

// Overload function for the equal operator
void Secretary ::operator=(const Secretary &S) {

  // we delete all the vectors from the class secretary
  std::vector<Student *>::iterator it1 = Students.begin();
  while (it1 != Students.end()) {
    delete *it1;
    it1++;
  }
  Students.erase(Students.begin(), Students.end());
  std::vector<Professor *>::iterator it2 = Professors.begin();
  while (it2 != Professors.end()) {
    delete *it2;
    it2++;
  }
  Professors.erase(Professors.begin(), Professors.end());
  std::vector<Course *>::iterator it3 = Courses.begin();
  while (it3 != Courses.end()) {
    delete *it3;
    it3++;
  }
  Courses.erase(Courses.begin(), Courses.end());

  // we initialize every vector of the class Secretary
  std::vector<Student *>::const_iterator itr1 =
      S.Students
          .begin(); // Const iterator because secretary S is a const variable
  while (itr1 != S.Students.end()) {

    Student *temp1 = new Student((*itr1)->GetName(), (*itr1)->GetAge(),
                                 (*itr1)->Getemail(), (*itr1)->GetSex(),
                                 (*itr1)->GetAM(), (*itr1)->GetSemester());
    Students.insert(Students.end(), temp1);
    itr1++;
  }
  std::vector<Professor *>::const_iterator itr2 = S.Professors.begin();
  while (itr2 != S.Professors.end()) {

    Professor *temp2 = new Professor((*itr2)->GetName(), (*itr2)->Getemail(),
                                     (*itr2)->GetAge(), (*itr2)->GetSex(),
                                     (*itr2)->GetCourses());
    Professors.insert(Professors.end(), temp2);
    itr2++;
  }
  std::vector<Course *>::const_iterator itr3 =
      S.Courses
          .begin(); // Const iterator because secretary S is a const variable
  while (itr3 != S.Courses.end()) {

    Course *temp3 = new Course((*itr3)->GetName(), (*itr3)->GetSemester(),
                               (*itr3)->GetECTS(), (*itr3)->GetMandatory());
    Courses.insert(Courses.end(), temp3);
    itr3++;
  }

  // we initialize the private member
  MandatoryCount = S.MandatoryCount;
}

// function for the start of the semester
void Secretary ::StartSemester() {
  std::vector<Student *>::iterator it = Students.begin();
  std::string sub;
  bool Flag;
  // for every student we have to add the courses that they are going to study
  while (it != Students.end()) {
    std::cout << "Which subject do you want to add to " << (*it)->GetName()
              << "(type end if you don't want to add anymore)-> ";
    std::getline(std::cin >> std::ws, sub);
    while (sub != std::string("end") || sub != std::string("End")) {
      if (sub == std::string("end") || sub == std::string("End")) {
        break;
      }
      try {
        Flag = RegisterStudent((*it)->GetName(), sub);
        if (Flag == false) {
          throw std::string("Couldn't add subject");
        }
      } catch (std::string error) {
        std::cout << "Error-> " << error << std::endl;
      }
      std::cout << "Which subject do you want to add to " << (*it)->GetName()
                << "(type end if you don't want to add anymore)-> ";
      std::getline(std::cin >> std::ws, sub);
    }
    it++;
  }
  // also for every course we make sure that the professor hasn't changed
  std::vector<Course *>::iterator it2 = Courses.begin();
  while (it2 != Courses.end()) {
    std::cout << "Do you want to change the professor of the course "
              << ((*it2)->GetName()) << "(True/False)-> ";
    std::getline(std::cin >> std::ws, sub);
    if (sub == "True" || sub == "true") {
      std::cout << "Which Professor do you want to assign? ->";
      std::getline(std::cin >> std::ws, sub);
      Flag = AssignProf(sub, (*it2)->GetName());
      while (Flag == false) {
        std::cout << "Wrong input!" << std::endl;
        std::cout << "Which Professor do you want to assign? ->";
        std::getline(std::cin >> std::ws, sub);
        Flag = AssignProf(sub, (*it2)->GetName());
      }
    }
    it2++;
  }
}

// function for the end of the semester
void Secretary ::EndSemester() {
  std::vector<Student *>::iterator it = Students.begin();
  std::vector<Course *> C;
  std::vector<Course *>::const_iterator it2;
  float Grade;

  // at the end of the semester we add the grades for every course that they
  // participated the last semester
  while (it != Students.end()) {
    (*it)->SetSemester(((*it)->GetSemester()) + 1);
    C = (*it)->GetSubjects();
    it2 = C.begin();
    while (it2 != C.end()) {
      std::cout << "What Grade did " << (*it)->GetName() << " get in "
                << (*it2)->GetName() << "-> ";
      std::cin >> Grade;
      while (Grade < 0 || Grade > 10) {
        std::cout << "Wrong input" << std::endl;
        std::cout << "What Grade did " << (*it)->GetName() << " get in "
                  << (*it2)->GetName() << "-> ";
        std::cin >> Grade;
      }
      PassCourse(*it, *it2, Grade);
      it2++;
    }
    it++;
  }
}

// function that is called by the main program to update the files after the end
// of the program
void Secretary ::printfiles(void) {
  std::ofstream fout;

  // print the courses file with the changed data
  fout.open("Courses.txt");
  std::vector<Course *>::iterator it = Courses.begin();
  while (it != Courses.end()) {
    fout << (*it)->GetName() << std::endl;
    fout << (*it)->GetSemester() << std::endl;
    fout << (*it)->GetECTS() << std::endl;
    if (it + 1 != Courses.end()) { // this helps not to print another line at
                                   // the end of the file
      fout << (*it)->GetMandatory() << std::endl;
    } else {
      fout << (*it)->GetMandatory();
    }
    it++;
  }
  fout.close();

  // print the students file with the changed data
  fout.open("Students.txt");
  std::vector<Student *>::iterator it2 = Students.begin();
  while (it2 != Students.end()) {
    fout << (*it2)->GetName() << std::endl;
    fout << (*it2)->GetSex() << std::endl;
    fout << (*it2)->GetAge() << std::endl;
    fout << (*it2)->Getemail() << std::endl;
    fout << (*it2)->GetAM() << std::endl;
    fout << (*it2)->GetSemester() << std::endl;
    std::vector<std::string> temp1 =
        (*it2)->getnamemap(); // this function returns the courses that the
                              // students are taking
    std::vector<float> temp2 =
        (*it2)->getgrademap(); // this function returns the grade of the course
    std::vector<std::string>::iterator stIt = temp1.begin();
    std::vector<float>::iterator fIt = temp2.begin();
    while (stIt != temp1.end()) {
      fout << *stIt << std::endl;
      fout << *fIt << std::endl;
      stIt++;
      fIt++;
    }
    it2++;
    if (it2 != Students.end()) {
      fout << "end" << std::endl;
    } else {
      fout << "end";
    }
  }
  fout.close();

  // print the professors file with the changed data
  fout.open("Professors.txt");
  std::vector<Professor *>::iterator it3 = Professors.begin();
  while (it3 != Professors.end()) {

    fout << (*it3)->GetName() << std::endl;
    fout << (*it3)->GetSex() << std::endl;
    fout << (*it3)->GetAge() << std::endl;
    fout << (*it3)->Getemail() << std::endl;
    std::vector<Course *> T = (*it3)->GetCourses();
    std::vector<Course *>::iterator itr2 = T.begin();
    while (itr2 != T.end()) {
      fout << (*itr2)->GetName() << std::endl;
      itr2++;
    }
    it3++;
    if (it3 != Professors.end()) { // this helps not to print another line at
                                   // the end of the file
      fout << "end" << std::endl;
    } else {
      fout << "end";
    }
  }
  fout.close();
}