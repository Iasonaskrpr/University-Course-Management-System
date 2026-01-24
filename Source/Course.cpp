#include <Course.h>
#include <string>

//constructors
Course :: Course(){
    Name= "undefined";
    semester = 0; 
    ects=0;
    mandatory=0;
    Prof= new Professor();
}

Course :: Course(std::string Name, int semester ,int ects ,bool mandatory){
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