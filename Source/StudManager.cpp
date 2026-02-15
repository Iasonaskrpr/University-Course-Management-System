#include <StudManager.h>
void StudManager::addStudent(std::string name, int age, std::string email,
                             std::string AM, Gender Sex, int Semester) {
  std::unique_ptr<Student> S(new Student(std::move(name), age, std::move(email),
                                         std::move(AM), Sex, Semester));
  Students.emplace(generateID(), S);
}

const Student &StudManager::getStudent(int id) const {
  auto it = Students.find(id);
  if (it == Students.end()) {
    throw StudentException("Student with ID " + std::to_string(id) +
                           " is not in the system!");
  }
  return *(it->second);
}

void StudManager::setSemester(int id, int semester) const {
  auto &student = findStudent(id);
  if (student) {
    student->Semester = semester;
  }
}

void StudManager::assignGrade(int StudentID, int CourseID, float grade) const{
  if (grade < 0.0f || grade > 10.0f) 
      throw std::invalid_argument("Grade must be between 0 and 10!");
  auto &student = getStudent(StudentID);
  auto it = student.Courses.find(CourseID);
  if (it == student.Courses.end()) 
    throw StudentException("Student is not enrolled in this course!");
  CourseRecord &course = it->second;
  if (course.status == CourseStatus::Enrolled) {
    course.status = grade >= 5.0f ? CourseStatus::Passed : CourseStatus::Failed;
    course.grade = grade;
    if (course.status == CourseStatus::Passed) 
      student.AccumulatedECTS += course.ECTS;
  } else if(course.status == CourseStatus::Passed) {
    throw StudentException("Student has already passed this course!");
  }
}
