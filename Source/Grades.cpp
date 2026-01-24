#include <Grades.h>

Student :: Grades ::Grades(){
    semester=0;
    grade=0;
}
Student :: Grades ::Grades(int semester, int grade){
    this->semester = semester;
    this->grade = grade;
}
Student :: Grades ::~Grades(){}

//set and get functions
void Student :: Grades :: SetGrade(float grade){
    this->grade=grade;
}
void Student :: Grades :: SetSemester(int semester){
    this->semester= semester;
}
float Student :: Grades :: GetGrade(void)const{
    return grade;
}
int Student :: Grades :: GetSemester(void)const{
    return semester;
}
