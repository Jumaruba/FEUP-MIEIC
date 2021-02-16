#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

bool bissexto(int ano) //Descobre se o ano eh bissexto
{
    if (ano % 400 == 0)
        return true;
    else if (ano % 4 == 0 && ano % 100 != 0)
        return true;
    return false;
}

int calcula_c(int mes, int ano) {  //calcula o codigo do mes
    bool b = bissexto(ano);
    vector<int> codigos_b = {0, 6, 2, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};  //se for bissexto;
    vector<int> codigos_nb = {0, 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5}; //se não for bissexto;
    
    if (b)
        return codigos_b[mes];
    return codigos_nb[mes];
}

int dias_no_mes(int ano, int mes)  //retorna a quantidade de string que tem nesse mes;
{
    vector<int> meses = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mes == 2 && bissexto(ano))
        return 29;
    return meses[mes];
}

int dia_da_semana(int ano, int mes, int dia)  //retorna o dia da semana;
{
    int c = calcula_c(mes, ano);
    return ((int) floor(5 * (ano % 100) / 4) + c + dia - 2 * (ano / 100) % 4 + 13) % 7;
    
}



void print_mes(int ano, int mes){
    int contador = 1; //contador representa o dia dos mes que será printado
    vector <string> mes_nome = {" ", "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    int primeiro_dia = dia_da_semana(ano, mes, 1); //dia da semana do primeiro dia
    int dias_mes = dias_no_mes(ano, mes);
    cout << endl;
    cout << mes_nome[mes] << "/" << ano << endl;  //printando o nome do mes e o ano
    cout << "Dom" << '\t' << "Seg" << '\t' << "Ter" << '\t' << "Qua" << '\t' << "Qui" << '\t' << "Sex" << '\t' << "Sab" << endl;
    for (int i = 0; i< primeiro_dia ; i++){
        cout << '\t';
    }
    while (contador <= dias_mes){
        cout << contador << '\t';
        contador++;
        primeiro_dia ++;
        if (primeiro_dia % 7 == 0){  //toda vez que o dia da semana for domingo, pulamos a linha
            primeiro_dia = 0;
            cout << endl;
        }
    }
    cout << endl;
}


int main()
{
    int ano;

    cout << "Digite o ano: ";
    cin >> ano;

    for (int i = 1; i< 13; i++)
        print_mes(ano, i);
    return 0;
}