#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class PalavraSignificado {
      string palavra;
      string significado;
public:
       PalavraSignificado(string p, string s): palavra(p), significado(s) {}
       string getPalavra() const { return palavra; }
       string getSignificado() const { return significado; }
       void setSignificado(string sig) { significado=sig; }
       bool operator < (const PalavraSignificado &ps1) const;
       bool operator == (const PalavraSignificado &ps1) const;

       void setPalavra(string p) {palavra=p; }
};

class Dicionario
{
      BST<PalavraSignificado> palavras;
public:
      Dicionario(): palavras(PalavraSignificado("","")){};
      BST<PalavraSignificado> getPalavras() const;
      void lerDicionario(ifstream &fich);
      string consulta(string palavra) const;
      bool corrige(string palavra, string significado);
      void imprime() const;
};

class PalavraNaoExiste
{
	string palavraAntes,significadoAntes,palavraApos,significadoApos;
public:
	PalavraNaoExiste(string pAnt, string sAnt, string pAp, string sAp):
		palavraAntes(pAnt), significadoAntes(sAnt), palavraApos(pAp), significadoApos(sAp)
	{}
	string getPalavraAntes() const { return palavraAntes; }
	string getSignificadoAntes() const { return significadoAntes; }
	string getPalavraApos() const { return palavraApos; }
	string getSignificadoApos() const { return significadoApos; }
};


#endif
