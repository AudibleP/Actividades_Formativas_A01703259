
#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

class Funciones
{
public:
    int sumaIterativa(int n);
    int sumaRecursiva(int n);
    int sumaDirecta(int n);
};

int Funciones::sumaIterativa(int n){
    int suma = 0;
    int i = 1;
    while (i<=n){
        suma += i;
        i++;
    }
    return suma;
}

int Funciones::sumaRecursiva(int n){
    if (n == 0) {
        return 0;
    } else {
        return n + sumaRecursiva(n - 1);
    }
}

int Funciones::sumaDirecta(int n){
  int suma = (n*(n+1))/2;
  return suma;
}

#endif
