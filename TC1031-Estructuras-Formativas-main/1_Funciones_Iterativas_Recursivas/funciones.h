/*
 * funciones.h
 *
 *  Created on: 19/08/2024
 *      Author: José Pablo Gonzalez Avila
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
using namespace std;

class Funciones{
    public:
        long sumaIterativa(int num);
        long sumaRecursiva(int num);
        long sumaDirecta(int num);

};

long Funciones::sumaIterativa(int num){
    long total = 0;
    for (int i=1;i<=num;i++){
        total+=i;
    }
    return total;
}

long Funciones::sumaRecursiva(int num){
    if (num==0){
        return 0;
    }
    if (num<=1){
        return 1;
    }
    return sumaRecursiva(num-1)+num;
}
long Funciones::sumaDirecta(int num){
    if (num==0){
        return 0;
    }
    if (num<=1){
        return 1;
    }
    return (num*(num+1))/2;
}
#endif