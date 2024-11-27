#ifndef SPLAY_H_
#define SPLAY_H_

//Autor: Jose Pablo Gonzalez

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

using namespace std;
template <class T> class SplayTree;

template <class T> 
class Node{
    private:
        T valor;
        Node *right, *left, *parent;
    public:
        Node(T);
        Node<T>* add(T);
        Node<T>* splay(Node<T>*, Node<T>*);
        Node<T>* rotR(Node<T>*);
        Node<T>* rotL(Node<T>*);
        string inorder(string &);
        string preorder(string &);
        Node<T>* find(T);
    friend class SplayTree<T>;
};

//Constructor de nodos
template <class T>
Node<T>::Node(T valor_){
    right=0;
    left=0;
    parent=0;
    valor=valor_;
}

//Funcion de add, aqui solo crea el nodo y lo regresa para usarse despues.
template <class T>
Node<T>* Node<T>::add(T val){
    if (val<valor){
        if (left !=0){
            return left->add(val);
        }
        else{
            left = new Node<T>(val);
            left->parent=this;
            return left;
        }
        
    }
    else if(val>valor){
        if (right !=0){
            return right->add(val);
        }
        else{
            right = new Node<T>(val);
            right->parent=this;
            return right;
        }
    }
    return this;
}


//Codigo como se vio en clase para las rotaciones para der.
template <class T>
Node<T>* Node<T>::rotR(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;
	y->parent = x->parent;
	x->parent = y; 
	if(y->parent){
		if(y->parent->left && y->parent->left->valor == x->valor)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

//Codigo como se vio en clase para rotaciones para izq.
template <class T>
Node<T>* Node<T>::rotL(Node<T>* x){
	Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;
	y->parent = x->parent;
	x->parent = y;
	if(y->parent){
		if(y->parent->left && y->parent->left->valor == x->valor)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

/*Funcion de splay, la que se asegura de mover los nodos "relevantes" hasta arriba.
Esta funcion se encarga de antes que nada, verificar si usamos el movimiento de zig, zag, 
zig-zig, zag-zag, zig-zag o zag,zig. Y asi va rotando el arbol hasta que quede con el nodo
x en la raiz. Las rotaciones no las hace este, si no que llama a las funciones respectivas.*/
template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
    while(x->parent != 0){
        if(x->parent->parent == 0){
			if(x->parent->left && x->parent->left->valor == x->valor){
				rotR(x->parent);
			}
         else{
				rotL(x->parent);
			}
        }
        else{
			Node<T>*p = x->parent; 
			Node<T>*g = p->parent; 
			if(p->left && g->left && x->valor == p->left->valor && p->valor == g->left->valor){
				rotR(g);
				rotR(p);
			}else if(p->right && g->right && x->valor == p->right->valor && p->valor == g->right->valor){
				rotL(g);
				rotL(p);
			}else	if(p->left && g->right &&x->valor == p->left->valor && p->valor == g->right->valor){
				rotR(p);
				rotL(g);
			}else{
				rotL(p);
				rotR(g);
			}
		}
    }
    return x;
}

//Se crea un string inorder, osea left, valor del nodo, right, usando recursion.
template <class T>
string Node<T>::inorder(string &res){

    if (left != 0) {
		left->inorder(res);
	}
    if (!res.empty()){
            res+= " ";
    }
	res+= to_string(valor);
	if (right != 0) {
		right->inorder(res);
	}
    return res;
}
//Se crea un string preorder, osea valor, left y right, usando recursion.
template <class T>
string Node<T>::preorder(string &res){
    if (!res.empty()) {
        res += " ";
    }
    res+= to_string(valor);
	if (left != 0) {
		left->preorder(res);

	}
	if (right != 0) {
		right->preorder(res);
	}
    return res;
}

//Busca el valor como en un arbol normal, no hace splay en esta parte.
template <class T>
Node<T>* Node<T>::find(T val){
    if(val==valor){
        return this;
    }
    if (val>valor && right!=0){
        return right->find(val);
    }
    else if (val<valor && left!=0){
        return left->find(val);
    }
    return this;
}


template <class T>
class SplayTree{
    private:
        Node<T> *root;
    public:
        SplayTree();
        bool empty();
        void add(T);
        bool find(T);
        bool remove(T);
        string inorder();
        string preorder();
};

//Constructor de arboles Splay. 
template <class T>
SplayTree<T>::SplayTree(){
    root = 0;
}

//Verifica si el arbol esta vacio
template <class T>
bool SplayTree<T>::empty(){
    return (root == 0);
}

/*Llama a el add de los nodos en caso de que root ya este ocupado (si no solo deja el nuevo no ahi),
y despues llama a splay para acomodar al nuevo valor como la nueva raiz del arbol.*/
template <class T>
void SplayTree<T>::add(T val){
    if (empty()){
        root=new Node<T>(val);
    }
    else{
        Node<T> *nuevo=root->add(val);
        root=nuevo->splay(root,nuevo);
    }
}

//Llama al inorder de los nodos y ademas le agrega los corchetes.
template <class T>
string SplayTree<T>::inorder(){
    string r;
    if (empty()){
        return("[]");
    }
    root->inorder(r);
    r+="]";
    return "["+r;
}

//Llama al preorder de los nodos y ademas le agrega los corchetes.
template <class T>
string SplayTree<T>::preorder(){
    string r;
    if (empty()){
        return("[]");
    }
    root->preorder(r);
    r+="]";
    return "["+r;
}

/*Busca el valor llamando a la funcion find de los nodos, y de ahi toma este nodo
y lo pasa para arriba con la funcion de splay*/
template <class T>
bool SplayTree<T>::find(T val){
    if (empty()){
        return false;
    }
    else{
        Node<T>* ans;
        ans=root->find(val);
        root=root->splay(root,ans);
        return true;
    }
}

//Faltante, no la pude resolver y debo de revisarla mas a detalle.
template <class T>
bool SplayTree<T>::remove(T val){
    return false;
}


#endif
