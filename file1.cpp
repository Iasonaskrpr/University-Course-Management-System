#include <iostream>
#include <algorithm>
#include<array>
#include "file1.h"

//initialize the counters
int Person::count = 0;
int Student :: countMandatory=0;

//global variable
const int ReqECTS = 90;

////////////////////////////////////////////////
///////Functions of the class Secretary/////////
////////////////////////////////////////////////

//constructor
Secretary :: Secretary(){}

//destructor
Secretary :: ~Secretary(){

    //delete vector with students
    vector<Student*> :: iterator it1 = Students.begin();
    while (it1 != Students.end()){
        delete *it1;
        it1++;
    }
    Students.erase(Students.begin(),Students.end());

    //delete vector with Professors
    vector<Professor*> :: iterator it2 = Professors.begin();
    while (it2 != Professors.end()){
        delete *it2;
        it2++; 
    }
    Professors.erase(Professors.begin(),Professors.end());

    //delete vector with courses
    vector<Course*> :: iterator it3 = Courses.begin();
    while (it3 != Courses.end()){
        delete *it3; 
        it3++;
    }
    Courses.erase(Courses.begin(),Courses.end());
}

//Copy contructor
Secretary :: Secretary(const Secretary &S){

    //we initialize every vector of the class Secretary  
    vector<Student*> :: const_iterator itr1 = S.Students.begin(); // Const iterator because secretary S is a const variable
    while(itr1 != S.Students.end()){
        
        Student* temp1 = new Student((*itr1)->GetName(),(*itr1)->GetAge(),(*itr1)->Getemail(),(*itr1)->GetSex(),(*itr1)->GetAM(),(*itr1)->GetSemester());
        temp1->decreaseCount(); //We reduce the counter so we won't count the student twice
        Students.insert(Students.end(), temp1);
        itr1++;//next object
    }

    //we initialize every vector of the class Professor 
    vector<Professor*> :: const_iterator itr2 = S.Professors.begin(); 
    while(itr2 != S.Professors.end()){
        
        Professor* temp2= new Professor((*itr2)->GetName(),(*itr2)->Getemail(),(*itr2)->GetAge(),(*itr2)->GetSex(),(*itr2)->GetCourses());
        temp2->decreaseCount(); //We reduce the counter so we won't count the professor twice
        Professors.insert(Professors.end(), temp2);
        itr2++;//next object
    }

    //we initialize every vector of the class Course  
    vector<Course*> :: const_iterator itr3 = S.Courses.begin();
    while(itr3 != S.Courses.end()){
        
        Course* temp3 = new Course((*itr3)->GetName(),(*itr3)->GetSemester(),(*itr3)->GetECTS(),(*itr3)->GetMandatory());
        Courses.insert(Courses.end(), temp3);
        itr3++;//next object
    }

    MandatoryCount = S.MandatoryCount;

}

//set and get function
void Secretary :: SetMandatoryCount(int MandatoryCount){
    this->MandatoryCount=MandatoryCount;
}
int Secretary :: GetMandatoryCount(void)const{
    return MandatoryCount;
}

//find the Student in the vector based on the name and if he/she doesn't exist return NULL
Student* Secretary :: FindStud(string S){
    vector<Student*> :: iterator it = Students.begin();
    while(it != Students.end()){
        if((*it)->GetName() == S){
            return (*it);
        }
        it++;
    }
    return NULL;
}

//find the Professor in the vector based on the name and if he/she doesn't exist return NULL
Professor* Secretary :: FindProf(string P){
    vector<Professor*> :: iterator it = Professors.begin();
    while(it != Professors.end()){
        if((*it)->GetName() == P){
            return *it;
        }

        it++;
    }
    return NULL;
}

//find the Course in the vector based on the name and if it doesn't exist return NULL
Course* Secretary :: FindCourse(string C){
    vector<Course*> :: iterator it = Courses.begin();
    while(it != Courses.end()){
        if((*it)->GetName() == C){
            return *it;
        }
        it++;
    }
    return NULL;
}

//returns a vector with all the students that can get a degree and prints them
vector<Student*> Secretary :: Degree(void){
    cout<< "These are the students that can get a degree: " << endl;
    vector<Student*> DegreeReady; // the vector that will contain the students ready to get a degree
    vector<Student*> :: iterator it = Students.begin();
    while (it != Students.end()){
        //the student can get a degree if he has the required amount of ects , studied 4 years (8 semesters) and has passed all the mandatory courses 
        if((*it)->GetECTS() >= ReqECTS && (*it)->GetSemester() >=8 && (*it)->GetMandatoryCount()>= MandatoryCount){
            DegreeReady.insert(DegreeReady.end(),*it);
            cout << (*it)->GetName() << " can get a degree!" << endl;
        }
        it++;
    }
    return DegreeReady;
}

//we print the statistics of the teacher if he exists
void Secretary :: PrintStats(string P){
    Professor* Prof= FindProf(P);
    Prof->PrintStats();
}

//the function enrolls a student to a course 
bool Secretary :: RegisterStudent(string S,string C){
    Student* Stud = FindStud(S);
    if(Stud == NULL){
        return false;
    }
    Course* Cs = FindCourse(C);
    if(Cs == NULL){
        return false;
    }
    //we have to check if the semester of the course is in the same season with the semester of the student
    //and the student can enroll to a course of the same semester or greater
    if(((Cs->GetSemester()%2) != (Stud->GetSemester()%2)) || Stud->GetSemester() < Cs->GetSemester()){ 
        return false;
    }
    Stud->AssignCourse(Cs);
    return true;
}

//the function assigns a course to a professor
bool Secretary :: AssignProf(string P,string C){
    Professor* Prof = FindProf(P);
    if(Prof == NULL){
        return false;
    }
    Course* CS = FindCourse(C);
    if(CS == NULL){
        return false;
    }
    CS->SetProfessor(Prof);
    return true;
}

//We delete a student from the vector
void Secretary :: DeleteStudent(string S){
    vector<Student*> :: iterator it = Students.begin();
    while(it != Students.end()){
        if((*it)->GetName() == S){
            Student* temp = *it;
            Students.erase(it);
            delete temp;
            return;
        }
        it++;
    }
}

//we delete a professor from the vector
void Secretary :: DeleteProf(string P){
    vector<Professor*> :: iterator it = Professors.begin();
    while(it != Professors.end()){
        if((*it)->GetName() == P){
            Professor* temp = *it;
            Professors.erase(it);
            delete temp;
            return;
        }
        it++;
    }
}

//we delete a course from the vector
void Secretary :: DeleteCourse(string C){
    vector<Course*> :: iterator it = Courses.begin();
    while(it != Courses.end()){
        if((*it)->GetName() == C){
            Course* temp = *it;
            Courses.erase(it);
            delete temp;
            return;
        }
        it++;
    }
}

//function that updates all the datas when a student pass a course 
void Secretary :: PassCourse(Student* S, Course* C,float Grade){
    S->UpdateCourse(C,Grade);
}

//we print the all the grades of the student in the specific semester  
void Secretary :: PrintDetailedSemester (string S,int semester){
    Student* Stud = FindStud(S);
    Stud->PrintSemester(semester);
}

//we print the all the grades of the student in the specific year
void Secretary :: PrintDetailedYear(string S ,int Year){
    Student* Stud = FindStud(S);
    Stud->PrintYear(Year);
}

//Each overload function adds every member to the right vector
void Secretary :: operator+(Student* S){
    Students.insert(Students.end(), S);
}
void Secretary :: operator+(Course* C){
    Courses.insert(Courses.end(), C);
}
void Secretary :: operator+(Professor* P){
    Professors.insert(Professors.end(), P);
}

//Overload function for the equal operator
void Secretary :: operator=(const Secretary &S){

    //we delete all the vectors from the class secretary
    vector<Student*> :: iterator it1 = Students.begin();
    while (it1 != Students.end()){
        delete *it1;
        it1++;
    }
    Students.erase(Students.begin(),Students.end());
    vector<Professor*> :: iterator it2 = Professors.begin();
    while (it2 != Professors.end()){
        delete *it2;
        it2++;
    }
    Professors.erase(Professors.begin(),Professors.end());
    vector<Course*> :: iterator it3 = Courses.begin();
    while (it3 != Courses.end()){
        delete *it3;
        it3++;
    }
    Courses.erase(Courses.begin(),Courses.end());


    //we initialize every vector of the class Secretary  
    vector<Student*> :: const_iterator itr1 = S.Students.begin(); // Const iterator because secretary S is a const variable
    while(itr1 != S.Students.end()){
    
        Student* temp1 = new Student((*itr1)->GetName(),(*itr1)->GetAge(),(*itr1)->Getemail(),(*itr1)->GetSex(),(*itr1)->GetAM(),(*itr1)->GetSemester());
        temp1->decreaseCount(); //We reduce the counter so we won't count the Student twice
        Students.insert(Students.end(), temp1);
        itr1++;
    }
    vector<Professor*> :: const_iterator itr2 = S.Professors.begin(); 
    while(itr2 != S.Professors.end()){
        
        Professor* temp2= new Professor((*itr2)->GetName(),(*itr2)->Getemail(),(*itr2)->GetAge(),(*itr2)->GetSex(),(*itr2)->GetCourses());
        temp2->decreaseCount(); //We reduce the counter so we won't count the Professor twice
        Professors.insert(Professors.end(), temp2);
        itr2++;
    }
    vector<Course*> :: const_iterator itr3 = S.Courses.begin(); // Const iterator because secretary S is a const variable
    while(itr3 != S.Courses.end()){
        
        Course* temp3 = new Course((*itr3)->GetName(),(*itr3)->GetSemester(),(*itr3)->GetECTS(),(*itr3)->GetMandatory());
        Courses.insert(Courses.end(), temp3);
        itr3++;
    }

    //we initialize the private member
    MandatoryCount = S.MandatoryCount;
}

//function for the start of the semester 
void Secretary :: StartSemester(){
    vector<Student*> :: iterator it = Students.begin();
    string sub;
    bool Flag;
    //for every student we have to add the courses that they are going to study
    while(it != Students.end()){
        cout << "Which subject do you want to add to " << (*it)->GetName() << "(type end if you don't want to add anymore)-> ";
        getline(cin>>ws , sub);
        while(sub != string("end")|| sub != string("End")){
            if(sub == string("end")|| sub == string("End")){
                break;
            }
            try{
                Flag = RegisterStudent((*it)->GetName(),sub);
                if(Flag == false){
                    throw string("Couldn't add subject");
                }
            }
            catch(string error){
                cout << "Error-> " << error << endl << endl;
            }
            cout << "Which subject do you want to add to " << (*it)->GetName() << "(type end if you don't want to add anymore)-> ";
            getline(cin>>ws , sub);
        }
        it++;
    }
    //also for every course we make sure that the professor hasn't changed
    vector<Course*> :: iterator it2 = Courses.begin();
    while(it2 != Courses.end()){
        cout << "Do you want to change the professor of the course " << ((*it2)->GetName()) << "(True/False)-> ";
        getline(cin>>ws , sub);
        if(sub == "True" || sub == "true"){
            cout << "Which Professor do you want to assign? ->";
            getline(cin>>ws , sub);
            Flag = AssignProf(sub,(*it2)->GetName());
            while(Flag == false){
                cout << "Wrong input!" <<endl;
                cout << "Which Professor do you want to assign? ->";
                getline(cin>>ws , sub);
                Flag = AssignProf(sub,(*it2)->GetName());
            }
        }
        it2++;
    }
}

//function for the end of the semester 
void Secretary :: EndSemester(){
    vector<Student*> :: iterator it = Students.begin();
    vector<Course*> C;
    vector<Course*> :: const_iterator it2;
    float Grade;

    //at the end of the semester we add the grades for every course that they participated the last semester
    while(it != Students.end()){
        (*it)->SetSemester(((*it)->GetSemester())+1);
        C = (*it)->GetSubjects();
        it2 = C.begin();
        while(it2 != C.end()){
            cout << "What Grade did " << (*it)->GetName() << " get in " << (*it2)->GetName() << "-> ";
            cin >> Grade;
            while(Grade < 0 || Grade > 10){
                cout << "Wrong input" << endl;
                cout << "What Grade did " << (*it)->GetName() << " get in " << (*it2)->GetName() << "-> ";
                cin >> Grade;
            }
            PassCourse(*it,*it2,Grade);
            it2++;
        }
        it++;
    }

}

//function that is called by the main program to update the files after the end of the program 
void Secretary :: printfiles(void){
    ofstream fout;

    //print the courses file with the changed data 
    fout.open("Courses.txt");
    vector<Course*> :: iterator it = Courses.begin();
    while(it != Courses.end()){
        fout<< (*it)->GetName() << endl;
        fout<< (*it)->GetSemester() <<endl;
        fout<< (*it)->GetECTS() <<endl;
        if(it+1!= Courses.end()){  //this helps not to print another line at the end of the file 
            fout<< (*it)->GetMandatory()<<endl;
        }
        else{
            fout<< (*it)->GetMandatory();
        }
        it++;
    }
    fout.close();

    //print the students file with the changed data 
    fout.open("Students.txt");
    vector<Student*> :: iterator it2 = Students.begin();
    while(it2 != Students.end()){
        fout<< (*it2)->GetName() <<endl;
        fout<< (*it2)->GetSex()<<endl ;
        fout<< (*it2)->GetAge() <<endl;
        fout<< (*it2)->Getemail()<<endl ;
        fout<< (*it2)->GetAM()<<endl ;
        fout<< (*it2)->GetSemester() <<endl;
        vector<string> temp1= (*it2)->getnamemap();// this function returns the courses that the students are taking
        vector<float> temp2= (*it2)->getgrademap();// this function returns the grade of the course
        vector<string> :: iterator stIt = temp1.begin();
        vector<float> :: iterator fIt = temp2.begin();
        while(stIt != temp1.end()){
            fout<< *stIt <<endl;
            fout<< *fIt <<endl;
            stIt++;
            fIt++;
        }
        it2++;
        if(it2!= Students.end()){
            fout <<"end"<<endl;
        }
        else{
            fout <<"end";
        }
    }
    fout.close();

    //print the professors file with the changed data 
    fout.open("Professors.txt");
    vector<Professor*> :: iterator it3 = Professors.begin();
    while(it3!= Professors.end()){
        
        fout<< (*it3)->GetName() <<endl;
        fout<< (*it3)->GetSex()<<endl ;
        fout<< (*it3)->GetAge() <<endl;
        fout<< (*it3)->Getemail()<<endl ;
        vector<Course*> T=(*it3)->GetCourses();
        vector<Course*> :: iterator itr2 = T.begin();
        while(itr2 != T.end()){
            fout<< (*itr2)->GetName()<<endl;
            itr2++;
        }
        it3++;
        if(it3!= Professors.end()){//this helps not to print another line at the end of the file 
            fout <<"end"<<endl;
        }
        else{
            fout <<"end";
        }
    }
    fout.close();
}

/////////////////////////////////////////////
///////Functions of the class Person/////////
////////////////////////////////////////////

//constructors
Person :: Person(){
    Name = "undefined";
    Sex = "Undefined";
    age = 0;
    email = "undefined";
    count++;
}

Person :: Person(string Name, string Sex , int age ,string email){
    this->Name = Name;
    this->age = age;
    this->email = email;
    this->Sex = Sex;
    count++;
}

//pure vitual destructor
Person :: ~Person(){
    count--;
}

//Set functions for the private members of the class Person
void Person :: SetAge(int age){
    this->age = age;
}

void Person :: SetSex(string Sex){
    this->Sex= Sex;
}

void Person :: SetName(string Name){
    this->Name= Name;
}

void Person :: Setemail(string email){
    this->email = email;
}

//Get functions for the private members of the class Person
int Person :: GetAge(void) const{
    return age;
}

string Person :: GetSex(void) const{
    return Sex;
}

string Person :: GetName(void) const{
    return Name;
}

string Person :: Getemail(void) const{
    return email;
}

//Functions for the counter 
void Person :: printCount(){
    cout << "We have this ammount of people: " << count << endl; 
}

void Person :: decreaseCount(){
    count--;
}

/////////////////////////////////////////////
///////Functions of the Student//////////////
////////////////////////////////////////////

//constructors
Student :: Student():Person(){
    total_ects = 0;
    AM = "0000000";
    semester = 1;
}

Student :: Student(string Name , int age , string email, string Sex,string AM,int semester):Person(Name,Sex,age,email){

    this->AM = AM;
    this->semester = semester;
}

//destructor
Student :: ~Student(){

    //delete map 
    PassedCourses.clear();

    //delete vector
    vector<Course*> :: iterator it = Courses.begin();
    while (it != Courses.end()){
        delete *it;
        it++;// next object 
    }
    Courses.erase(Courses.begin(),Courses.end());

}

//Set functions
void Student :: SetSemester(int semester){
    this->semester = semester;
}

void Student :: SetAM(string AM){
    this->AM = AM;
}

void Student :: SetECTS(int total_ects){
    this->total_ects = total_ects;
}

//Get functions
int Student :: GetECTS(void) const{
    return total_ects;
}

string Student :: GetAM(void) const{
    return AM;
}

int Student :: GetSemester(void) const{
    return semester;
}

int Student :: GetMandatoryCount(void)const{
    return countMandatory;
}

vector<Course*> Student :: GetSubjects(void) const{
    return Courses;
}

//function that updates the total ects of the student 
void Student :: UpdateECTS(Course C){
    total_ects += C.GetECTS();
}

//we update the course by assigning a grade 
void Student :: UpdateCourse(Course* C,float Grade){
    Grades G; 
    //if the grade is greater or equal than five then we have to update the ects ,the counter for the mandatory courses 
    //and the data structures we have in the class
    if(Grade >= 5){
        UpdateECTS(*C);
        if(C->GetMandatory()){
            countMandatory++;
        }
        G.SetGrade(Grade);
        G.SetSemester(C->GetSemester());
        PassedCourses[C->GetName()] = G;
    }
    C->SetGrade(GetName(),Grade);
}

//we print the grades of every passed course in the specific year 
void Student :: PrintYear(int Year){
    bool flag = false;
    map<string,Grades>::iterator it = PassedCourses.begin();
    // if the year is zero then print all the grades of every passed course
    if(Year == 0){
        while(it != PassedCourses.end()){
            cout << "Course:  "<< it->first << "    Grade: " << it->second.GetGrade() << endl;
            it++;
            flag=true;
        }      
    }
    //Otherwise print all the grades of every passed course in the specific year
    else{
        while(it != PassedCourses.end()){
            if (it->second.GetSemester() == Year*2 || it->second.GetSemester() == Year*2-1){
                cout << "Course:  "<< it->first << "    Grade: " << it->second.GetGrade() << endl;
                flag=true;
            }
            it++;
        }
    }
    if(!flag){
        cout<< "The student doesn't have any courses in this year"<< endl;
    }
    cout <<endl;
}

//we print the grades of every passed course in the specific semester
void Student :: PrintSemester(int Semester){
    bool flag= false;
    map<string,Grades>::iterator it = PassedCourses.begin();
    while(it != PassedCourses.end()){
        if (it->second.GetSemester() == Semester){ //we check if the course is in the semester we want to print 
            cout << "Course:  "<< it->first << "    Grade: " << it->second.GetGrade() << endl;
            flag=true;
        }
        it++;
    }
    if(!flag){
        cout<< "The student doesn't have any courses in this semester"<< endl;
    }
    cout <<endl;
}

//function that assign a course to the student
void Student :: AssignCourse(Course* C){
    Courses.insert(Courses.end(),C);
}

//Overload function for the equal operator
void Student :: operator=(const Student &S){

    //we itialize the private members
    total_ects=S.total_ects;
    AM= S.AM;
    semester=S.semester;
    countMandatory= S.countMandatory;

    //we delete the map with the old data and we insert the new data 
    PassedCourses.clear();
    multimap<string,Grades> :: const_iterator itr = S.PassedCourses.begin();
    while(itr != S.PassedCourses.end()){
        PassedCourses.insert(pair<string,Grades>(itr->first,itr->second));
        itr++;
    }

    //we delete the vector with the old objects and we insert the new objects  
    vector<Course*> :: iterator it = Courses.begin();
    while (it != Courses.end()){
        delete *it;
        it++;
    }
    Courses.erase(Courses.begin(),Courses.end());
    vector<Course*> :: const_iterator it1 = S.Courses.begin();
    while (it1!= S.Courses.end()){
        Course* temp = new Course((*it1)->GetName(),(*it1)->GetSemester(),(*it1)->GetECTS(),(*it1)->GetMandatory());
        Courses.insert(Courses.end(), temp);
        it1++; 
    }

}

//Overload function for the input operator
istream &operator>> (istream &str , Student *S){
   cout << "Give the student's name: ";
    getline(str>>ws , S->Name);//reads a string with the spaces because the name contains and the surname
    cout << "Give the student's age: ";
    str >> S->age;
    cout << "Give the student's email: ";
    str >> S->email;
    cout << "Give the student's sex: ";
    str >> S->Sex;
    cout << "Give the student's total ects: ";
    str >> S->total_ects;
    cout << "Give the student's register number: ";
    str >> S->AM;
    cout << "Give the student's current semester ";
    str >> S->semester;
    return str;
}

//functions that helps with updating the files
vector<string>  Student ::  getnamemap(void){
    vector<string> temp;
    map<string,Grades> :: iterator itr = PassedCourses.begin();
    while (itr!=PassedCourses.end()){
        temp.insert(temp.end(),itr->first);
        itr++;
    }
    return temp;
}
 vector<float> Student :: getgrademap(void){
    vector<float> temp;
    map<string,Grades> :: iterator itr = PassedCourses.begin();
    while (itr!=PassedCourses.end()){
        temp.insert(temp.end(),itr->second.GetGrade());
        itr++;
    }
    return temp;
}

///////////////////////////////////////////////////////
///////Functions for the nested class Grades///////////
///////////////////////////////////////////////////////

//constructors and destructor
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

/////////////////////////////////////////////
///////Functions of the Professor///////////
////////////////////////////////////////////

//constructors
Professor :: Professor():Person(){}

Professor :: Professor(string Name , string email, int age , string Sex): Person(Name,Sex,age,email){}

Professor :: Professor(string Name , string email, int age , string Sex,vector<Course*>c): Person(Name,Sex,age,email){
    vector<Course*> Courses(c.begin(), c.end());
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

vector<Course*> Professor ::GetCourses(void) const{
    return Courses;
}

//function for removing a course that the professor no longer teaches
void Professor :: RemoveCourse(string course){
    vector<Course*> :: iterator it = Courses.begin();
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
    vector<Course*> :: iterator it = Courses.begin();
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
    map<string,float> G;
    vector<Course*> :: iterator it = Courses.begin();
    while (it != Courses.end()){
        int count = 0;
        SucRate = 0.0;
        TotalStudents = 0;
        PassedStudents = 0;
        G = (*it)->GetMap();
        map<string,float> :: iterator itr = G.begin();
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
        cout << (*it)->GetName() << " statistics are: " << endl;
        cout << "Success Rate of the Course :   " << SucRate << "%  and the average grade is :  " << MO << endl;
        it++;
    }
    cout<< endl;
}

//Overload function for the input operator
istream &operator>>(istream &str , Professor* P){
    cout << "Give the professor's name: ";
    getline(str>>ws , P->Name);//reads a string with the spaces because the name contains and the surname
    cout << "Give the professor's age: ";
    str >> P->age;
    cout << "Give the professor's email: ";
    str >> P->email;
    cout << "Give the professor's sex: ";
    str >> P->Sex;
    return str;
}

//Overload function for the equal operator
void Professor :: operator=(const Professor &P){

    //we delete the vector with the old objects and we insert the new objects 
    vector<Course*> :: iterator it = Courses.begin();
    while (it != Courses.end()){
        delete *it;
        it++;
    }
    Courses.erase(Courses.begin(),Courses.end());
    vector<Course*> :: const_iterator it1 = P.Courses.begin();
    while (it1!= P.Courses.end()){
        Course* temp = new Course((*it1)->GetName(),(*it1)->GetSemester(),(*it1)->GetECTS(),(*it1)->GetMandatory());
        Courses.insert(Courses.end(), temp);
        it1++;
    }
}
/////////////////////////////////////////////
///////Functions of the Course //////////////
////////////////////////////////////////////

//constructors
Course :: Course(){
    Name= "undefined";
    semester = 0; 
    ects=0;
    mandatory=0;
    Prof= new Professor();
}

Course :: Course(string Name, int semester ,int ects ,bool mandatory){
    this->Name= Name;
    this->semester = semester; 
    this->ects=ects;
    this->mandatory=mandatory;
   
}

//destructor
Course :: ~Course(){
    Grades.clear();
}

//set functions
void Course :: SetSemester(int semester){
    this->semester = semester;
}

void Course :: SetName(string Name){
    this->Name = Name;
}

void Course :: SetECTS(int ects){
    this->ects = ects;
}

void Course :: SetMandatory(bool mandatory){
    this->mandatory = mandatory;
}

void Course :: SetProfessor(Professor* Prof){
    this->Prof = Prof;
    Prof->SetCourses(this);
}

void Course :: SetGrade(string S,int G){
    Grades[S] = G;
}

//get functions
string Course :: GetName(void) const{
    return Name;
}

int Course :: GetSemester(void) const{
    return semester;
}

int Course :: GetECTS(void) const{
    return ects;
}

bool Course :: GetMandatory(void) const{
    return mandatory;
}

Professor* Course:: GetProfessor(void)const{
    return Prof;
}

map<string,float> Course :: GetMap(void) const{
    return Grades;
}

//Overload function for the output operator that prints the courses with the grades that she passed in that semester
ostream &operator<<(ostream &str , Course *C){
    map<string,float> :: iterator it = C->Grades.begin();
    str << "The students that passed " << C->Name << " are:" << endl;
    while(it != C->Grades.end()){
        if(it->second >=5){
            str << "Name:   " << it->first << "   Grade:" << it->second << endl;
        }
        it++;
    }
    return str;
}

//Overload function for the input operator
istream &operator>>(istream &str , Course* C){
    string temp;
    cout << "Give the course's name: ";
    getline(str>>ws , C->Name);//reads a string with the spaces because the course can contain two words
    cout << "Give the course's semester: ";
    str >> C->semester;
    cout << "Give the course's ects: ";
    str >> C->ects;
    cout << "Is this course mandatory? (True/False): ";
    str >> temp ;
    if (temp == "True" || temp == "true")
        C->mandatory = 1;
    else
        C->mandatory = 0;
    
    return str;
}

//Overload function for the equal operator
void Course :: operator=(const Course &C){

    //we itialize the private members
    Name= C.Name;
    semester= C.semester;
    ects = C.ects;
    mandatory= C.mandatory;

    //we delete the old professor and initialize the new one 
    delete Prof;
    Prof= C.Prof;

    //we delete the map with the old data and we insert the new data 
    Grades.clear();
    multimap<string,float> :: const_iterator itr = C.Grades.begin();
    while(itr != C.Grades.end()){
        Grades.insert(pair<string,float>(itr->first,itr->second));
        itr++;
    }

}