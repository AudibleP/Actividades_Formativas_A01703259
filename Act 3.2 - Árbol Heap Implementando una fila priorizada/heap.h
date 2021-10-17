#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>

////////////////////////////////////
template <class T>
class Heap{
private:
	T *datos;
	unsigned int tamano;
	unsigned int count;
	unsigned int pad(unsigned int) const;
	unsigned int izq(unsigned int) const;
	unsigned int der(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);

public:
	Heap(unsigned int);
	~Heap();
	void push(T);
	void pop();
	T top();
	bool empty() const;
	int size() const;
	std::string toString() const;
};

////////////////////////////////////
template <class T>
Heap<T>::Heap(unsigned int t) {
	tamano = t;
	datos = new T[tamano];
	count = 0;
}

////////////////////////////////////
template <class T>
Heap<T>::~Heap() {
	delete [] datos;
	datos = 0;
	tamano = 0;
	count = 0;
}

////////////////////////////////////
template <class T>
unsigned int Heap<T>::pad(unsigned int posi) const {
	return (posi - 1)/2;
}

////////////////////////////////////
template <class T>
unsigned int Heap<T>::izq(unsigned int posi) const {
	return (posi*2 + 1);
}

////////////////////////////////////
template <class T>
unsigned int Heap<T>::der(unsigned int posi) const {
	return (posi*2 + 2);
}

////////////////////////////////////
template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j){
	T aux = datos[i];
	datos[i] = datos[j];
	datos[j] = aux;
}

////////////////////////////////////
template <class T>
void Heap<T>::heapify(unsigned int posi){
	unsigned int iz = izq(posi);
	unsigned int de = der(posi);
	unsigned int min = posi;
	if (iz <= count && datos[iz] < datos[min]) {
		min = iz;
	}
	if (de <= count && datos[de] < datos[min]) {
		min = de;
	}
	if (min != posi) {
		swap(posi, min);
		heapify(min);
	}
}

////////////////////////////////////
template <class T>
void Heap<T>::push(T val){
	int posi;
	posi = count;
	count++;

	while(posi > 0 && val < datos[pad(posi)]){
		datos[posi] = datos[pad(posi)];
		posi = pad(posi);
	}
	datos[posi] = val;
}

////////////////////////////////////
template <class T>
void Heap<T>::pop(){
	T aux = datos[0];
	datos[0] = datos[--count];
	heapify(0);
}

///////////////////////////////////////
template <class T>
T Heap<T>::top(){
	T aux = datos[0];
	return aux;
}

////////////////////////////////////
template <class T>
bool Heap<T>::empty() const {
	return (count == 0);
}

////////////////////////////////////
template <class T>
int Heap<T>::size() const{
	return count;
}

////////////////////////////////////
template <class T>
std::string Heap<T>::toString() const{
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		}
		aux << datos[i];
	}
	aux << "]";
	return aux.str();
}

#endif
