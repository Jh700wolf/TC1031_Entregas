#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
// Autor: Jose Pablo Gonzalez
using namespace std;

template <class T>
class Heap{
private:
    T *datos;
    int tam;
    int cont;

public:
    Heap();
    Heap(int);
    string toString() const;
    int size();
    void push(int);
    void pop();
    bool empty();
    bool lleno();
    int parent(int);
    int right(int);
    int left(int);
    int top();
    void heapify(int);
    void swap(int, int);
};

template <class T>
Heap<T>::Heap()
{
    tam=0;
    cont=0;

}

template <class T>
Heap<T>::Heap(int tam_)
{
    tam=tam_;
    datos=new T[tam_];
    cont=0;


}

template <class T>
void Heap<T>::push(int num){
    unsigned int a;
    if (lleno()){
        return;
    }
    a=cont;
    cont++;
    while (a>0 && num<datos[parent(a)]){
        datos[a]=datos[parent(a)];
        a=parent(a);
    }

    datos[a]=num;
}

template <class T>
int Heap<T>::size(){
    return (cont);
}

template <class T>
int Heap<T>::top(){
    return datos[0];
}

template <class T>
void Heap<T>::pop(){
    if (empty()){
        return;
    }
    datos[0]=datos[cont-1];
    cont--;
    heapify(0);
    return;
}

template <class T>
bool Heap<T>::lleno(){
    return(tam==cont);

}

template <class T>
int Heap<T>::parent(int pos){
    return((pos-1)/2);

}

template <class T>
int Heap<T>::left(int pos){
    return((pos*2)+1);

}

template <class T>
int Heap<T>::right(int pos){
    return((pos*2)+2);

}

template <class T>
void Heap<T>::heapify(int p){
    int r,l,min;
    r=right(p);
    l=left(p);
    min=p;
    if (cont>=l && datos[l]<datos[min]){
        min=l;
    }
    if (cont>=r && datos[r]<datos[min]){
        min=r;
    }
    if (min!=p){
        swap(min,p);
        heapify(min);
    }

}

template <class T>
bool Heap<T>::empty(){
    return (cont == 0);

}

template <class T>
void Heap<T>::swap(int a, int b){
    int c;
    c=datos[a];
    datos[a]=datos[b];
    datos[b]=c;

}

template <class T>
string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < cont; i++) {
		if (i != 0) {
			aux << " ";
		} aux << datos[i];
	} aux << "]";
	return aux.str();
}

