/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
    if ( frase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = frase.find(' ');
    while (pos != string::npos) {
        frase = frase.substr(pos+1);
        pos = frase.find(' ');
        n++;
    }
    return n;
}

// a implementar
Jogo::Jogo()
{
    criancas.clear();
}

// a implementar
Jogo::Jogo(list<Crianca>& lc2)
{
    criancas = lc2;
}

// a implementar
void Jogo::insereCrianca(const Crianca &c1)
{
    criancas.push_back(c1);
}

// a implementar
list<Crianca> Jogo::getCriancasJogo() const
{
    return criancas;
}

// a implementar
string Jogo::escreve() const
{
    string g;
    for (auto const &i: criancas){
        g += i.escreve() + "\n";
    }
    return g;
}

// deu certo, vida de merda
Crianca& Jogo::perdeJogo(string frase)
{
    Crianca *c1 = new Crianca();
    list<Crianca> m = criancas;
    int palavras = numPalavras(frase);

    int perdedor = palavras%criancas.size();
    int contador = 1;
    auto it = m.begin();

    while (m.size()!= 1) {
        for (int i = 1; i < palavras; i++) {
            it++;
            if (it == m.end()) it = m.begin();
        }
        cout << it->getNome() << endl;
        it = m.erase(it);
        if (it == m.end()) it = m.begin();
    }
    return *m.begin();


}

// a implementar
list<Crianca>& Jogo::inverte()
{
    criancas.reverse();
    return criancas;
}

// a implementar
list<Crianca> Jogo::divide(unsigned id)
{
    list<Crianca> c;
    for (auto it = criancas.begin(); it!=criancas.end(); it++){
        if ((*it).getIdade() > id ){
            c.push_back(*it);
        }

    }
    return c;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
    criancas = l1;
}

// a implementar
bool Jogo::operator==(Jogo& j2)
{
    list<Crianca> prov1 = criancas;
    list<Crianca> prov2 = j2.getCriancasJogo();

    if (j2.getCriancasJogo().size()!= criancas.size())
        return false;
    for (int i = 0 ; i< prov1.size(); i++){
        if (!(prov1.front() == prov2.front()))
            return false;
        prov1.pop_front();
        prov2.pop_front();
    }
    return true;
}

// finalmente deu certo, vida de merda
list<Crianca> Jogo::baralha() const
{
    list<Crianca> res;
    int random;
    int counter = 0;
    list<Crianca> m = criancas;

    while (res.size() < criancas.size()) {
        counter = 0;
        random = rand() % m.size();
        for (auto it = m.begin(); it != m.end(); it++) {
            if (counter == random) {
                random = rand() % m.size();
                res.push_back((*it));
                it = m.erase(it);
                counter = 0;
            }
            counter++;
            //cout << counter << endl;
        }
    }
    return res;
}