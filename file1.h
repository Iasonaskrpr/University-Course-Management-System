#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

class Secretary;
class Student;
class Professor;
class Course;

class Secretary{

    private:  
        vector<Student*>Students;  //vector of all students in the university
        vector<Professor*>Professors;  //vector of all professors in the university
        vector<Course*>Courses; //vector of all courses in the university
        int MandatoryCount; //the number of the mandatory courses
    public:
        //constructor
        Secretary();

        //destructor
        ~Secretary();

        //copy constructor
        Secretary(const Secretary &S);

        //set and get function
        void SetMandatoryCount(int);
        int GetMandatoryCount(void)const;

        //Overload fuctions of the operators
        void operator+(Student* S);
        void operator+(Professor* P);
        void operator+(Course* C);
        void operator=(const Secretary &S);

        //finds the object based on its name
        Course* FindCourse(string);
        Professor* FindProf(string);
        Student* FindStud(string);

        //delete functions  
        void DeleteStudent(string);
        void DeleteProf(string);
        void DeleteCourse(string);
        
        //returns a vector with all the students that can get a degree
        vector<Student*> Degree(void);

        //functions with different operations
        void PrintStats(string);
        bool RegisterStudent(string ,string);
        bool AssignProf(string,string);
        void PassCourse(Student* , Course* ,float);
        void PrintDetailedSemester(string,int);
        void PrintDetailedYear(string,int);
        void StartSemester(void);
        void EndSemester(void);

        //function that update files 
        void printfiles(void);
};

class Person{

    protected:
        string Name;
        string Sex;
        int age;
        string email;
        static int count;  //the variable that counts the number of people created is static int because we need to retain its value
    public:
        // constructors
        Person();
        Person(string,string,int,string);
    
        //destructor
        virtual ~Person()=0;
        
        //we need set functions because the members of the class are private
        void SetAge(int age);
        void SetSex(string Sex);
        void SetName(string Name);
        void Setemail(string email);

        //we need get functions because the members of the class are private
        string Getemail(void) const;
        int GetAge(void) const;
        string GetSex(void) const;
        string GetName(void) const;

        //Functions for the counter 
        void printCount();
        void decreaseCount();

};

class Student:public Person{

    private:
        //the class Grades contains  
        class Grades{
            private:
                int semester;
                float grade;
            public:
                //costructors and destructor
                Grades();
                Grades(int,int);
                ~Grades();
                //set and get functions
                void SetGrade(float);
                void SetSemester(int);
                float GetGrade(void) const;
                int GetSemester(void) const;
        };

        int total_ects;
        string AM;
        int semester;        
        
        map<string,Grades> PassedCourses;//the map contains the courses that the student passed with the grade
        vector<Course*> Courses; //the vector contains  the courses that the student enrolled 
        static int countMandatory; //counts the madatory courses that he passed 
    public:
        //constructors
        Student();
        Student(string,int,string,string,string,int); 
        
        //destructor
        ~Student(); 

        //set functions
        void SetSemester(int);
        void SetAM(string);
        void SetECTS(int);

        //get functions
        int GetECTS(void) const;
        string GetAM(void) const;
        int GetSemester(void) const;
        int GetMandatoryCount(void) const;
        vector<Course*> GetSubjects(void)const;//returns the vector with courses he enrolled

        //overload functions of the operators
        void operator=(const Student &S);
        friend istream &operator>> (istream &str , Student *S);
        
        //update functions
        void UpdateECTS(Course); // overflow operand +=
        void UpdateCourse(Course*,float);

        //functions with different operations
        void AssignCourse(Course*);
        void PrintSemester(int);
        void PrintYear(int);    

        //functions that helps with the update of the files
        vector<string> getnamemap(void);
        vector<float> getgrademap(void);
};

class Professor:public Person{

    private:
        vector<Course*> Courses;//the vector contains the courses that the professor teaches   

    public:
        //constructors
        Professor();
        Professor(string,string,int ,string);
        Professor(string,string,int ,string,vector<Course*>);
        
        //destructor
        ~Professor(); 

        //set and get function
        void SetCourses(Course*);//Two set courses functions one to delete a course and one to add
        vector<Course*> GetCourses(void) const;

        //overload functions of the operators
        void operator=(const Professor &P);
        friend istream &operator>>(istream &str , Professor* P);
        
        //functions with different operations
        void RemoveCourse(string);
        void RemoveAllCourses(void);
        void PrintStats(void);   
};

class Course{

    private:
        string Name;
        int semester;
        int ects;
        bool mandatory;//if the course is mandatory or a course of choise 
        Professor* Prof;//the professor who teaches the course

        map<string,float> Grades;// the map contains the students who passed the course and their grades

    public:
        //constructor
        Course();
        Course(string,int,int,bool);

        //destructor
        ~Course();

        //set functions
        void SetName(string);
        void SetSemester(int);
        void SetECTS(int);
        void SetMandatory(bool);
        void SetProfessor(Professor*);
        void SetGrade(string,int);
        
        //get functions
        string GetName(void) const;
        int GetSemester(void) const;
        int GetECTS(void) const;
        bool GetMandatory(void) const;
        Professor* GetProfessor(void)const;
        map<string,float> GetMap(void) const;

        //overload functions of the operators
        friend ostream &operator<<(ostream &str , Course *);
        friend istream &operator>>(istream &str , Course* C);
        void operator=(const Course &C);
};