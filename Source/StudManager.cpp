#include <StudManager.h>
void StudManager::addStudent(std::string name, int age, std::string email,
                             std::string AM, Gender Sex, int Semester) {
  std::unique_ptr<Student> S(new Student(std::move(name), age, std::move(email),
                                         std::move(AM), Sex, Semester));
  Students.emplace(generateID(), S);
}

const Student *StudManager::findStudent(int id) const {
  auto it = Students.find(id);
  if (it != Students.end()) {
    return it->second.first;
  }
  return nullptr;
}

void StudManager::setECTS(int id, int ects) const {
  auto &student = findStudent(id);
  if (student) {
    student->AccumulatedECTS = ects;
  }
}

void StudManager::setSemester(int id, int semester) const {
  auto &student = findStudent(id);
  if (student) {
    student->Semester = semester;
  }
}