#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;
template <class N> class NoRepetido;
template <class N> class ArestaRepetida;
template <class N> class NoInexistente;
template <class N> class ArestaInexistente;


template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo();
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template<class N, class A>
Grafo<N,A>::Grafo(){}

template<class N, class A>
Grafo<N,A>::~Grafo(){}

template<class N, class A>
int Grafo<N,A>::numArestas(void) const{
    int arestas = 0;
    for (auto it = nos.begin(); it < nos.end(); it++){
        arestas += (*it)->arestas.size();
    }
    return arestas;
}

template<class N, class A>
int Grafo<N,A>::numNos(void) const{
    return nos.size();
}

template<class N, class A>
Grafo<N,A>& Grafo<N,A>::inserirNo(const N &dados) {
    for (auto n: nos){
        if (dados ==  n->info) {
            throw NoRepetido<N>(dados);
        }
    }
    //é preciso alocar!!
    No<N,A> *temp = new No<N,A>(dados);
    nos.push_back(temp);
    return *this;
}

template<class N, class A>
Grafo<N,A>& Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val) {
    size_t posBegin = -1;
    for (int i = 0; i < nos.size(); i++){
        if (nos[i]->info == inicio) {
            posBegin = i;
            break;
        }
    }
    if (posBegin == -1) throw NoInexistente<N>(inicio);

    //checa a existencia do final
    size_t posEnd = -1;
    for (int i = 0; i < nos.size(); i++){
        if (nos[i]->info == fim) {
            posEnd = i;
            break;
        }
    }

    if (posEnd == -1) throw NoInexistente<N>(fim);


    for (auto a: nos[posBegin]->arestas){
        if (a.destino->info == fim)
            throw ArestaRepetida<N>(inicio, fim);
    }

    Aresta<N,A> *temp = new Aresta<N,A>(nos[posEnd], val);
    nos[posBegin]->arestas.push_back(*temp);
    return *this;
}

template <class N, class A>
Grafo<N,A>& Grafo<N,A>::eliminarAresta(const N &inicio, const N &fim) {
    int posBegin = -1;
    for (int i = 0; i < nos.size(); i++){
        if (nos[i]->info == inicio){
            posBegin = i;
            break;
        }
    }

    if (posBegin == -1) throw NoInexistente<N>(inicio);

    for (auto it = nos[posBegin]->arestas.begin(); it < nos[posBegin]->arestas.end(); it++){
        if (it->destino->info == fim){
            nos[posBegin]->arestas.erase(it, it+1);
            return *this;
        }
    }

    throw ArestaInexistente<N>(inicio,fim);
}
template<class N, class A>
void Grafo<N,A>::imprimir(std::ostream &os) const {
    for (auto it = nos.begin(); it< nos.end(); it++){
        os << "( " << (*it)->info;
        for (auto it2 = (*it)->arestas.begin(); it2 < (*it)->arestas.end(); it2++){
            os << "[ " << it2->destino->info << " " << it2->valor << "] ";
        }
        os << ") ";
    }
}

template<class N, class A>
A& Grafo<N,A>::valorAresta(const N &inicio, const N &fim) {
    int posBegin = -1;
    for (int i = 0; i < nos.size(); i++){
        if (nos[i]->info == inicio){
            posBegin = i;
            break;
        }
    }
    if (posBegin == -1) throw NoInexistente<N>(inicio);

    //podia ter feito com iterators
   for (int i = 0; i < nos[posBegin]->arestas.size(); i++){
       if (nos[posBegin]->arestas[i].destino->info == fim)
           return nos[posBegin]->arestas[i].valor;
   }
   throw ArestaInexistente<N>(inicio, fim);
}

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g){
    g.imprimir(out);
    return out;
}


// excecao NoRepetido

template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }


//excecao arestaRepetida

template<class N>
class ArestaRepetida{
public:
    N info1;
    N info2;
    ArestaRepetida(N in1, N in2): info1(in1), info2(in2){}
};

template <class N>
std:: ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar){
    out << "Aresta repetida: " << ar.info1 << " , " << ar.info2;
    return out;
}

//excecao ArestaInexistente
template<class N>
class ArestaInexistente{
public:
    N info1;
    N info2;
    ArestaInexistente(N in1, N in2): info1(in1), info2(in2){};
};

template<class N>
std::ostream & operator<<(std::ostream & out, const ArestaInexistente<N> & ai){
    out << "Aresta inexistente: " << ai.info1 << " , " << ai.info2;
    return out;
}