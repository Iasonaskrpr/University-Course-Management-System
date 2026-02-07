#include <Professor.h>

void Professor ::removeCourse(id_t courseID) {
  auto it = std::find(AssignedCourses.begin(), AssignedCourses.end(), courseID);
  if (it != AssignedCourses.end()) {
      AssignedCourses.erase(it);
  }
} 

// function that removes all the courses that the professor teaches
void Professor ::RemoveAllCourses(void) {
  AssignedCourses.clear();
}

// function that prints the statistics of the courses that the professor teaches
// FIXME: This should be moved to a manager class that can access the courses and students data to calculate the statistics, and the professor class should only have a function that returns the courses that he teaches
void Professor ::printStats(void) {
  float MO, SucRate;
  int TotalStudents, PassedStudents;
  std::unordered_map<std::string, float> G;
  std::vector<int>::iterator it = AssignedCourses.begin();
  while (it != AssignedCourses.end()) {
    int count = 0;
    SucRate = 0.0;
    TotalStudents = 0;
    PassedStudents = 0;
    G = (*it)->GetMap();
    std::unordered_map<std::string, float>::iterator itr = G.begin();
    while (itr != G.end()) {
      if (itr->second >= 5) {
        PassedStudents++;
      }
      count += itr->second;
      TotalStudents++;
      itr++;
    }
    MO = ((float)count) / ((float)TotalStudents);
    SucRate = ((float)PassedStudents) / TotalStudents * 100;
    std::cout << (*it)->GetName() << " statistics are: " << std::endl;
    std::cout << "Success Rate of the Course :   " << SucRate
              << "%  and the average grade is :  " << MO << std::endl;
    it++;
  }
  std::cout << std::endl;
}

