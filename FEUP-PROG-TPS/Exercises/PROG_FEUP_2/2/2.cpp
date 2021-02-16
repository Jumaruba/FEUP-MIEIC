#include <iostream>
#include <string>
#include <cmath>
#include <vector> 
#include <iomanip>
#include <fstream>

using namespace std; 


class Student {
    public:
        static int weightShortExam, weightProject, weightExam; // weights in percentage (ex:20,30,50)
        Student();
        Student(const string &code, const string &name){
            this-> code = code ; 
            this-> name = name; 
        }
        void setGrades(double shortExam, double project, double exam){
            this-> weightShortExam = 20; 
            this-> weightProject = 30; 
            this-> weightExam = 50; 

            this-> shortExam= shortExam; 
            this-> project = project; 
            this-> exam = exam;

        }
        string getCode() const{
            return code; 
        }
        string getName() const{
            return name;
        }
        int getFinalGrade() const{ //get the final grade
            return round((shortExam*weightShortExam + project*weightProject + exam*weightExam) / (weightExam+weightProject+weightShortExam)); 
        }
        double getExam() const{ // get the exam grade
            return this->exam; 
        }
        double getShortExam() const{ //get the short exam grade 
            return this ->shortExam; 
        }
        double getProject()const { //get the project grade 
            return this-> project;
        }
        bool isApproved() const // is the student approved or not ?
        {
            if (this->getFinalGrade() >= 10 )
                return true;
            return false;  
        }
 

    private:
        string code; // student code
        string name; // student complete name
        double shortExam, project, exam; // grades obtained by the student in the different components
        int finalGrade;
}; 


int Student::weightShortExam = 20; 
int Student::weightProject = 30; 
int Student::weightExam = 50; 


Student readStundentData(){  //Set information about an student
    string name; 
    string code; 
    double shortExamGrade, projectGrade, examGrade; 
 


    cout << "Student code? ";   //getting the code 
    cin >> code; 
    cin.ignore(); 
    cout << "Student name? ";   //getting the student name
    getline(cin, name); 

    Student aux(code, name);    //declaring the aux object of Student with the information given before
    Student* ptrAux = &aux;     

    //Input 
    cout << "Short exam grade? "; 
    cin >> shortExamGrade; 
    cout << "Project grade? "; 
    cin >> projectGrade; 
    cout << "Exam grade? "; 
    cin >> examGrade; 

    ptrAux-> setGrades(shortExamGrade, projectGrade, examGrade);   //setting grades 
    return aux;

    
}

string showAboveAvarageStudents(stringstream& out,vector<Student>& m){  //it shows a list of approved students
     
    out << left <<setw(30) <<"ID" 
        << setw(30) << "Name" 
        << setw(25) << "Project" 
        << setw(25) << "ShortExam"
        << setw(25) << "Exam"
        <<"Final_grade" << endl; 

    for (int i = 0; i < m.size(); i++){
        if (m[i].isApproved())
            out << left <<setw(30) << m[i].getCode() 
                << setw(30) << m[i].getName()
                << setw(25) << m[i].getProject()
                << setw(25) << m[i].getShortExam()
                << setw(25) << m[i].getExam()
                <<m[i].getFinalGrade() << endl; 
         
    }
    return out.str(); 
}

void inputVector(vector<Student>& m){  // input the information about n students manually
    stringstream out; 
    int numStudents; 
    cout << "Number of students ? " << endl; 
    cin >> numStudents; 

    for (int i = 0; i< numStudents; i++){
        cout << "Student number "<< i << endl; 
        m.push_back(readStundentData()); 
    }

    showAboveAvarageStudents(out, m); 
}

Student push_student(string text){  //extract information from a text and return a Student 
    size_t posb = 0;
    size_t pose;
    double shortExamGrade, projectGrade, examGrade;
 
    
    pose = text.find(';'); 
    string code = text.substr(0,pose); 
    
    text[pose] = '-'; 
    posb = pose; 
    pose = text.find(';');
    
    string name = text.substr(posb+1, pose-posb-1); 
 
    Student aux(code, name); 
    Student* ptr = &aux; 

    text[pose] = '-'; 
    posb = pose; 
    pose = text.find(';');

    shortExamGrade = stof(text.substr(posb+1, pose-posb-1));

    text[pose] = '-'; 
    posb = pose; 
    pose = text.find(';');

    projectGrade = stof(text.substr(posb+1, pose-posb-1));
    examGrade = stof(text.substr(pose+1));

    ptr-> setGrades(shortExamGrade, projectGrade, examGrade); 

    return aux; 
     

}
void readFile(string name, vector<Student>& m){  //read the file and push_back the information into a Student vector

    string text; 
    ifstream file; 
    file.open(name); 

    if (file.is_open()){
        while(getline(file, text)){  //read the file
            m.push_back(push_student(text));  //push_back the information into the vector 
        }
            
    }
}

void writeFile(string name, string text){  //write the file with the information 
    ofstream file; 
    file.open(name); 
    file << text; 
}

int main(){
    stringstream out; 
    vector<Student> m; 
    readFile("text.txt", m); 
    writeFile("Result.txt", showAboveAvarageStudents(out, m)); 

    return 0; 

}