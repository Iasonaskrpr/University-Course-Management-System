#include <Student.h>
#include <map>

// Get functions
int Student::getECTS(void) const { return AccumulatedECTS; }

int Student::getID(void) const { return ID; }

int Student::getSemester(void) const { return Semester; }

int Student::getPassedMandatory(void) const { return PassedMandatorySubjects; }

// returns courses of the student with the specific id,
std::span<const CourseRecord> Student::getCourses(int id, bool IncludeFailed,
                                                  bool IncludePassed,
                                                  bool IncludeCurrent) const {
  std::vector<CourseRecord> grades;
  grades.reserve(Courses.size());
  for (const auto &course : Courses) {
    if ((IncludePassed && course.second.status == CourseStatus::Passed) ||
        (IncludeFailed && course.second.status == CourseStatus::Failed) ||
        (IncludeCurrent && course.second.status == CourseStatus::Enrolled)) {
      grades.push_back(course.second);
    }
  }
  return grades;
}

float Student::calculateAverage() const {
  auto passed_view =
      Courses | std::views::values // 1. Just look at the CourseRecord,
                                   // ignore the string key
      | std::views::filter([](const CourseRecord &rec) {
          return rec.status ==
                 CourseStatus::Passed; // 2. Only keep the Passed ones
        });
  float average{};
  for (const auto &Course : passed_view) {
    average += Course.grade * Course.ECTS;
  }
  // Round to two decimal places
  return std::round((average / getECTS()) * 100.0f) / 100.0f;
}

// we update the course by assigning a grade
// void Student ::UpdateCourse(Course *C, float Grade) {
//  Grades G;
//  // if the grade is greater or equal than five then we have to update the
//  ects
//  // ,the counter for the mandatory courses and the data structures we have in
//  // the class
//  if (Grade >= 5) {
//    UpdateECTS(*C);
//    if (C->GetMandatory()) {
//      countMandatory++;
//    }
//    G.SetGrade(Grade);
//    G.SetSemester(C->GetSemester());
//    PassedCourses[C->GetName()] = G;
//  }
//  C->SetGrade(GetName(), Grade);
//}

// we print the grades of every passed course in the specific year
// void Student ::PrintYear(int Year) {
//  bool flag = false;
//  std::unordered_map<std::string, Grades>::iterator it =
//  PassedCourses.begin();
//  // if the year is zero then print all the grades of every passed course
//  if (Year == 0) {
//    while (it != PassedCourses.end()) {
//      std::cout << "Course:  " << it->first
//                << "    Grade: " << it->second.GetGrade() << std::endl;
//      it++;
//      flag = true;
//    }
//  }
//  // Otherwise print all the grades of every passed course in the specific
//  year else {
//    while (it != PassedCourses.end()) {
//      if (it->second.GetSemester() == Year * 2 ||
//          it->second.GetSemester() == Year * 2 - 1) {
//        std::cout << "Course:  " << it->first
//                  << "    Grade: " << it->second.GetGrade() << std::endl;
//        flag = true;
//      }
//      it++;
//    }
//  }
//  if (!flag) {
//    std::cout << "The student doesn't have any courses in this year"
//              << std::endl;
//  }
//  std::cout << std::endl;
//}
//
//// we print the grades of every passed course in the specific semester
// void Student ::PrintSemester(int Semester) {
//   bool flag = false;
//   std::unordered_map<std::string, Grades>::iterator it =
//   PassedCourses.begin(); while (it != PassedCourses.end()) {
//     if (it->second.GetSemester() == Semester) { // we check if the course is
//     in
//                                                 // the semester we want to
//                                                 print
//       std::cout << "Course:  " << it->first
//                 << "    Grade: " << it->second.GetGrade() << std::endl;
//       flag = true;
//     }
//     it++;
//   }
//   if (!flag) {
//     std::cout << "The student doesn't have any courses in this semester"
//               << std::endl;
//   }
//   std::cout << std::endl;
// }
//
//// function that assign a course to the student
// void Student ::AssignCourse(Course *C) { Courses.insert(Courses.end(), C); }
//
//// Overload function for the equal operator
// void Student ::operator=(const Student &S) {
//
//   // we itialize the private members
//   total_ects = S.total_ects;
//   AM = S.AM;
//   semester = S.semester;
//   countMandatory = S.countMandatory;
//
//   // we delete the map with the old data and we insert the new data
//   PassedCourses.clear();
//   std::unordered_multimap<std::string, Grades>::const_iterator itr =
//       S.PassedCourses.begin();
//   while (itr != S.PassedCourses.end()) {
//     PassedCourses.insert(
//         std::pair<std::string, Grades>(itr->first, itr->second));
//     itr++;
//   }
//
//   // we delete the vector with the old objects and we insert the new objects
//   std::vector<Course *>::iterator it = Courses.begin();
//   while (it != Courses.end()) {
//     delete *it;
//     it++;
//   }
//   Courses.erase(Courses.begin(), Courses.end());
//   std::vector<Course *>::const_iterator it1 = S.Courses.begin();
//   while (it1 != S.Courses.end()) {
//     Course *temp = new Course((*it1)->GetName(), (*it1)->GetSemester(),
//                               (*it1)->GetECTS(), (*it1)->GetMandatory());
//     Courses.insert(Courses.end(), temp);
//     it1++;
//   }
// }

// Overload function for the input operator
// std::istream &operator>>(std::istream &str, Student *S) {
//  std::cout << "Give the student's name: ";
//  std::getline(str >> std::ws,
//               S->Name); // reads a string with the spaces because the name
//                         // contains and the surname
//  std::cout << "Give the student's age: ";
//  str >> S->age;
//  std::cout << "Give the student's email: ";
//  str >> S->email;
//  std::cout << "Give the student's sex: ";
//  str >> S->Sex;
//  std::cout << "Give the student's total ects: ";
//  str >> S->total_ects;
//  std::cout << "Give the student's register number: ";
//  str >> S->AM;
//  std::cout << "Give the student's current semester ";
//  str >> S->semester;
//  return str;
//}

// THESE ARE UNNEEDED ONCE WE SWITCH TO USING SQL DATABASES
// functions that helps with updating the files
// FIXME: This needs to make use of a id->Crs name function to work
// std::vector<std::string> Student ::getnamemap(void) {
//  std::vector<std::string> temp;
//  for (auto& Crs : PassedCourses) {
//    temp.insert(temp.end(), Crs.first);
//  }
//  return temp;
//}
// std::vector<float> Student ::getgrademap(void) {
//  std::vector<float> temp;
//  for (auto &Crs : PassedCourses) {
//    temp.insert(temp.end(), Crs.second.second);
//  }
//  return temp;
//}
