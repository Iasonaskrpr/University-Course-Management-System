#pragma once
#include <Student.h>
#include <memory>
#include <span>
#include <unordered_map>

enum class CourseStatus { Enrolled, Passed, Failed };
struct CourseRecord {
  int courseID;
  float grade = 0.0;
  int semester;
  int ECTS;
  CourseStatus status;
};
class StudManager {
private:
  std::unordered_map<int, std::unique_ptr<Student>>
      Students; // Mapping of student ID to student shared ptr and his grades
                // Generate a unique ID for each student. We start from a large
                // number to avoid conflicts with any existing IDs that might be
                // in the database
                //
  // FIXME: Make sure IDS are unique across students, courses, and other
  // entities in the system. This might require a more robust ID generation
  // strategy, such as using UUIDs or a centralized ID generator.
  int generateID() {
    static int id = 0;
    return ++id;
  }

public:
  StudManager() = default;
  ~StudManager() = default;
  void addStudent(const std::unique_ptr<Student> S) {
    Students.emplace(generateID(), S);
  }
  void addStudent(std::string name, int age, std::string email, std::string AM,
                  Gender Sex, int Semester);

  const Student *findStudent(int id) const;

  void deleteStudent(int id) { Students.erase(id); }

  void setECTS(int id, int ects) const;

  void setSemester(int id, int semester) const;
};