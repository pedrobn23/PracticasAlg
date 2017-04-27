#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

/*
 * Devuelve 0 si el elemento i del vector v cumple con el predicado,
 * -1 si está a la derecha del elemento que lo cumple, y 1 si está a
 * su izquierda.
 */
int predicado(int *v, int i)
{
    if(v[i] > v[i-1] && v[i] > v[i+1])
	return 0;

    return v[i] < v[i+1] ? 1 : -1;
}

/*
 * Realiza una búsqueda binaria en el vector v de tamaño n usando
 * el predicado pred, es decir, encuentra el elemento para el que
 * pred devuelve cero.
 */
int busquedaBinaria(int *v, int n, int(*pred)(int *v, int i))
{
    int k = n/2;
    int l = k, res = 1;

    while(res != 0)
    {
	res = pred(v, k);

	l /= 2; if(l == 0) l = 1;
	k += res*l;
    }

    return k;
}

double uniforme(){ //Genera un número uniformemente distribuido en el
                   //intervalo [0,1) a partir de uno de los generadores
                   //disponibles en C.
	double u;
	  u = (double) rand();
	  u = u/(double)(RAND_MAX+1.0);
	return u;
}

int main()
{
    int n = 100;
    int *T = new int[n];
    std::srand(std::time(NULL));
    double u=uniforme();
    int p=1+(int)((n-2)*u);
       
    T[p]=n-1;
    for (int i=0; i<p; i++) T[i]=i;
    for (int i=p+1; i<n; i++) T[i]=n-1-i+p;

    for(int i=0; i<n; i++)
    	std::cout << " " << T[i];

    std::cout << "Máximo: " << p << " encontrado: " << busquedaBinaria(T, n, predicado) << std::endl;
    
    return 0;
}
