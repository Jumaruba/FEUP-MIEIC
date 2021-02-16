
#include <iostream>
#include <cstring> //IF WE WANNA INCLUDE SOMETHING FROM C, WE NEED TO PUT A C BEFORE THE BIBLIO
#include <string>

using namespace std;

bool isHydroxide_c (char compound[]){
    int tamanho = strlen(compound);  //HOW TO DETERMINE THE LENGTH OF AN ARRAY!
    if (compound[tamanho -2] == 'O' && compound[tamanho -1] == 'H')
        return true;
    return false;
}

bool isHydroxide_s(string compound){
    int tamanho = compound.size();
    if (compound[tamanho -2] == 'O' && compound[tamanho -1] == 'H')
        return true;
    return false;
}

int main(){
    string word = "KOmopo";
    char wordm[3] = {'K','O','H'}; 

    cout << isHydroxide_s(word) << " " << isHydroxide_c(wordm) << endl;

    return 0;
}