#include <StudManager.h>

void StudManager::addStudent(std::string name, int age, std::string email, std::string AM, Gender Sex, int Semester){
  std::shared_ptr<Student> S(new Student(std::move(name), age, std::move(email),
                                         std::move(AM), Sex, Semester));
  Students.emplace(generateID(), S);
}
