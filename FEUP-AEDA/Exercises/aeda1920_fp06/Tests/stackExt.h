# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack<T> s;
    stack<T> min;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const
{
	return s.empty();
}

//a alterar
template <class T> 
T& StackExt<T>::top()
{
    T *novo = new T();
    *novo = s.top();
    return *novo;
}

//a alterar
template <class T> 
void StackExt<T>::pop()
{
    if (s.top() == min.top())
        min.pop();
    s.pop();

}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val)
{
    if (s.empty()) min.push(val);
    else if (s.top()> val)
        min.push(val);
    s.push(val);

}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    T *novo = new T();
    *novo = min.top();
    return *novo;
}

