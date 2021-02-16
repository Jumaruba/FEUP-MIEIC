#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
		lotacao(lot), numMaximoClientes(nMaxCli)
{ vagas=lot; }


int ParqueEstacionamento::posicaoCliente(const string & nome) const
{
	for (unsigned int i=0; i<clientes.size(); i++)
		if (clientes[i].nome == nome) return i;
	return -1;
}


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if (clientes.size() == numMaximoClientes) return false;
	if (posicaoCliente(nome) != -1) return false;
	InfoCartao info;
	info.nome=nome;
	info.presente=false;
	clientes.push_back(info);
	return true;
}
 

bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( (*it).nome == nome ) {
			if ( (*it).presente == false ) {
				clientes.erase(it);
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

unsigned int ParqueEstacionamento::getNumMaximoClientes() const
{
	return numMaximoClientes;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const
{
	return clientes.size();
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if (vagas == 0) return false;
	int pos = posicaoCliente(nome);
	if (pos == -1) return false;
	if (clientes[pos].presente == true) return false;
	clientes[pos].presente = true;
	vagas--;
	return true;
}


bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if (pos == -1) return false;
	if (clientes[pos].presente == false) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}
		


