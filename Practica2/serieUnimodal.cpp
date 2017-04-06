#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>

 using namespace std;
#define Millon 1000000 

/*
 * Empezamos en i=1 porque sabemos por el enunciado que nunca estará el máximo en la posición 0 
 * y la ultima posición que comprobamos es la i=n-2 porque tampoco va a estar nunca en la 
 * posición i=n-1 y en caso que realizase la comprobación con algún vector en dicha posición
 * daría violación de segmento.
*/
int fuerzaBruta(int* v, int n){
	for(int i=1; i < n-1; ++i){
     if(v[i] > v[i+1])
       return i;
	}
}

int divideYVenceras(int* v, int n){
	int k = n/2;
	if(n==1)
		return 0; //Caso trivial
	
	if(n==2)
		return v[0]>v[1]?0:1; //Entre dos elementos, manda el más pequeño.

	if(v[k] > v[k+1]){

		if(v[k] > v[k-1]) 
			return k;

		//else
		return divideYVenceras(v,k);

	}

	//else
	return k + 1 + divideYVenceras(v+k+1,n-k-1);
}

//generador de ejemplos para el problema de la serie unimodal de números. Se genera un índice aleatorio entre 1 y n-2, se asigna el mayor entero (n-1) a ese índice, a los índices anteriores a p se le asignan valores en orden creciente (0,1,...,p-1) y a los índices mayores que p se le asignan valores en orden decreciente (n-2, n-1,...,p

double uniforme(){ //Genera un número uniformemente distribuido en el
                   //intervalo [0,1) a partir de uno de los generadores
                   //disponibles en C.
	double u;
	  u = (double) rand();
	  u = u/(double)(RAND_MAX+1.0);
	return u;
}

int main(int argc, char * argv[]){
	clock_t tantes,tantes1;    // Valor del reloj antes de la ejecuci�n
	clock_t tdespues,tdespues1;  // Valor del reloj despu�s de la ejecuci�n
	if (argc != 2){
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);

  int * T = new int[n];
  assert(T);

	srand(time(0));
	double u=uniforme();
	int p=1+(int)((n-2)*u);
	T[p]=n-1;
	for (int i=0; i<p; i++) T[i]=i;
	for (int i=p+1; i<n; i++) T[i]=n-1-i+p;

	//for (int j=0; j<n; j++) {cout << T[j] << " ";}

	//Tiempo con fuerza bruta
	tantes = clock();
	fuerzaBruta(T, n);
  	tdespues = clock();
	//Tiempo con divide y vencerás
	tantes1 = clock();
	divideYVenceras(T,n);
	tdespues1 = clock();

  	cout << argv[1] << " " << (((double)(tdespues-tantes))/CLOCKS_PER_SEC) << " " << (((double)(tdespues1-tantes1))/CLOCKS_PER_SEC) << endl;

	delete T;

}
