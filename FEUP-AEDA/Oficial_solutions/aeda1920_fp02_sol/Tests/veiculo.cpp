#include "veiculo.h"
#include <iostream>

using namespace std;

Veiculo::Veiculo(string mc, int m, int a)
{ marca=mc; mes=m; ano=a; }

string Veiculo::getMarca() const
{ return marca; }

int Veiculo::info(ostream &o) const
{
    o << "Marca: " << marca << endl;
    o << "Data: " << mes << "/" << ano << endl;
    return 3;
}

int Veiculo::info() const
{ return Veiculo::info(cout); }

bool Veiculo::operator <(const Veiculo & v) const
{
    if (ano<v.ano) return true;
    if (ano==v.ano && mes<v.mes) return true;
    return false;
}

int Veiculo::getAno() const
{ return ano; }


Motorizado::Motorizado(string mc, int m, int a,string c,int cil):Veiculo(mc,m,a)
{ combustivel=c; cilindrada=cil; }

string Motorizado::getCombustivel() const
{ return combustivel; }


int Motorizado::info(ostream &o) const
{
   int infoV = Veiculo::info();
   o << "Combustivel: " << combustivel << endl;
   o << "Cilindrada: " << cilindrada << endl;
   return infoV+2;
}

int Motorizado::info() const
{ return Motorizado::info(cout); }

float Motorizado::calcImposto() const
{
   if (combustivel=="gasolina") {
      if (cilindrada<=1000)
		if (ano<=1995) return 8.10; else return 14.56;
	else if (cilindrada<=1300)
		if (ano<=1995) return 14.56; else return 29.06;
	else if (cilindrada<=1750)
		if (ano<=1995) return 22.65; else return 45.15;
	else if (cilindrada<=2600)
		if (ano<=1995) return 54.89; else return 113.98;
	else if (cilindrada<=3500)
		if (ano<=1995) return 87.13; else return 181.17;
	else if (ano<=1995) return 148.35; else return 320.89;
   }
   else {
	if (cilindrada<=1500)
		if (ano<=1995) return 8.10; else return 14.56;
	else if (cilindrada<=2000)
		if (ano<=1995) return 14.56; else return 29.06;
	else if (cilindrada<=3000)
		if (ano<=1995) return 22.65; else return 45.15;
	else  if (ano<=1995) return 54.89; else return 113.98;
   }
}


Automovel::Automovel(string mc, int m, int a,string c, int cil): Motorizado(mc,m,a,c,cil)
{ }

int Automovel::info(ostream &o) const
{
   o << "Automovel"<< endl;
   int infoM=Motorizado::info();
   o << endl;
   return infoM;
}

int Automovel::info() const
{ return Automovel::info(cout); }


Camiao::Camiao(string mc, int m, int a,string c, int cil,int cm): Motorizado(mc,m,a,c,cil)
{
   carga_maxima=cm;
}

int Camiao::info(ostream &o) const
{
   o << "Camiao"<<endl;
   int infoM = Motorizado::info();
   o << "Carga maxima: " << carga_maxima<< endl<< endl;
   return infoM+1;
}

int Camiao::info() const
{ return Camiao::info(cout); }

Bicicleta::Bicicleta(string mc, int m, int a,string t): Veiculo(mc,m,a)
{ tipo=t; }

int Bicicleta::info(ostream &o) const
{
   o << "Bicicleta" << endl;
   int infoV=Veiculo::info();
   o << "Tipo: " << tipo<< endl<< endl;
   return infoV+1;
}

int Bicicleta::info() const
{ return Bicicleta::info(cout); }

float Bicicleta::calcImposto() const
{ return 0; }




