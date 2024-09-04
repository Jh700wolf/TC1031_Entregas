/*
Nombre: Jose Pablo Gonzalez Avila
Matricula: A01706819
Fecha: 28/08/2024

Tarea: Algoritmos de busqueda y ordenacion
*/
#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
#include <list>

using namespace std;
template <class T>
class Sorts{
    private:
        void swap(vector<T>&, int, int);
        void split(vector<T>&,vector<T>&,int,int);
        void merge(vector<T>&,vector<T>&,int,int,int);
        void copyPaste(vector<T>&,vector<T>&,int,int);
    public:
        vector<T> ordenaSeleccion(vector<T>&);
        vector<T> ordenaBurbuja(vector<T>&);
        vector<T> ordenaMerge(vector<T>&);




        int busqSecuencial (const vector<T>&, int n);
        int busqBinaria (const vector<T>&, int n);


};
// Funcion de ayuda para realizar el Swap de posiciones. Se usa en orden seleccion y bubble. 
template <class T>
void Sorts<T>::swap(vector<T> &v, int i, int j){
    T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

// Funcion de Seleccion
template <class T>
vector<T> Sorts<T>::ordenaSeleccion(vector<T> &v){
    for(int i=0; i<v.size();i++){
        int aux=i;
        for (int j=i+1; j<v.size();j++){
            if (v[aux]>v[j]){
                aux=j;
            }
        }
        if (aux != i)
            swap(v,i,aux);
    }
    return v;
}

//Funcion Burbuja
template <class T>
vector<T> Sorts<T>::ordenaBurbuja(vector<T> &v){
    for (int i=v.size()-1; i>0; i--){
        for (int j=0;j<i;j++){
            if (v[j]>v[j+1]){
                swap(v,j,j+1);
            }
        }
    }
    return v;
}

//Funcion Merge y las de ayuda que son split (para cuando vas bajando), 
//merge(para volver a juntar los pedazos en orden) y copyPaste
//(la cual me sirve para guardar todo el el arreglo original)
template <class T>
vector<T> Sorts<T>::ordenaMerge(vector<T> &v){
    int leng = v.size();
    vector <T> aux(leng);
    split(v,aux,0,leng-1);

    return v;
}

template <class T>
void Sorts<T>::merge(vector<T> &a, vector<T> &b, int low, int mid, int high){
    int i = low;
    int j= mid+1;
    int k=low;
    while (i<=mid && j<= high){
        if(a[i]<a[j]){
            b[k]=a[i];
            i++;
        }
        else{
            b[k]=a[j];
            j++;
        }
        k++;
    }
    if (i>mid){
        for(;j<=high;j++){
            b[k++]=a[j];
        }
    }
    else{
        for(;i<=mid;i++){
            b[k++]=a[i];
        }
    }
}

template <class T>
void Sorts<T>::split(vector<T>&a,vector<T>&b,int low,int high){
    if ((high-low)<1){
        return;
    }
    int mid = (high+low)/2;
    split(a,b,low,mid);
    split(a,b,mid+1,high);
    merge(a,b,low,mid,high);
    copyPaste(a,b,low,high);

}
template <class T>
void Sorts<T>::copyPaste(vector<T> &a,vector<T> &b, int low, int high ){
    for (int i=low; i<=high;i++){
        a[i]=b[i];
    }

}

//Una busqueda normal, que recorre todo el arreglo buscando el item
template <class T>
int Sorts<T>::busqSecuencial(const vector<T> &source, int n){
    int tam= source.size();
    int ans=0;
    for(int i= 0; i<tam;i++){
        if (n==source[i]){
            return i;
        }
    }
    return -1;
}

//Una busqueda binaria, que divide la lista en pedazos, dependiendo si el item
//buscado es mayor o menor q la mitad. 
template <class T>
int Sorts<T>::busqBinaria(const vector<T> &source, int n){
    int low = 0;
    int high = source.size()-1;
    while (low<high){
        int mid = (low+high)/2;
        if (n==source[mid]){
            return mid;
        }
        else if (n>source[mid]){
        low = mid+1;
        }
        else if (n< source[mid]){
        high = mid-1;
        }

    }
    return -1;
}
#endif 