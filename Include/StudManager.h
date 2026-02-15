#pragma once
#include <Student.h>
#include <memory>
#include <span>
#include <unordered_map>
#include <stdexcept>

class StudentException : public std::runtime_error {
public:
  explicit StudentException(const std::string &msg) : std::runtime_error(msg) {}
};

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

/// @brief Gets student with the given ID. Throws an exception if the student
/// is not found.
/// @param id
/// @return referece to the student with the given ID
  const Student &getStudent(int id) const;

  // Consider not removing the student from the manager when he is deleted, but
  // instead marking him as deleted and not allowing any operations on him. This
  // way we can keep the history of the student and his courses, and we can also
  // avoid any issues with dangling pointers or invalid IDs.
  void deleteStudent(int id) {
    size_t deletedCount = Students.erase(id);

    if (deletedCount == 0) {
      // It failed silently! You might want to throw your own error here
      throw std::runtime_error("Delete Failed: Student ID " +
                               std::to_string(id) + " does not exist.");
    }
  }

  void setSemester(int id, int semester) const;
  // TODO: After adding a global configuration we should set pass or fail based on the global configuration instead of hardcoding it to 5.0f
  /// @brief Assigns a grade to a student for a specific course. This function thows an exception so it needs to be handled correctly
  /// @param StudentID ID of the student to assign the grade to
  /// @param CourseID ID of the course for which the grade is being assigned
  /// @param grade Grade to be assigned to the student for the specified course.
  void assignGrade(int StudentID, int CourseID, float grade) const;
};