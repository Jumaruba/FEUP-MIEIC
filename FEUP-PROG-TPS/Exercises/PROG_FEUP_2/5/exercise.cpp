#include <iostream> 
#include <string> 
#include <vector> 
#include <fstream> 
#include <sstream> 
#include <regex> 

using namespace std; 


//CORPO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
vector<string> tVec(const string& s); 
void readClient();
void readBooks(); 

//CLASSES++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Client{
	public: 
		Client(){
			number ++; 
			this-> id = number; 
		}
		Client(string name, string books){
			number++;
			this-> id = number; 
			this->name = name; 
			this-> books = tVec(books); 

		}


		static int number; 

	private: 
		int id; 
		string name; 
		vector<string> books; 

};

int Client::number = 0; 

class Books{
	public: 
		Books(){
			nBooks++; 
			this-> id = nBooks; 
		}
		Books(string name, string available){
			nBooks++; 
			this-> name = name; 
			this-> available = stoi(available); 
		}

		static int nBooks; 

	private: 
		int id; 
		string name;
		bool available; 
};

int Books::nBooks = 0; 

//FUNCOES+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
vector<string> text; 
vector<Client> c; 
vector<Books> b;

//transform string in vector 
vector<string> tVec(const string& s){
	
	int size; 
	string aux; 
	aux = regex_replace(s, regex(","), " ");

	stringstream in(aux); 
	size = count(s.begin(), s.end(), ' ');
	vector<string> vecReturn(size);  
	for (int i = 0; i < size; i++){
		in >> vecReturn[i]; 
	}
	return vecReturn; 
}

//lê o arquivo de cliente; 
void readClient(){
	string fName; 
	string aux; 
	getline(cin, fName); 

	ifstream file; 
	file.open(fName.c_str()); 

	if (file.is_open()){
		while (getline(cin, aux)){
			text.push_back(aux); 
		}
	}
	else{
		cerr << "Not possible to open " << fName << endl; 
	}

	for (int i = 0; i < text.size(); i+=2){
		Client aux(text[i], text[i+1]);
		c.push_back(aux); 
	}

}

//reads books file
void readBooks(){
	text.clear(); 
	string fName;
	string aux; 

	getline(cin, fName); 
	ifstream file;
	file.open(fName.c_str()); 

	if(file.is_open()){
		while(getline(file, aux)){
			text.push_back(aux);
		}
	}
	else 
		cerr << "Not possible to open " << fName << endl; 

	for (int i = 0; i < text.size(); i+=2){
		Books aux(text[i], text[i+1]); 
		b.push_back(aux);
	}
}

int main(){
	readClient();
	readBooks(); 

}