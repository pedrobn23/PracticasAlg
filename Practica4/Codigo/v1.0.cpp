#include <set>
#include <utility>
#include <string>
#include <tuple>
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include "pieza.h"
#include <stack>

using namespace std;


const int FIL=6;
const int COL=9;

class Matriz {

private:
  int m[FIL][COL];

public:

  Matriz(){
    for(int i = 0; i < FIL; i++)
      for(int j = 0; j < COL; j++)
	m[i][j] = 0;
  }


  int get (int i, int j) const {
    assert (0<=i && i<FIL && 0<=j && j<COL);
    return m[i][j];
  }

  void set(int i, int j, int value){
    assert (0<=i && i<FIL && 0<=j && j<COL);

    m[i][j] = value;
  }

  
  bool llena () const{
    for (int i=0; i<FIL; ++i) {
      for (int j=0; j<COL; ++j) {
	if (!m[i][j])
	  return false;
      }
    }

    return true;
  }


  Matriz& operator=(const Matriz &m) {
    for (int i=0; i<FIL; ++i)
      for (int j=0; j<COL; ++j)
	this->set(i,j,m.get(i,j));
  }

  friend std::ostream& operator << (std::ostream& os, Matriz&m);
  
};


std::ostream& operator<<(std::ostream& os, Matriz& m) {
  for (int i=0; i<FIL; ++i) {
    for (int j=0; j<COL; ++j) {
      os <<  m.m[i][j] << ' ';
    }
    os << '\n';
  }
}


int ocupabajo (int pieza[5][5]) {
  // int i = 0, max = 0;
  // for (int j=0; j<5; ++j) {
  //   for ( i=0; i<5; ++i)
  //     if (!pieza[i][j]) break;
    
  //   max = max>i+1 ? max : i+1;

  // }

  // return max;


  int max = 0, maxActual = 0;
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++)
      {
	if(pieza[j][i])
	  maxActual++;

      }
    max = maxActual > max ? maxActual : max;
    maxActual = 0;
  }
}


//supervisa cuantas posiciones hacia abajo ocupa la pieza
// int ocupadcha (int pieza[5][5]) {
//   int j = 0, max = 0,realmax = 0;
//   for (int i=0; i<5; ++i) {
//     for ( j= 0; j<5; ++j){
//       if (pieza[i][j]!=0)      
// 	max = max >j+1 ? max : j+1;
//     }
//   }

//   return max;
// }

int ocupadcha (int pieza[5][5]) {
  int max = 0, maxActual = 0;
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++)
      {
	if(pieza[i][j])
	  maxActual++;

      }
    max = maxActual > max ? maxActual : max;
    maxActual = 0;
  }
}

bool cabe (const Matriz &tab, int pieza[5][5], pair<int,int> p1) {
  int derecha = ocupadcha(pieza),abajo = ocupabajo(pieza);
  
  if ((FIL - p1.first <= abajo-1)|| (COL-p1.second <= derecha-1))
    return false;

  
  for (int i=0,k=p1.second; i<derecha && k<COL; ++i, ++k) {
    for (int j=0,  h=p1.first;j<abajo && h<FIL; ++j, ++h) {
      if (pieza[j][i] && tab.get(h,k)) {
	return false;
      }
    }
  }

  return true;
}



bool cabe (const Matriz &tab, int pieza[5][5], int h, int j) {
    assert (0<=h && h<FIL && 0<=j && j<COL);
  return cabe (tab, pieza, pair<int,int> (h,j));
}

void colocar  (Matriz &tab, int pieza[5][5], pair<int,int> p1) {
  for (int i=0,k=p1.second; i<ocupadcha(pieza) && k<COL; ++i, ++k) {
    for (int j=0,  h=p1.first;j<ocupabajo(pieza) && h<FIL; ++j, ++h) {
      tab.set(h, k, pieza[j][i] | tab.get(h,k));
    }
  }
}

void colocar(Matriz &sol, int pieza[5][5], int h, int j) {

  return colocar(sol, pieza, pair<int,int> (h, j));
}



bool resolver (int pieza[8][4][5][5] , Matriz &tab, int indice){
  //si hemos conseguido llenar la matriz hemos ganado
  if (tab.llena() )
    return true;

  //Iteramos sobre las rotaciones
  for (int i=0; i<4; ++i){

    //con estos dos bucles y el if cogemos todas las casillas libres
    for (int j=0; j<FIL; ++j){
      for (int k=0; k<COL; ++k){
	if (!tab.get(j,k)){ //cuando valga 0

	  
	  
	  if (!cabe(tab, pieza[indice][i], j, k))
	    continue;
	  
	  Matriz copiaDeSeguridad = tab;	  
	  colocar (tab, pieza[indice][i], j, k);
	  indice++;
	  
	  bool resuelto = resolver(pieza, tab, indice);

	  if(resuelto)
	    return true; 
	  else{
	    indice--;
	    tab = copiaDeSeguridad;
	  }
	}
      }
    }
  }
    return false;  
}

int main () {
  Matriz tab;
  resolver (pieza, tab, 0);
  cout << tab;
}
 
