#pragma once
#include <unordered_map>
#include <Student.h>
#include <memory>
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
		void AddStudent(const std::shared_ptr<Student>& S) {
			Students.emplace(generateID(), S); 
		}
        void AddStudent(const std::string& name, int age, const std::string& email, const std::string&, const std::string&, const int);

		const std::shared_ptr<Student>& FindStudent(int id) const {
			auto it = Students.find(id);
			if (it != Students.end()) {
				return it->second;
			}
			return nullptr;
		}
		void DeleteStudent(int id) {
			auto it = Students.find(id);
			if (it != Students.end()) {
				it->second.reset();
				Students.erase(it);
			}
        }
		void SetECTS(int id, int ects) const{
			auto& student = FindStudent(id);
			if (student) {
				student->total_ects = ects;
			}
         }
};