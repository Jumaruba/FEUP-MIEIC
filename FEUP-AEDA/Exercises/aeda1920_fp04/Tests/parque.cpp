#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
#include  <iomanip>

using namespace std;



ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }


// a imnplementar
int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    vector<string> name;
    for (auto it = clientes.begin(); it<clientes.end(); it++) name.push_back(it->nome);
    return sequentialSearch(name,nome);
}

//a implementar
int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    int pos = posicaoCliente(nome);
    if (pos == -1) throw ClienteNaoExistente(nome);
    return clientes[pos].frequencia;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ?
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

// a alterar/atualizar ?
bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente ) return false;
	clientes[pos].presente = true;
	vagas--;
	clientes[pos].frequencia++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

		
// a implementar
void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    insertionSort(clientes);
}


// a implementar
void ParqueEstacionamento::ordenaClientesPorNome()
{
    /*sort(clientes.begin(), clientes.end(), [](const InfoCartao& i1, const InfoCartao& i2){
        return (i1.nome < i2.nome);
    });*/
    //bubble sort
    for (int i = clientes.size()-1; i > 0; i--){
        for (int j = 1; j <= i; j++){
            if (clientes[j].nome < clientes[j-1].nome)
                swap(clientes[j], clientes[j-1]);
        }
    }
}


// a implementar
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    ordenaClientesPorFrequencia();
    vector<string> nomes;
    for (auto i = clientes.begin(); i < clientes.end(); i++){
        if (i->frequencia>=n1 && i->frequencia<=n2)
            nomes.push_back(i->nome);
    }
    return nomes;
}


// a implementar
ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
    os << left << setw(15) << "NOME" << setw(10) << "PRESENTE"
    << "FREQUENCIA" << endl;
    for (auto it = pe.clientes.begin(); it < pe.clientes.end(); it ++){
        os << left << setw(15) << it->nome << setw(11) << it->presente
        << it->frequencia << endl;
    }
    return os;
}


// a implmentar
InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    InfoCartao info;
    if (p >= clientes.size()) throw PosicaoNaoExistente(p);
    info = clientes[p];
    return info;
}

ClienteNaoExistente::ClienteNaoExistente(string name): nome(name) {}
string ClienteNaoExistente::getNome() {
    return nome;
}

bool InfoCartao::operator<(const InfoCartao& i) {
    if (frequencia > i.frequencia) return true;
    else if (frequencia == i.frequencia)
        return (nome < i.nome);
    return false;
}
PosicaoNaoExistente::PosicaoNaoExistente(int Valor): valor(Valor) {}

int PosicaoNaoExistente::getValor() {
    return valor;
}