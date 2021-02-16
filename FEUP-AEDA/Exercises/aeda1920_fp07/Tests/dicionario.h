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

// a alterar
class PalavraNaoExiste
{
    BST<PalavraSignificado> d;
    string palavra;
public:
	string getPalavraAntes() const {
	    BSTItrIn<PalavraSignificado> it(d);
	    string palavra_antes = it.retrieve().getPalavra();
        string pal = palavra_antes;
	    it.advance();
	    while(!it.isAtEnd()){
	        pal = it.retrieve().getPalavra();
	        if (pal > palavra) return palavra_antes;
	        palavra_antes = pal;
	        it.advance();
	    }
	    return pal;
	}
	string getSignificadoAntes() const {
        BSTItrIn<PalavraSignificado> it(d);
        string sig_antes = it.retrieve().getSignificado();
        it.advance();
        string pal;
        while(!it.isAtEnd()){
            pal = it.retrieve().getPalavra();
            if (pal > palavra) return sig_antes;
            sig_antes = it.retrieve().getSignificado();
            it.advance();
        }
        return pal;
	}
	string getPalavraApos() const {
	    BSTItrIn<PalavraSignificado> it(d);
	    string pal = it.retrieve().getPalavra();
	    while(!it.isAtEnd()){
            pal = it.retrieve().getPalavra();
            if (pal > palavra) return pal;
	        it.advance();
 	    }
	    return pal;
	}
	string getSignificadoApos() const {
        BSTItrIn<PalavraSignificado> it(d);
        string sig, pal;
        while(!it.isAtEnd()){
            sig= it.retrieve().getSignificado();
            pal = it.retrieve().getPalavra();
            if (pal > palavra) return sig;
            it.advance();
        }
        return pal;
    }

    PalavraNaoExiste(BST<PalavraSignificado> D, string Palavra): palavra(Palavra), d(D){}
};


#endif
