# ifndef LIST_H_
# define LIST_H_

#include <string>
#include <sstream>

using namespace std;

template <class T> class List;

/*Creador de la clase Link, la cual es como un objeto dentro de 
nuestra lista*/
template <class T> 
class Link {
    private:
        Link(T); //Constructor con valor apuntando a 0
        Link(T,Link<T>*); //Constructor con valor y apuntando a otro valor
        Link(const Link<T>&); // "Copiador"
        T valor; //Valor almacenado
        Link<T> *next; //Apuntador a siguiente valor
        friend class List<T>; //Para que Lista pueda acceder a los valores privados
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

/*Defincion de la calse Lista, junto con todas las acciones
que pide la tarea.*/
template <class T>
class List{
    private:
        Link<T> *head;
        int size;

    public:
        List();
        List(const List<T>&);

        bool checarVacia();
        void insertion(int);
        int search(int);
        void update(int, int);
        void deleteAt(int);
        string toString() const;


};
// Constructor de lista
template <class T>
List<T>::List(){
    head = 0;
    size = 0;
}

//Verificador de si la lista esta vacia
template <class T>
bool List<T>::checarVacia(){
    return (head == 0);
}

//Agrega un valor al final de la lista
template <class T>
void List<T>::insertion(int valor_){
    Link <T> *nuevoElemento, *p;
    nuevoElemento = new Link<T>(valor_);

    if (checarVacia()){
        nuevoElemento->next = head;
        head = nuevoElemento;
        size++;
        return;
    }

    p = head;
    while (p -> next != 0){
        p = p->next;
    }
    nuevoElemento -> next = 0;
    p -> next = nuevoElemento;
    size ++;

}

//Busca un valor, recorriendo desde el head hasta 
//el ultimo nodo
template <class T>
int List<T>::search(int valorBuscado){
    Link<T> *p;
    p=head;
    int cont = 0;
    while (p != 0){
        if (p -> valor == valorBuscado){
            return cont;
        }
        p = p->next;
        cont ++;
    }
    return -1;
}

//Cambia el valor de un Link a un valor indicado
template <class T>
void List<T>::update(int indice, int valorNuevo){
    if (indice > size|| indice<0){
        return;
    }
    Link<T> *p;
    p=head;
    int cont = 0;
    while (cont != indice ){
        p = p->next;
        cont ++;
    }
    p -> valor = valorNuevo;

    return;
}

//Elimina un Link de la lista
template <class T>
void List<T>::deleteAt(int indice){
    if (indice > size || indice<0){
        return;
    }
    Link<T> *p,*q;
    p=head;
    q=p->next;
    if (indice == 0){
        head = q;
        delete p;
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
    delete q;
    return;
}

// FUNCION IMPORTADA DE MAIN PARA TAREA
template <class T>
string List<T>::toString() const {
	std::stringstream aux;
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

#endif