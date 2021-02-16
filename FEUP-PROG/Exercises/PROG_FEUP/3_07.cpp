#include <iostream>
#include <climits>

using namespace std; 

long factorial_ite(long numero)
{
    long resultado = 1;
    for (long i = 1; i < numero + 1; i++)
    {
        resultado = i * resultado;
    }
    return resultado;
}

long factorial_rec(long n)
{
    if (n <= 1)
        return 1;
    else
    {
        return n * factorial_rec(n - 1);
    }
}

long factorial_ite_maior(long maior)
{   long contador = 1, numero = 1;
    long resultado = 1;
    while (numero < maior){
        numero = numero*contador;
        contador ++;
    }
    return contador; 
}


int main()
{
    const long m = LONG_MAX;
    cout << m << endl;
    cout << factorial_ite_maior(m) << endl;
    
}