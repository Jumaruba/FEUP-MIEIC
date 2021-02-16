#include <iostream>
#include <string>

using namespace std;

void decompose(string compound)
{   string m;
    bool anterior = false;
    for (int i = 0; i < compound.size(); i++)
    {
        if (compound[i] >= 65 && compound[i] <= 90){ // se achar um maiusculo
            if (anterior)
                cout << m << " ";
            m = "";
            anterior = true;
            m.push_back(compound[i]);
        }
        else if (anterior && compound[i] >= 97 && compound[i] <= 122){ // se o proximo for minusculo
            anterior = false;
            m.push_back(compound[i]);
            cout << m << " ";
            m = "";
        }
        else{
            anterior = false;
            cout << m << " ";
            m = "";
        }
    }
    cout << m << endl;
}

int main()
{
    string s;
    cout << "string" << endl; 

    cin >> s; 
    decompose(s);

}