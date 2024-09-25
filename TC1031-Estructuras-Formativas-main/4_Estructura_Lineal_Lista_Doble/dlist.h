/*DLIST:
Autor: Jose Pablo Gonzalez
ESte codigo es muy similar al codigo de lista encadenada,
solo que todas ya tienen un prev y un head, ademas de que
en funciones como update y destroyAt, divido la lista en
2.*/
#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>

using namespace std;

template <class T> class DList;

template <class T>
class Link {
    private:
        Link(T); //Constructor con valor apuntando a 0
        Link(T,Link<T>*); //Constructor con valor y apuntando a otro valor
        Link(const Link<T>&); // "Copiador"
        T valor; //Valor almacenado
        Link<T> *next; //Apuntador a siguiente valor
        Link <T> *prev; // Apuntador al valor anterior
        friend class DList<T>; //Para que Lista pueda acceder a los valores privados
};

template <class T>
Link<T>::Link(T val){
    valor = val;
    next=0;
}

template <class T>
Link<T>::Link(T val, Link<T>* next_){
    valor  = val;
    next = next_;
}

template <class T>
Link<T>::Link(const Link<T> &Sor_){
    valor = Sor_.value;
    next = Sor_.next;
}

template <class T>
class DList{
    private:
        Link<T> *head;
        Link <T> *tail;
        int size;
    public:
        DList();
        DList(const DList<T>&);

        
        bool checarVacia();
        void insertion(int);
        int search(int);
        void update(int, int);
        void deleteAt(int);
        string toStringForward() const;
        string toStringBackward() const;
};

//Constructor de la lista
template <class T>
DList<T>::DList(){
    head = 0;
    tail = 0;
    size = 0;
}

//Verificador de si la lista esta vacia
template <class T>
bool DList<T>::checarVacia(){
    return (head == 0);
}

template <class T>
void DList<T>::insertion(int valor){
    Link<T> *nuevoElemento, *p, *q;
    nuevoElemento = new Link<T>(valor);
    if (checarVacia()){
        nuevoElemento->next = 0;
        nuevoElemento->prev = 0;
        tail = nuevoElemento;
        head = nuevoElemento;
        size++;
        return;
    }
    p=tail;
    p->next=nuevoElemento;
    nuevoElemento->prev=p;
    tail=nuevoElemento;
    size ++;
}

//Busca un valor en especifico. ES IGUAL A EL DE LISTA ENCADENADA
template <class T>
int DList<T>::search(int valor){
    Link<T> *p;
    p=head;
    int cont = 0;
    while (p != 0){
        if (p -> valor == valor){
            return cont;
        }
        p = p->next;
        cont ++;
    }
    return -1;
}

//Como se menciono al inicio, divide la lista y usa next y head
//cuando es menor a la mitad, y prev y tail cuando es mayor.
template <class T>
void DList<T>::update(int indice, int valorNuevo){
    if (indice >= size|| indice<0){
        return;
    }
    Link<T> *p;
    if (size/2<=indice){
        p=tail;
        int cont = size-1;
        while (cont != indice ){
            p = p->prev;
            cont --;
            }
        p -> valor = valorNuevo;
        return;
    }
    p=head;
    int cont = 0;
    while (cont != indice ){
        p = p->next;
        cont ++;
    }
    p -> valor = valorNuevo;

}
//Como se menciono al inicio, divide la lista y usa next y head
//cuando es menor a la mitad, y prev y tail cuando es mayor.
template <class T> 
void DList<T>::deleteAt(int indice){
    if (indice >= size || indice<0){
        return;
    }
    Link<T> *p,*q;

    if (indice>=(size)/2){
        p=tail;
        q=p->prev;
        if (indice == size-1){
            tail=q;
            tail->next=0;
            delete p;
            size --;
            return;
        }
        int cont=size-2;
        while (cont != indice-1){
            p = p->prev;
            q = q->prev;
            cont --;
        }
        
        q -> next = p -> next; // Aqui me aseguro de que 
    //no se rompa la lista, conectando los demas elementos para que funcionen sin p.
        q -> next -> prev= q;
        delete p;
        size --;
        return;
    }
    
    p=head;
    q=p->next;
     if (indice == 0){
        head = q;
        head->prev=0;
        delete p;
        size --;
        return;
    }

    int cont = 1;
    while (cont != indice ){
        p = p->next;
        q = q->next;
        cont ++;
    }
    p -> next = q -> next; // Aqui me aseguro de que 
    //no se rompa la lista, conectando los demas elementos para que funcionen sin p.
    p -> next -> prev= p;
    delete q;
    size --;
    return;
}
template <class T>
string DList<T>::toStringForward() const {
	stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->valor;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
string DList<T>::toStringBackward() const {
	stringstream aux;
	Link<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->valor;
		if (p->prev != 0) {
			aux << ", ";
		}
		p = p->prev;
	}
	aux << "]";
	return aux.str();
}

#endif