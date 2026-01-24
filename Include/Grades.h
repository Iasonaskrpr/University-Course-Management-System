class Grades {
  int semester;
  float grade;

public:
  // costructors and destructor
  Grades();
  Grades(int, int);
  ~Grades();
  // set and get functions
  void SetGrade(float);
  void SetSemester(int);
  float GetGrade(void) const;
  int GetSemester(void) const;
};