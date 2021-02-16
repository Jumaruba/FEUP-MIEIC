/*
Write a template function that determines the minimum and maximum values of a vector of numbers that it receives
as parameter.
*/

#include <bits/stdc++.h>
using namespace std; 

template <typename T> 
string maxValue (vector<T> v){
	T min = v[0]; 
	T max = v[0]; 
	string resul; 
	for (int i = 1; i< v.size(); i++){
		if (v[i] > max)
			max = v[i]; 
		if (v[i] < min)
			min = v[i]; 
	}
	cout<<fixed<< setprecision(2);

	resul.append(to_string(max)) ;
	resul.push_back(' ');
	resul.append(to_string(min)); 
	return resul; 
}

void bosta(int& x){
	cout << "meu cu " << x << endl;  
}

int main(){
	vector<float> v = {1,3.6,8.3,1,2,9.8,5.0,4.1,10,6.2};
	cout << maxValue(v); 
	int bla = 2; 
	bosta(bla); 
	cout << &bla << endl; 
	return 0;

}