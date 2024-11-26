

/*Implementacion del Hash
Jose Pablo Gonzalez
Como dice cuadratica, use 
la forma de i+j*j
*/
#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>

using namespace std;

template <class Key, class Value>
class Quadratic{
    private:
        unsigned int (*func) (const Key);
        unsigned int size;
        unsigned int count;

        Key *keys;
        Key Valorinicial;
        Value *Valores;

        long indice(const Key) const;
    public:
        Quadratic(unsigned int, Key, unsigned int(*f)(const Key));
        bool full() const;
        bool put(Key,Value);
        string toString() const;
        Value get(const Key);
};



template <class Key, class Value>
long Quadratic<Key, Value>::indice(const Key k) const {
	unsigned int i, j=0, inicio = 0;
    inicio = i = func(k) % size;
    do {
    i = (inicio + j * j) % size;
    if (keys[i] == k) {
        return i;
    }
    j++;
    } while (j < size);
    return -1;
}

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int(*f)(const Key)){
    size=sze;
    keys=new Key[size];
    Valorinicial=init;
    for (int i=0;i<size;i++){
        keys[i]=init;
    }
    Valores = new Value[size];
    for (int i=0; i<size; i++){
        Valores[i]=0;
    }
    func =f;
    count=0;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const{
    return(count>size);
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key a, Value b){
    unsigned int i, j=0, inicio=0;
    long posicion;

    if (full()){
        return false;
    }
    posicion=indice(a);
    if(posicion!=-1){
        Valores[posicion]=b;
        return true;
    }

    inicio = i = func(a) % size;
    do {
    i = (inicio + j * j) % size;
    if (keys[i] == Valorinicial) {
        keys[i] = a;
        Valores[i] = b;
        count++;
        return true;
    }
    j++;
    } while (j < size);

	return false;
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k){
    unsigned int i, inicio;
    long pos;

    pos = indice(k);
    if (pos != -1){
        return Valores[pos];
    }
    else{
        return Valores[0];
    }
}

template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;
	for (int i = 0; i < size; i++){
			if (keys[i] != Valorinicial){
				aux << "(" << i << " ";
			  aux << keys[i] << " : " << Valores[i] << ") ";
			}
	}
	return aux.str();
}

#endif
