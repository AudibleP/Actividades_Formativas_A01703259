#ifndef sorts_h
#define sorts_h

#include <vector>
#include <iostream>
#include <list>

using namespace std;

template < class T >
class Sorts {

  private:
    void swap(vector<T>&vec, int, int); 
    void copyArray(vector<T>& , vector<T>& , int , int );
    void mergeArray(vector<T>& A, vector<T>& B, int i, int j, int k);
    void mergeSplit(vector<T>& , vector<T>& , int , int );   

  public:
    void ordenaSeleccion(vector<T>&);
    void ordenaBurbuja(vector<T>&);
    void ordenaMerge(vector<T>&);
    int busqBinaria(vector<T>&, int);
    int busqSecuencial(vector<T>&, int);
};

template <class T>
void Sorts<T>::swap(vector<T> &vec, int i, int j) {
	int aux = vec[i];
	vec[i] = vec[j];
	vec[j] = aux;
}

template <class T>
void Sorts<T>::ordenaSeleccion(vector<T> &vec){ 

  for (int i = 0; i < vec.size(); i++) {
		int index = i;
		for (int j = i; j <= vec.size() - 1; j++) {
			if (vec[j] < vec[index]) {
				index = j;
			}
		}

		if (index != i) {
			swap(vec, i, index);
		}
	}
}


template <class T>
void Sorts<T>::ordenaBurbuja(vector<T> &vec) {

    for (int i = vec.size() - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (vec[j] > vec[j + 1]) {
                swap(vec, j, j + 1);
            }
        }
    }
}

template <class T>
void Sorts<T>::ordenaMerge(vector<T> &vec) {
	vector<T> aux(vec.size());

	mergeSplit(vec, aux, 0, vec.size() - 1);
}

template <class T>
void Sorts<T>::mergeSplit(vector<T> &A, vector<T> &B, int inf, int sup) {
	int med;

	if ( (sup - inf) < 1 ) {
		return;
	}
	med = (sup + inf) / 2;
	mergeSplit(A, B, inf, med);
	mergeSplit(A, B, med + 1, sup);
	mergeArray(A, B, inf, med, sup);
	copyArray(A, B, inf, sup);
}

template <class T>
void Sorts<T>::mergeArray(vector<T> &A, vector<T> &B, int inf, int med, int sup) {
	int i, j, k;

	i = inf;
	j = med + 1;
	k = inf;

	while (i <= med &&j <= sup) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > med) {
		for (; j <= sup; j++) {
			B[k++] = A[j];
		}
	} else {
		for (; i <= med; i++) {
			B[k++] = A[i];
		}
	}
}

template <class T>
void Sorts<T>::copyArray(vector<T> &A, vector<T> &B, int inf, int sup) {
	for (int i = inf; i <= sup; i++) {
		A[i] = B[i];
	}
}

template <class T>
int Sorts<T>::busqSecuencial(vector<T> &vec, int val) {
    for (int i = 0; i < vec.size(); i++) {
        if (val == vec[i])
            return i;
    }
    return -1;
}

template <class T>
int Sorts<T>::busqBinaria(vector<T> &vec, int val) {
  ordenaBurbuja(vec);
	int inf = 0;
	int sup = vec.size() - 1;

	while (inf < sup) {
		int med = (sup + inf) / 2;
		if (val == vec[med]) {
			return med;
		} else if (val > vec[med]) {
			inf = med + 1;
		} else if (val < vec[med]) {
			sup = med - 1;
		}
	}
	return -1;
}

#endif