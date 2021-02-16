#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;


//a fazer
bool InfoCartao::operator == (const InfoCartao &ic1) const
{
     if (nome==ic1.nome) return true;
     return false;
}

// a fazer
bool InfoCartao::operator < (const InfoCartao &ic1) const
{
     if (frequencia > ic1.frequencia)
    	 return true;
     else if (frequencia < ic1.frequencia)
    	 return false;
     else
    	 return (nome<ic1.nome);
}

// a fazer
bool compNome(const InfoCartao &c1, const InfoCartao &c2)
{
	return c1.nome < c2.nome;
}


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


// a fazer
int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    InfoCartao inf1;
    inf1.nome=nome;
	int p = sequentialSearch(clientes, inf1);
	return p;
}

int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    int pos = posicaoCliente(nome);
    if (pos == -1) throw ClienteNaoExistente(nome);
    return clientes[pos].frequencia;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;  // a fazer
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes[pos].frequencia++;   // a fazer
	vagas--;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

		
 // a fazer
ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
	for (unsigned int i= 0; i < pe.clientes.size(); i++) {
        os << "Nome: " << pe.clientes[i].nome;
        if (pe.clientes[i].presente == true) os << " (esta presente)" ;
        os << " ; frequencia = " << pe.clientes[i].frequencia << endl;
    }
	return os;
	
}

InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    if (p >= clientes.size()) throw PosicaoNaoExistente(p);
    return clientes[p];
}


// a fazer
void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
     insertionSort(clientes);
}


// a fazer
void ParqueEstacionamento::ordenaClientesPorNome()
{
     sort(clientes.begin(),clientes.end(),compNome);
}


// a fazer
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    ordenaClientesPorFrequencia();
    vector<string> nomes;
    for (unsigned int i=0; i<clientes.size(); i++)
    {
        if (clientes[i].frequencia < n1)
        	break;
        if (clientes[i].frequencia <= n2)
        	nomes.push_back(clientes[i].nome);
    }
    return nomes;
}
