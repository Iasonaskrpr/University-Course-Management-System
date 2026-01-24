#include <Professor.h>

//constructors
Professor :: Professor():Person(){}

Professor :: Professor(std::string Name , std::string email, int age , std::string Sex): Person(Name,Sex,age,email){}

Professor :: Professor(std::string Name , std::string email, int age , std::string Sex,std::vector<Course*>c): Person(Name,Sex,age,email){
    std::vector<Course*> Courses(c.begin(), c.end());
}

//destructor
Professor :: ~Professor(){

    // delete the vector
    Courses.erase(Courses.begin(),Courses.end());
}

//set and get functions
void Professor :: SetCourses(Course* course){
    Courses.insert(Courses.end(),course);
}

std::vector<Course*> Professor ::GetCourses(void) const{
    return Courses;
}

//function for removing a course that the professor no longer teaches
void Professor :: RemoveCourse(std::string course){
    std::vector<Course*> :: iterator it = Courses.begin();
    while (it != Courses.end()){
        if ( (*it)->GetName() == course){
            Courses.erase(it);
            return;
        }
        it++;
    }
}

// function that removes all the courses that the professor teaches
void Professor :: RemoveAllCourses(void){
    std::vector<Course*> :: iterator it = Courses.begin();
    while(it != Courses.end()){
        (*it)->SetProfessor(NULL);
        it++;
    }
    Courses.clear();
}

//function that prints the statistics of the courses that the professor teaches
void Professor :: PrintStats(void){
    float MO,SucRate;
    int TotalStudents,PassedStudents;
    std::unordered_map<std::string,float> G;
    std::vector<Course*> :: iterator it = Courses.begin();
    while (it != Courses.end()){
        int count = 0;
        SucRate = 0.0;
        TotalStudents = 0;
        PassedStudents = 0;
        G = (*it)->GetMap();
        std::unordered_map<std::string,float> :: iterator itr = G.begin();
        while (itr!=G.end()){
            if(itr->second>=5){
                PassedStudents++;
            }
            count += itr->second;
            TotalStudents++;
            itr++;
        }
        MO = ((float)count)/((float)TotalStudents);
        SucRate = ((float)PassedStudents)/TotalStudents*100;
        std::cout << (*it)->GetName() << " statistics are: " << std::endl;
        std::cout << "Success Rate of the Course :   " << SucRate << "%  and the average grade is :  " << MO << std::endl;
        it++;
    }
    std::cout << std::endl;
}

//Overload function for the input operator
std::istream &operator>>(std::istream &str , Professor* P){
    std::cout << "Give the professor's name: ";
    std::getline(str>>std::ws , P->Name);//reads a string with the spaces because the name contains and the surname
    std::cout << "Give the professor's age: ";
    str >> P->age;
    std::cout << "Give the professor's email: ";
    str >> P->email;
    std::cout << "Give the professor's sex: ";
    str >> P->Sex;
    return str;
}

//Overload function for the equal operator
void Professor :: operator=(const Professor &P){

    //we delete the vector with the old objects and we insert the new objects 
    std::vector<Course*> :: iterator it = Courses.begin();
    while (it != Courses.end()){
        delete *it;
        it++;
    }
    Courses.erase(Courses.begin(),Courses.end());
    std::vector<Course*> :: const_iterator it1 = P.Courses.begin();
    while (it1!= P.Courses.end()){
        Course* temp = new Course((*it1)->GetName(),(*it1)->GetSemester(),(*it1)->GetECTS(),(*it1)->GetMandatory());
        Courses.insert(Courses.end(), temp);
        it1++;
    }
}
