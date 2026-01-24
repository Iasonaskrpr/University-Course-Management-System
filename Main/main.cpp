#include <Course.h>
#include <Secretary.h>
#include <Student.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
// TODO: Turn this into a simple UI with the same options

int main(void){
    
    Secretary S;
    string fun;
    int data;
    bool flag = true;

    //set the count with the mandatory courses
    S.SetMandatoryCount(14);
    
    //variables that we need to read from files 
    ifstream fin;
    string name, sex,email,AM,c,endline;
    int age,sem, ects ,g;
    bool mandatory;

    //we read from file Courses.txt and insert them to the vector Courses of the secretary
    fin.open("Data/Courses.txt");
    while(fin){
        getline(fin,name);
        fin >> sem;
        fin >> ects;
        fin >> mandatory;
        getline(fin,endline);
        Course* C = new Course(name,sem,ects,mandatory);
        S + C; //overload of the addiction operator  
    }
    fin.close();

    //we read from file Students.txt and insert them to the vector of Students the secretary
    fin.open("Data/Students.txt");
    while(!fin.eof()){
        getline(fin,name);
        getline(fin,sex);
        fin >> age;
        getline(fin,endline);
        getline(fin,email);
        getline(fin,AM);
        fin >> sem;
        getline(fin,endline);
        Student* Stud = new Student(name,age,email,sex,AM,sem); 
        S + Stud;  //overload of the addiction operator 

        //read every course and the grade until we read the word end 
        getline(fin,c);
        while(c != "end"){
            fin >> g;
            getline(fin,endline);
            Course* C = S.FindCourse(c);
            if(C != NULL){
                S.PassCourse(Stud,C,g);//this function update the ects if the student passed the course and the grades
            }
            getline(fin,c);
        }
    }
    fin.close();
    S.StartSemester();
    //we read from file Professors.txt and insert them to the vector of Professors the secretary
    fin.open("Data/Professors.txt");
    while(!fin.eof()){
        getline(fin,name);
        getline(fin,sex);
        fin>> age;
        getline(fin,endline);
        getline(fin,email);
        Professor* P = new Professor(name,email,age,sex); 
        S + P; //overload of the addiction operator 
        getline(fin,c);
        while(c != "end"){
            S.AssignProf(name,c);
            getline(fin,c);
        }
    }
    fin.close();
    while (flag){
        try{
            cout << "1) Modify a Student" << endl;
            cout << "2) Modify a Professor" << endl;
            cout << "3) Print Students that passed a course" << endl;
            cout << "4) Print a Professor's stats of last semester" << endl;
            cout << "5) Print a student's detailed student score" << endl;
            cout << "6) Write in a file Students that passed in a Course last semester" << endl;
            cout << "7) End semester" << endl;
            cout << "8) Exit system" << endl;
            cout << "Enter which function you want to perform-> ";
            cin >> fun;
            cout << endl;
            if (fun == "1"){
                try{
                    cout <<  "1) Change something in a student" << endl;
                    cout <<  "2) Create a student" << endl;
                    cout <<  "3) Delete a student" << endl;
                    cout << "Enter which function you want to perform-> ";
                    cin >> fun;
                    if(fun == "1"){
                        try{
                            cout << "Which Student do you want to change? -> ";
                            getline(cin>>ws , fun);//read the line with spaces 
                            
                            //if the student wasn't found then we throw an exception
                            Student* Stud = S.FindStud(fun);
                            if(Stud == NULL){
                                throw string("Student wasnt found");
                            }

                            cout << "1) Change email" << endl;
                            cout << "2) Change Semester"<< endl;
                            cout << "Enter which function you want to perform->  ";
                            cin >> fun;

                            if (fun == "1"){
                                cout << "What do you want " << Stud->GetName() <<"'s email to be? ->";
                                cin >> fun;
                                Stud->Setemail(fun);
                                cout << "The change has been completed" << endl << endl;
                            }
                            else if (fun == "2"){
                                cout << "What do you want " << Stud->GetName() <<"'s Semester to be? ->";
                                cin >> data;
                                Stud->SetSemester(data);
                                cout << "The change has been completed" << endl << endl;
                            }
                            else{
                                throw string("wrong input");
                            }
                        }
                        catch(string message){
                            cerr << "Error-> " << message << endl << endl;
                        }
                    }
                    else if(fun == "2"){
                        //create a new student and insert them into the vector 
                        Student* Stud = new Student;
                        cin >> Stud;
                        S+Stud;
                        cout<< "The student has been created successfully"<<endl<< endl;
                    }
                    else if(fun == "3"){
                        cout << "Which student do you want to delete-> ";
                        getline(cin>>ws , fun);//read the line with spaces  
                        if(S.FindStud(fun) == NULL){
                            throw string("Student wasnt found");
                        }else{
                            S.DeleteStudent(fun);
                            cout <<"The student was deleted successfully"<<endl<<endl;
                        }
                    }
                    else{
                        throw string("wrong input");
                    }
                }
                catch(string error){
                    cout << "Error->" << error <<endl << endl;
                }
            }
            else if (fun == "2"){
                try{
                    cout <<  "1) Change something in a Professor" << endl;
                    cout <<  "2) Create a Professor" << endl;
                    cout <<  "3) Delete a Professor" << endl;
                    cout << "Enter which function you want to perform-> ";
                    cin >> fun;
                    if(fun == "1"){
                        try{
                            cout << "Which Professor do you want to change? -> ";
                            getline(cin>>ws , fun);//read the line with spaces

                            //if the professor wasn't found then we throw an exception
                            Professor* Prof = S.FindProf(fun);
                            if(Prof == NULL){
                                throw string("Professor wasnt found");
                            }

                            cout << "1) Change Email" << endl;
                            cout << "2) Add a Course" << endl;
                            cout << "Enter which function you want to perform->  ";
                            cin >> fun;

                            if (fun == "1"){
                                cout << "What do you want" << Prof->GetName() <<"'s email to be? ->";
                                cin >> fun;
                                Prof->Setemail(fun);
                                cout << "The change has been completed" << endl << endl;
                            }
                            else if(fun == "2"){
                                cout << "Enter Course -> ";
                                getline(cin>>ws , fun);//read the line with spaces 
                                Course* C = S.FindCourse(fun);
                                while(C != NULL){ 
                                    cout << "Course added!" << endl;
                                    Prof->SetCourses(C);
                                    cout << "Enter Course -> ";
                                    getline(cin>>ws , fun);//read the line with spaces
                                    C = S.FindCourse(fun);
                                }
                            }
                            else{
                                throw string("Wrong input");
                            }
                        }
                        catch(string message){
                            cout << "Error-> " << message << endl <<endl; 
                        }
                    }
                    else if (fun == "2"){
                        //we create a new professor and insert him in the vector 
                        Professor* Prof = new Professor;
                        cin >> Prof;
                        S+Prof;
                        cout<< "The Professor has been created successfully"<<endl;
                    }
                    else if(fun == "3"){
                        cout << "Which Professor do you want to delete-> ";
                        getline(cin>>ws , fun);//read the line with spaces  
                        if(S.FindProf(fun) == NULL){
                            throw string("Professor wasnt found");
                        }else{
                            S.DeleteProf(fun);
                            cout <<"The professor was deleted successfully"<<endl<<endl;
                        }
                    }
                    else{
                       throw string("wrong input");
                    }
                }
                catch(string message){
                    cout << "Error-> " << message << endl << endl;
                }
            }
            else if (fun == "3"){
                try{
                    cout << "For which course do you want to print students that passed ->";
                    getline(cin>>ws , fun);

                    //if the course doesn't exist throw exception
                    Course* C = S.FindCourse(fun);
                    if(C == NULL){
                        throw string("Couldn't find course");
                    }
                    cout << C; //overload of the output operator to print the students who passed
                }
                catch(string message){
                    cout << "Error-> " << message << endl << endl;
                }
            }
            else if (fun == "4"){
                try{
                    cout << "For which Professor do you want to print stats ->";
                    getline(cin>>ws , fun);

                    //if the Professor doesn't exist throw exception
                    Professor* Prof = S.FindProf(fun);
                    if(Prof == NULL){
                        throw string("Couldnt find professor");
                    }

                    Prof->PrintStats();
                }
                catch(string message){
                    cout << "Error-> " << message << endl << endl;
                }
            }
            else if (fun == "5"){
                try{
                    int sem;
                    cout << "Which student's detailed score do you want to print?-> ";
                    getline(cin>>ws , fun);

                    //if the Student doesn't exist throw exception
                    Student* Stud = S.FindStud(fun);
                    if (Stud == NULL){
                        throw  string("Failed to find student");
                    }

                    cout << "1) Print a semester's detailed score" << endl;
                    cout << "2) Print a Year's detailed score" << endl;
                    cout << "3) Print detailed score of all semesters" << endl;
                    cout << "Enter which function you want to perform-> ";
                    cin >> fun;

                    if (fun == "1"){
                        cout << "Enter the semester you want to print ->";
                        cin >> sem;
                        Stud->PrintSemester(sem);
                    }
                    else if(fun == "2"){
                        cout << "Enter the year you want to print ->";
                        cin >> sem;
                        Stud->PrintYear(sem);
                    }
                    else if (fun == "3"){
                        Stud->PrintYear(0);
                    }
                    else{
                        throw string("Wrong input");
                    }
                }
                catch(string message){
                    cout << "Error-> " << message << endl << endl;
                }
            }
            else if (fun == "6"){
                try{
                    cout << "From which course do you want to save the passed students? ->";
                    getline(cin>>ws , fun);

                    //if the Course doesn't exist throw exception
                    Course* C = S.FindCourse(fun);
                    if(C == NULL){
                      throw std::string("Couldn't find course");
                    }
                    
                    //write contents of the map in a file "data.txt"
                    std::unordered_map<std::string, float> G = C->GetMap();
                    ofstream fout;
                    fout.open("data.txt");
                    fout<< " Students that passed "<< fun <<endl;
                    std::unordered_map<string, float>::iterator it = G.begin();
                    while(it != G.end()){
                        fout << "Name:   " << it->first << "   Grade:" << it->second << endl;
                        it++;
                    }
                    fout.close();
                    cout << "Wrote students that passed the course last semster in the file" << endl<< endl;
                }
                catch(string message){
                    cout << "Error-> " << message << endl << endl;
                }
            }
            else if (fun == "7"){
                bool Flag2 = true;
                cout << "Semester ended!" << endl;
                S.EndSemester();
                while(Flag2){
                    try{
                        cout << "1) Modify a Student" << endl; 
                        cout << "2) Modify a Professor" << endl;
                        cout << "3) Modify a Course" << endl;
                        cout << "4) Print Students that passed in a Course" << endl;
                        cout << "5) Print a Professor's stats" << endl;
                        cout << "6) Enroll a student in a course" << endl; 
                        cout << "7) Assign Professor to a Course" << endl; 
                        cout << "8) Print a student's detailed student score" << endl;
                        cout << "9) Print students that can get a degree" << endl;
                        cout << "10)Write in a file Students that passed a Course" << endl;
                        cout << "11) Start semester" << endl;
                        cout << "12) Exit system" << endl;
                        cout << "Enter which function you want to perform-> ";
                        cin >> fun;
                        cout << endl;
                        if (fun == "1"){
                            try{
                                    cout <<  "1) Change something in a student" << endl;
                                    cout <<  "2) Create a student" << endl;
                                    cout <<  "3) Delete a student" << endl;
                                    cout << "Enter which function you want to perform-> ";
                                    cin >> fun;
                                    if(fun == "1"){
                                        try{
                                            cout << "Which Student do you want to change? -> ";
                                            getline(cin>>ws , fun);//read the line with spaces 
                                            
                                            //if the student wasn't found then we throw an exception
                                            Student* Stud = S.FindStud(fun);
                                            if(Stud == NULL){
                                                throw string("Student wasnt found");
                                            }

                                            cout << "1) Change email" << endl;
                                            cout << "2) Change Semester"<< endl;
                                            cout << "Enter which function you want to perform->  ";
                                            cin >> fun;

                                            if (fun == "1"){
                                                cout << "What do you want " << Stud->GetName() <<"'s email to be? ->";
                                                cin >> fun;
                                                Stud->Setemail(fun);
                                                cout << "The change has been completed" << endl << endl;
                                            }
                                            else if (fun == "2"){
                                                cout << "What do you want " << Stud->GetName() <<"'s Semester to be? ->";
                                                cin >> data;
                                                Stud->SetSemester(data);
                                                cout << "The change has been completed" << endl << endl;
                                            }
                                            else{
                                                throw string("wrong input");
                                            }
                                        }
                                        catch(string message){
                                            cerr << "Error-> " << message << endl << endl;
                                        }
                                    }
                                    else if(fun == "2"){
                                        //create a new student and insert them into the vector 
                                        Student* Stud = new Student;
                                        cin >> Stud;
                                        S+Stud;
                                        cout<< "The student has been created successfully"<<endl;
                                    }
                                    else if(fun == "3"){
                                        cout << "Which student do you want to delete-> ";
                                        getline(cin>>ws , fun);//read the line with spaces  
                                        if(S.FindStud(fun) == NULL){
                                            throw string("Student wasnt found");
                                        }else{
                                            S.DeleteStudent(fun);
                                            cout <<"The student was deleted successfully"<<endl<<endl;
                                        }
                                    }
                                    else{
                                        throw string("wrong input");
                                    }
                                }
                                catch(string error){
                                    cout << "Error->" << error <<endl << endl;
                                }
                            }
                        else if (fun == "2"){
                             try{
                                cout <<  "1) Change something in a Professor" << endl;
                                cout <<  "2) Create a Professor" << endl;
                                cout <<  "3) Delete a Professor" << endl;
                                cout << "Enter which function you want to perform-> ";
                                cin >> fun;
                                if(fun == "1"){
                                    try{
                                        cout << "Which Professor do you want to change? -> ";
                                        getline(cin>>ws , fun);//read the line with spaces

                                        Professor* Prof = S.FindProf(fun);
                                        if(Prof == NULL){
                                            throw string("Professor wasnt found");
                                        }

                                        cout << "1) Change Email" << endl;
                                        cout << "2) Add a Course" << endl;
                                        cout << "Enter which function you want to perform->  ";
                                        cin >> fun;

                                        if (fun == "1"){
                                            cout << "What do you want" << Prof->GetName() <<"'s email to be? ->";
                                            cin >> fun;
                                            Prof->Setemail(fun);
                                            cout << "The change has been completed" << endl << endl;
                                        }
                                        else if(fun == "2"){
                                            cout << "Enter Course -> ";
                                            getline(cin>>ws , fun);//read the line with spaces 
                                            Course* C = S.FindCourse(fun);
                                            while(C != NULL){ 
                                                
                                                cout << "Course added!" << endl;
                                                Prof->SetCourses(C);
                                                cout << "Enter Course -> ";
                                                getline(cin>>ws , fun);//read the line with spaces
                                                C = S.FindCourse(fun);
                                            }
                                        }
                                        else{
                                            throw string("Wrong input");
                                        }
                                    }
                                    catch(string message){
                                        cout << "Error-> " << message << endl <<endl; 
                                    }
                                }
                                else if (fun == "2"){
                                    Professor* Prof = new Professor;
                                    cin >> Prof;
                                    S+Prof;
                                    cout<< "The Professor has been created successfully"<<endl;
                                }
                                else if(fun == "3"){
                                    cout << "Which Professor do you want to delete-> ";
                                    getline(cin>>ws , fun);//read the line with spaces  
                                    if(S.FindProf(fun) == NULL){
                                        throw string("Professor wasnt found");
                                    }else{
                                        S.DeleteProf(fun);
                                        cout <<"The professor was deleted successfully"<<endl<<endl;
                                    }
                                }
                                else{
                                throw string("wrong input");
                                }
                            }
                            catch(string message){
                                cout << "Error-> " << message << endl << endl;
                            }
                        }
                        else if (fun == "3"){
                            try{
                                cout <<  "1) Change something in a Course" << endl;
                                cout <<  "2) Create a Course" << endl;
                                cout <<  "3) Delete a Course" << endl;
                                cout << "Enter which function you want to perform-> ";
                                cin >> fun;
                                if(fun == "1"){
                                    try{
                                        cout << "Which course do you want to change? ->";
                                        getline(cin>>ws , fun);

                                        //create a new Course and insert them into the vector 
                                        Course* C = S.FindCourse(fun);
                                        if (C == NULL){
                                            throw string("Couldn't find Course");
                                        }
                         
                                        cout << "1) Change Name of the Course" << endl;
                                        cout << "2) Change Semester" << endl;
                                        cout << "3) Switch mandatory" << endl;
                                        cout << "4) Change Professor " << endl;
                                        cout << "Enter which function you want to perform-> ";
                                        cin >> fun;
                                        if(fun == "1"){
                                            cout << "Enter the new name of the course ->";
                                            getline(cin>>ws , fun);
                                            C->SetName(fun);
                                            cout << "The change has been completed" << endl << endl;
                                        }
                                        else if(fun == "2"){
                                            cout << "Enter the new semester of the course ->";
                                            cin >> data;
                                            C->SetSemester(data);
                                            cout << "The change has been completed" << endl << endl;
                                        }
                                        else if(fun == "3"){
                                            if(C->GetMandatory()){
                                                C->SetMandatory(false);
                                                cout << "Course is now a course of choice!" << endl<< endl;
                                            }
                                            else{
                                                C->SetMandatory(true);
                                                cout << "Course is now mandatory!" << endl<< endl;
                                            }
                                        }
                                        else if(fun == "4"){
                                            cout << "What Professor do you want to be assigned to the course? ->";
                                            getline(cin>>ws , fun);
                                            Professor* Prof = S.FindProf(fun);
                                            if(Prof == NULL){
                                                throw string("Couldn't find professor");
                                            }
                                            C->SetProfessor(Prof);
                                            cout << "Changed Professor!" << endl<< endl;
                                        }
                                        else{
                                            throw string("Wrong input");
                                        }
                                    }
                                    catch(string error){
                                        cout << "Error-> " << error << endl << endl;
                                    }
                                }
                                else if (fun == "2"){
                                    //cerate a course add to the vector and assign a professor
                                    Course* C = new Course;
                                    cin >> C;
                                    S+C;
                                    cout << "Which Professor do you want to assign to the course-> ";
                                    getline(cin>>ws , fun);
                                    Professor* Prof = S.FindProf(fun);
                                    if(Prof == NULL){
                                        throw string("Couldn't find professor");
                                    }
                                    C->SetProfessor(Prof);
                                    cout<< "The Course has been created successfully"<<endl<< endl;  
                                }
                                else if (fun == "3"){
                                    cout << "Which course do you want to delete? ->";
                                    getline(cin>>ws , fun);
                                    if(S.FindCourse(fun) == NULL){
                                        throw string("Course wasnt found");
                                    }else{
                                        S.DeleteCourse(fun);
                                        cout <<"The course was deleted successfully"<<endl<<endl;
                                    }
                                    
                                }
                                else{
                                    throw string("Wrong input");
                                }
                            }
                            catch(string message){
                                cout << "Error-> " << message << endl << endl;
                            }
                        }
                        else if (fun == "4"){
                            try{
                                cout << "For which course do you want to print students that passed ->";
                                getline(cin>>ws , fun);
                                
                                //if the course wasn't found then we throw an exception
                                Course* C = S.FindCourse(fun);
                                if(C == NULL){
                                    throw string("Couldn't find course");
                                }
                                cout << C;
                            }
                            catch(string message){
                                cout << "Error-> " << message << endl << endl;
                            }
                        }
                        else if (fun == "5"){
                            try{
                                cout << "For which Professor do you want to print stats ->";
                                getline(cin>>ws , fun);

                                //if the Professor wasn't found then we throw an exception
                                Professor* Prof = S.FindProf(fun);
                                if(Prof == NULL){
                                    throw string("Couldnt find professor");
                                }
                                Prof->PrintStats();
                            }
                            catch(string message){
                                cout << "Error-> " << message << endl << endl;
                            }
                        }
                        else if (fun == "6"){
                            try{
                                string st;
                                string cs;

                                //if the student wasn't found then we throw an exception
                                cout << "Which student do you want to enroll in a course?-> ";
                                getline(cin>>ws , st);
                                if(S.FindStud(st)==NULL){
                                    throw string("Could't find Student");
                                }

                                // if the course wasn't found then we throw an exception
                                cout << "Which Course do you want " << st <<" to enroll in?->";
                                getline(cin>>ws , cs);
                                if(S.FindCourse(cs)==NULL){
                                    throw string("Could't find Course");
                                }
                                
                                bool F = S.RegisterStudent(st,cs);
                                if (F == false){
                                    throw string("Failed to enroll student");
                                }
                                cout << "Enrolled " << st << " in the course " << cs << endl;
                                
                            }
                            catch(string message){
                                cout << "Error-> " << message << endl << endl;
                            }
                        }
                        else if (fun == "7"){
                            try{
                                string Pr;
                                string cs;

                                //if the professor wasn't found then we throw an exception
                                cout << "Which Professor do you want to assign in a course?-> ";
                                getline(cin>>ws , Pr);
                                if(S.FindStud(Pr)==NULL){
                                    throw string("Could't find Professor");
                                }

                                //if the course wasn't found then we throw an exception
                                cout << "Which Course do you want " << Pr <<" to be assigned?->";
                                getline(cin>>ws , cs);
                                if(S.FindStud(cs)==NULL){
                                    throw string("Could't find Course");
                                }

                                bool F = S.AssignProf(Pr,cs);
                                if(F == false){
                                    throw string("Unable to assign Professor") ;
                                }
                                cout << "Assigned " << Pr << "to " << cs << endl;
                            }
                            catch(string message){
                                cout << "Error-> " << message << endl << endl;
                            } 
                        }
                        else if (fun == "8"){
                            try{
                                int sem;
                                cout << "Which student's detailed score do you want to print?-> ";
                                getline(cin>>ws , fun);

                                //if the Student doesn't exist throw exception
                                Student* Stud = S.FindStud(fun);
                                if (Stud == NULL){
                                    throw  string("Failed to find student");
                                }

                                cout << "1) Print a semester's detailed score" << endl;
                                cout << "2) Print a Year's detailed score" << endl;
                                cout << "3) Print detailed score of all semesters" << endl;
                                cout << "Enter which function you want to perform-> ";
                                cin >> fun;
                                if (fun == "1"){
                                    cout << "Enter the semester you want to print ->";
                                    cin >> sem;
                                    Stud->PrintSemester(sem);
                                }
                                else if(fun == "2"){
                                    cout << "Enter the year you want to print ->";
                                    cin >> sem;
                                    Stud->PrintYear(sem);
                                }
                                else if (fun == "3"){
                                    Stud->PrintYear(0);
                                }
                                else{
                                    throw string("Wrong input");
                                }
                            }
                            catch(string message){
                                cout << "Error-> " << message << endl << endl;
                            }
                        }
                        else if (fun == "9"){
                            vector<Student*> Students = S.Degree();
                            cout << "Do you want to remove students that can get a degree?(True/False)-> ";
                            cin >> fun;
                            if(fun == "True" || fun == "true"){
                                vector<Student*> :: iterator it = Students.begin();
                                while(it != Students.end()){
                                    S.DeleteStudent((*it)->GetName());
                                    it++;
                                }
                                cout << "Deleted all students that got a degree from the system!" << endl;
                            }
                        }
                        else if (fun == "10"){
                            try{
                                cout << "From which course do you want to save the passed students? ->";
                                getline(cin>>ws , fun);

                                //if the course doesn't exist throw exception
                                Course* C = S.FindCourse(fun);
                                if(C == NULL){
                                    throw string("Couldn't find course");
                                }

                                //write contents of the map in a file
                                std::unordered_map<string, float> G =
                                    C->GetMap();
                                ofstream fout;
                                fout.open("data.txt");
                                fout<< " Students that passed "<< fun <<endl;
                                std::unordered_map<string, float>::iterator it =
                                    G.begin();
                                while(it != G.end()){
                                    fout << "Name:   " << it->first << "   Grade:" << it->second << endl;
                                    it++;
                                }
                                fout.close();
                                cout << "Wrote students that passed the course in a file" << endl;
                            }
                            catch(string message){
                                cout << "Error-> " << message << endl << endl;
                            }
                        }
                        else if (fun == "11"){
                            Flag2 = false;
                            S.StartSemester();
                        }
                        else if (fun == "12"){
                            cout << "Exiting system..." << endl;
                            flag = false;
                            Flag2 = false;
                            S.printfiles();
                        }
                        else{
                            throw string("Wrong input");
                        }
                    }
                    catch(string message){
                        cout << "Error-> " << message << endl << endl;
                    }
                }
            }
            else if (fun == "8"){
                flag= 0;
                cout << "Exiting system..." << endl;
                S.printfiles();
            }
            else{   
                throw string(fun);
            }
        }
        catch(string error){
            cout << "Wrong input-> " << error <<endl <<endl;

        }
    }
}