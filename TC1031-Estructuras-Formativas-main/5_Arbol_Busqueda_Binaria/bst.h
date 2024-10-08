#ifndef BST_H_
#define BST_H_
/*Tarea 5:BST
Autor: José Pablo Gonzalez
Este codigo se enfoca en recorrer un BST de multiples formas,
ademas de otras funciones útiles.
*/

#include <string>
#include <sstream>

using namespace std;

template <class T> class BST;
template <class T> 
class Node{
    private:
        Node <T> *right, *left;//Apuntadores a los Nodos hijos
        T value; //Valor de mi nodo
    public:
        Node(T); //Constructor
        Node(T,Node<T>*,Node<T>*); //Constructor
        void add(T);
        bool find(T);
        void preorder(string &);
        void inorder(string &);
        void postorder(string &);
        int height();
        string ancestors(T, string &);
        int whatLevelamI(T);
        void byLevel(string &, int);

};

//Constructor Vacio 
template <class T>
Node<T>::Node(T val){
    value=val;
    right=0;
    left=0;
}

// Copiador
template <class T>
Node<T>::Node(T val,Node<T> *r, Node<T> *l){
    value=val;
    right = r;
    left = l;
}

//Suma valores al arból. Se asegura de posicionarlos depedniendo de su valor
//ademas de añadirlos en el nivel mas bajo. Es recursiva.
template <class T>
void Node<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} else {
			left = new Node<T>(val);
		}
	} else {
		if (right != 0) {
			right->add(val);
		} else {
			right = new Node<T>(val);
		}
	}
}

// Funcion recursiva que funcióna como busqueda binaria,
//haciendo uso de la division de right y left.
template <class T>
bool Node<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
	}
	
}

//Los ordena tal cual encuentra, moviendose de izq a derecha y de arriba a abajo.
template <class T>
void Node<T>::preorder(string &res){
    res += to_string(value);
    if (left != 0){
        res += " ";
        left -> preorder(res);
    }
    if (right != 0){
        res += " ";
        right -> preorder(res);
    }
}

// Los ordena en el orden que deben de estar, empezando desde el valor de la izq. mas 
// bajo. 
template <class T>
void Node<T>::inorder(string &res){
    if (left !=0){
        left -> inorder(res);
    }
    res += to_string(value);
    res += " ";
    if (right !=0){
        right ->inorder(res);
    }
}

// Imprime los valores mas bajos primero, siempre de izq a derecha con esta lógica.
template <class T>
void Node<T>::postorder(string &res){
    if (left !=0){
        left -> postorder(res);
    }
    if (right !=0){
        right ->postorder(res);
    }
    res += to_string(value);
    res += " ";

}

//Función recursiva que compara la longitud de ambas ramas
// y regresa la mas grande. Se usa para sacar la profundidad total.
template <class T>
int Node<T>::height(){
    int rh = 1, lh = 1;
    if (right ==0 && left == 0){
        return 1;
    }
    if (right !=0){
        rh=1+right->height();
    }
    if (left !=0){
        lh=1+left->height();
    }
    if (rh > lh){
        return rh;
    }
    else{
        return lh;
    }

}

// Funciona similar al find, solo que va imrpimiendo cada valor que
// recorre. 
template <class T>
string Node<T>::ancestors(T val, string &res){
    if (val == value) {
		return res;
	}
    else{
        res += to_string(value)+" ";
        if (val < value) {
		    left ->ancestors(val, res);
	    } 
        else if (val > value) {
		    right -> ancestors(val, res);
	    }
        return res;
    }


}

// Funciona igual que el find, solo que va sumando a un total 
// y regresa la suma recursiva una vez encuentra el valor.
template <class T>
int Node<T>::whatLevelamI(T val){
    if (value == val){
        return 1;
    }
    else if (value < val){
        return 1+ right -> whatLevelamI(val);
    }
    else if (value > val){
        return 1+ left ->whatLevelamI(val);
    }
}

template <class T>

// Función que va imprimiendo valores de un nivel. Se usa en 
// visit
void Node<T>::byLevel(string &res, int level){
    if (level == 1){
        res+=to_string(value) + " ";
    }
    else{
        if (left !=0){
            left ->byLevel(res,level-1);
        }
        if (right !=0){
            right->byLevel(res, level-1);
        }
    }
}

template <class T>
class BST{
    private:
        Node <T> *root; 
    public:
        BST();
        BST(T);
        string visit();
        void add(T);
        bool find(T);
        int height();
        string ancestors(T);
        int whatlevelamI(T);
};


template <class T>
BST<T>::BST(){
    root = 0;
}

template <class T>
void BST<T>::add(T value){
    if (root != 0) {
		if (!root->find(value)) {
			root->add(value);
		}
	} else {
		root = new Node<T>(value);
	}
}

template <class T>
bool BST<T>::find(T val) {
	if (root != 0) {
		return root->find(val);
	} 
    else {
		return false;
	}
}

template <class T>
string BST<T>::visit(){
    string res;
    int treeH;
    int level = 1;
    res += "[";
    root ->preorder(res);
    if (res.back() == ' ') {  //APOYO DE FUNCION EXTERNA, SOLO USADA PARA QUE NO AGREGUE UN ESPACIO
        res.pop_back();
    }
    res += "]";
    res += "\n";
    res += "[";
    root ->inorder(res);
    if (res.back() == ' ') { 
        res.pop_back(); 
    }
    res += "]";
    res += "\n";
    res += "[";
    root ->postorder(res);
    if (res.back() == ' ') {  
        res.pop_back(); 
    }
    res += "]";
    res += "\n";
    res += "[";
    treeH=root->height();
    while (level<=treeH){
        root->byLevel(res,level);
        level +=1;
    }
    if (res.back() == ' ') {  
        res.pop_back(); 
    }
    res += "]";
    return res;
}
template <class T>
int BST<T>::height(){
    return root->height();
}

template <class T>
string BST<T>::ancestors(T val){
    string res;
    res += "[";
    if (root != 0 && root->find(val)) {
		root->ancestors(val, res);
	}
    if (res.back() == ' ') {  //APOYO DE FUNCION EXTERNA, SOLO USADA PARA QUE NO AGREGUE UN ESPACIO :)
        res.pop_back();
    }
    res += "]";

    return res;
}

template <class T>
int BST<T>::whatlevelamI(T val){
    return root -> whatLevelamI(val);
}
#endif
