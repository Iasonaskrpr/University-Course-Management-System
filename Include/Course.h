#ifndef COURSE_HEADER
#define COURSE_HEADER

#include <string>
#include <iostream>
#include <unordered_map>
#include <Professor.h>

class Course{

        std::string Name;
        int semester;
        int ects;
        bool mandatory;//if the course is mandatory or a course of choise 
        Professor* Prof;//the professor who teaches the course

        std::unordered_map<std::string,float> Grades;// the map contains the students who passed the course and their grades

    public:
        //constructor
        Course();
        Course(std::string,int,int,bool);

        //destructor
        ~Course();

        //set functions
        void SetName(std::string);
        void SetSemester(int);
        void SetECTS(int);
        void SetMandatory(bool);
        void SetProfessor(Professor*);
        void SetGrade(std::string,int);
        
        //get functions
        std::string GetName(void) const;
        int GetSemester(void) const;
        int GetECTS(void) const;
        bool GetMandatory(void) const;
        Professor* GetProfessor(void)const;
        std::unordered_map<std::string,float> GetMap(void) const;

        //overload functions of the operators
        friend std::ostream &operator<<(std::ostream &str , Course *);
        friend std::istream &operator>>(std::istream &str , Course* C);
        void operator=(const Course &C);
};
#endif