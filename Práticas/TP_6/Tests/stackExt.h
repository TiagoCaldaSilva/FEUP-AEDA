# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
private:
    stack<T> s, min;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};


template <class T> 
bool StackExt<T>::empty() const
{
	return s.empty();
}


template <class T> 
T& StackExt<T>::top()
{
    T *novo = new T();
    *novo = s.top();
    return *novo;
}


template <class T> 
void StackExt<T>::pop()
{
    if(!min.empty() && s.top() == min.top())
        min.pop();
    s.pop();
}


template <class T> 
void StackExt<T>::push(const T & val)
{
    if(min.empty())
        min.push(val);
    else if(val <= min.top())
        min.push(val);
    s.push(val);
}


template <class T> 
T& StackExt<T>::findMin()
{
    T *minim = new T();
    *minim = min.top();
    return *minim;
}

