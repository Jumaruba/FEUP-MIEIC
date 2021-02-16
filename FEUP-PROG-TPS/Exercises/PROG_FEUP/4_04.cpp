#include <iostream>
#include <vector>

using namespace std;

string maiuscula(string name)
{
    for (int i = 0; i < name.size(); i++)
    {
        if (name[i] >= 97 && name[i] <= 122)
        {
            name[i] = name[i] - 32;
        }
    }
    cout << name << endl;
    return name;
}

string normalizeName(string name)
{
    string palavra, sub_palavra;
    name = maiuscula(name); //colocando tudo em letra maiuscula;
    for (int i = 0; i < name.size(); i++){
        if (name[i] != ' '){
            sub_palavra.push_back(name[i]);
        }
        else{
            if (sub_palavra != "DE" && sub_palavra != "DO" && sub_palavra != "DA" && sub_palavra != "DAS" && sub_palavra != "DOS" && sub_palavra !="E" && sub_palavra != " "){
                palavra.append(sub_palavra); //append to add string;
                if (sub_palavra != "")
                    palavra.push_back(' ');
                sub_palavra = "";
            }
            else{
                sub_palavra = "";
            }
        }
    }
    palavra.append(sub_palavra);
    return palavra;
}
int main()
{
    string name;
    cout << "name ? \n";
    getline(cin, name); //dont forget!
    cout << normalizeName(name) << endl;
}