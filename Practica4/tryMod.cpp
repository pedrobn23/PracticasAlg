#include <vector>
#include <utility>
#include <string>
#include <tuple>
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include "piezamod.h"
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
    assert (i<FIL && j<COL);
	      
    return m[i][j];
  }

  void set(int i, int j, int value){
    m[i][j] = value;
  }

  
bool llena () const{
  for (int i=0; i<FIL; ++i) {
    for (int j=0; j<COL; ++j) {
      if (![i][j])
	return false;
    }
  }

  return true;
}

  // la comento por la posibilidad de que sea innecesaria
  //
  // pair <int,int> primeraLibre () {
  //   for (int i=0; i<FIL; ++i) {
  //     for (int j=0; j<COL; ++j) {
  // 	if (!m[i][j])
  // 	  return pair <int,int> (i,j);
  //     }
  //   }

  //   return  pair<int,int> (-1,-1);
  // }
 
  
  Matriz& operator=(const Matriz &m) {
    for (int i=0; i<FIL; ++i)
      for (int j=0; j<COL; ++j)
	this->set(i,j,m.get(i,j));
  }

  friend std::ostream& operator << (std::ostream& os, Matriz&m);
  
};

 //Sobrecarga del operador de escritura
   std::ostream& operator<<(std::ostream& os, Matriz& m) {
    for (int i=0; i<FIL; ++i) {
      for (int j=0; j<COL; ++j) {
  	os <<  m.m[i][j] << ' ';
      }
      os << '\n';
    }
  }

//supervisa cuantas posiciones a la derecha ocupa la pieza
int ocupabajo (int pieza[5][5]) {
  int i = 0, max = 0;
  for (int j=0; j<5; ++j) {
    for ( i=0; i<5; ++i)
      if (!pieza[i][j]) break;
    
    max = max>i+1 ? max : i+1;

  }

  return max;
}


//supervisa cuantas posiciones hacia abajo ocupa la pieza
int ocupadcha (int pieza[5][5]) {
  int j = 0, max = 0;
  for (int i=0; i<5; ++i) {
    for ( j= 0; j<5; ++j)
      if (!pieza[i][j]) break;
      
    max = max >j+1 ? max : j+1;

  }

  return max;
}


bool cabe (const Matriz &tab, int pieza[5][5], pair<int,int> p1) {
  int derecha = ocupadcha(pieza),abajo = ocupabajo(pieza);
  
  if ((FIL - p1.first <= derecha-1)|| (COL-p1.second <= abajo-1))
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


//esta funcion es para poder cambiar la interfaz de la funcion
bool cabe (const Matriz &tab, int pieza[5][5], int h, int j) {
  return cabe (tab, pieza, pair<int,int> (h,j));
}

void colocar  (Matriz &sol, int pieza[5][5], pair<int,int> p1) {
  for (int i=0,k=p1.second; i<ocupadcha(pieza) && k<COL; ++i, ++k) {
    for (int j=0,  h=p1.first;j<ocupabajo(pieza) && h<FIL; ++j, ++h) {
      sol.set(h, k, pieza[j][i] | tab.get(h,k));
    }
  }
}

void colocar(Matriz &sol, int pieza[5][5], int h, int j) {
  return colocar(sol, pieza, h, j);
}



//Esta funcion resuelve el problema por backtrack, hay que pasarle el vector de
//piezas a usar y la matriz donde se almacena la solucion
// bool resolver (int pieza[8][4][5][5] , Matriz &tab, int rep){
//   pair <int,int> p1 = tab.primeraLibre();
//   bool resolucionPosible = false, pos=false;
//   Matriz copiaMatriz;
  
//   if (p1.first == -1 || p1.second == -1) {
//     return true;
//   }

//   for (int i=rep; i<8 && !resolucionPosible; ++i) {
//     for (int j=0; j<4 && !resolucionPosible; ++j) {
//       if (posible (tab, pieza[i][j], p1) ){
// 	copiaMatriz = tab;
// 	colocar(tab, pieza[i][j], p1);
// 	cout << tab << endl;
// 	resolucionPosible = resolver(pieza, tab, ++rep);
//      	if(!resolucionPosible)
// 	  tab= copiaMatriz;
//       }

//     }
//   }

//   return resolucionPosible;
// }



//Voy a empezar resolver desde el principio, utilizando una cosa  cutrecilla

bool resolver (const int& pieza[8][4][5][5] , Matriz &tab, set<int> unusedNumbers){
  //si hemos conseguido llenar la matriz hemos ganado
  if (tab.llena())
    return true;

  auto it = unusedNumbers.begin();
  int cutradaParaModificar = *it;
  
  //Iteramos sobre las rotaciones
  for (int i=0; i<4; ++i){

    //con estos dos bucles y el if cogemos todas las casillas libres
    for (int j=0; j<FIL; ++j){
      for (int k=0; k<COL; ++K){
	if (!tab.get(j,k)){ //cuando valga 0

	  if (!cabe(tab, pieza[*it][i]), j, k)
	    continue;

	  colocar (tab, pieza[cutradaParaModificar][j], j, k);
	  unusedNumbers.erase(cutradaParaModificar);

	  bool resuelto = resolver(pieza, tab, unusedNumbers);

	  if(resuelto)
	    return true;
	  else
	    unusedNumber.insert(cutradaParaModificar);
	}
      }
    }

    return false;
}


int main () {
  Matriz tab;
  resolver(pieza, tab, 0);
  cout << tab;
}
