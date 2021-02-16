#include <bits/stdc++.h>
using namespace std; 


template <class T>
class Vector
{
public:
	Vector();
	Vector(unsigned int size);
	Vector(unsigned int size, const T & initial);
	Vector(const Vector<T> & v);
	~Vector();
	size_t size() const;
	bool empty() const;
	T & front();
	T & back();
	T & at(size_t index);
	void push_back(const T & value);
	void pop_back();
	void clear();
	size_t capacity(); 
	void reserve(const int & lentgh);
private:
	size_t bufferCapacity;
	T * buffer;
	size_t bufferSize;
};

template<class T> 
Vector<T>::Vector(){
	bufferSize = 0; 
}

template<class T> 
Vector<T>::Vector(unsigned int size){
	bufferSize = size; 
	buffer = (T *)malloc(size*sizeof(T)); 
} 

template<class T> 
Vector<T>::Vector(unsigned int size, const T & initial){
	buffer = (T *)malloc(sizeof(T));
	buffer[0] = initial;  
	/*for (int i = 0; i < bufferSize; i ++){
		buffer[i] = initial[i]; 
	}*/
}

template<class T> 
Vector<T>::Vector(const Vector<T> & v){
	bufferSize =  v.size(); 
	buffer = (T *)malloc(bufferSize*sizeof(T)); 

	for (int i = 0; i < bufferSize; i++){
		buffer[i] = v[i]; 
	}
}
template<class T>
Vector<T>::~Vector(){
	free(buffer); 
}

template<class T> 
size_t Vector<T>::size() const{
	return bufferSize; 
}

template<class T> 
bool Vector<T>::empty() const{
	return bufferSize == 0; 
}

template<class T> 
T & Vector<T>::front(){
	return buffer[0]; 
}

template<class T> 
T & Vector<T>::back(){
	return buffer[bufferSize-1]; 
}

template<class T> 
T & Vector<T>::at(size_t index){
	return buffer[index]; 
}

template<class T> 
void Vector<T>::push_back(const T & value){
	buffer =  (T*)realloc(buffer, (bufferSize+1)*sizeof(T));
	bufferSize ++; 
	buffer[bufferSize-1] = value;  
}

template<class T> 
void Vector<T>::pop_back(){
	bufferSize--; 
	buffer = (T * )realloc(buffer ,bufferSize*sizeof(T)); 
	
}

template<class T> 
void Vector<T>::clear(){
	bufferSize = 0; 
	free(buffer); 
}

template<class T> 
size_t Vector<T>::capacity(){
	return bufferCapacity; 
}

template<class T> 
void Vector<T>::reserve(const int & lentgh){
	buffer = (T *)realloc(buffer, lentgh*sizeof(T)); 
	bufferCapacity = lentgh; 
}


int main(){
	Vector<int> v(5, 1);

	cout << v.at(0) << endl; 
	for (int i = 0; i < 5; i++)
		v.push_back(i); 

	for (int i = 0; i < 5; i++)
		cout << v.at(i) << endl; 


}

