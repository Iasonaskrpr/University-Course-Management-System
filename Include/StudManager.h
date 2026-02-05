#pragma once
#include <unordered_map>
#include <Student.h>
#include <memory>
// Maybe hide this from the user????
class StudManager {
	private:
		std::unordered_map<int ,std::shared_ptr<Student>> Students;
		int generateID() {
			static int id = 0;
			return ++id;
         }
	public:
        StudManager() = default;
        ~StudManager() = default;
		void addStudent(const std::shared_ptr<Student> S) {
			Students.emplace(generateID(), S); 
		}
        void addStudent(std::string name, int age, std::string email,
                        std::string AM, Gender Sex, int Semester);

		const std::shared_ptr<Student> findStudent(int id) const {
			auto it = Students.find(id);
			if (it != Students.end()) {
				return it->second;
			}
			return nullptr;
		}
		void deleteStudent(int id) {
			auto it = Students.find(id);
			if (it != Students.end()) {
				it->second.reset();
				Students.erase(it);
			}
        }
		void setECTS(int id, int ects) const{
			auto& student = findStudent(id);
			if (student) {
				student->AccumulatedECTS = ects;
			}
         }
};