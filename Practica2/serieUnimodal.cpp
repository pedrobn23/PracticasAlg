#include <iostream>
#include <vector>

 using namespace std;

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
	int res;
	if(n==1)
		return n;

	else if(n==2)
		return v[0]>v[1]?0:1;

	else if(v[k] > v[k+1] && v[k] < v[k-1]) 
		return k;

	else if(v[k] > v[k+1]){
		res=divideYVenceras(v,k);
		return res;

	}else{
		res=divideYVenceras(v+k,n-k);
		return k+res-1;
	}	
}

int main(){

}
