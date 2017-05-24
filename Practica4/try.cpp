#include <utility>
#include <string>
#include <tuple>
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include "piezamod.h"

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


  
  pair <int,int> primeraLibre () {
    for (int i=0; i<FIL; ++i) {
      for (int j=0; j<COL; ++j) {
	if (!m[i][j])
	  return pair <int,int> (i,j);
      }
    }

    return  pair<int,int> (-1,-1);
  }

  
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


bool posible (const Matriz &tab, int pieza[5][5], pair<int,int> p1) {
  int derecha = ocupadcha(pieza),abajo = ocupabajo(pieza);
  
  if ((FIL - p1.first <= derecha)|| (COL-p1.second <= abajo))
    return false;

  
  for (int i=0,k=p1.second; i<derecha && k<COL; ++i, ++k) {
    for (int j=0,  h=p1.first;j<abajo && h<FIL; ++j, ++h) {
      if (pieza[j][i] && tab.get(h,k)) {
	cout << "No posible aqui" << endl;
	return false;
      }
    }
  }
  cout << "Posible aqui" << endl;
  return true;
}

bool colocar  (Matriz &sol, int pieza[5][5], pair<int,int> p1) {
  assert(posible(sol, pieza, p1));
  for (int i=0,k=p1.second; i<ocupadcha(pieza) && k<COL; ++i, ++k) {
    for (int j=0,  h=p1.first;j<ocupabajo(pieza) && h<FIL; ++j, ++h) {
      sol.set(h, k, pieza[j][i]);
    }
  }
}



//Esta funcion resuelve el problema por backtrack, hay que pasarle el vector de
//piezas a usar y la matriz donde se almacena la solucion
bool resolver (int pieza[8][4][5][5] , Matriz &tab, int rep){
  pair <int,int> p1 = tab.primeraLibre();
  bool resolucionPosible = false, pos=false;
  Matriz copiaMatriz;


  
  if (p1.first == -1 || p1.second == -1) {
    return true;
  }

  cout << "Llamada recursiva con primera libre:"<< p1.first << p1.second << endl;
  for (int i=rep; i<8 && !resolucionPosible; ++i) {
    for (int j=0; j<4 && !resolucionPosible; ++j) {
      if (posible (tab, pieza[i][j], p1) ){
	cout << "Pieza " << i+1 << " Rotacion" << j +1 <<endl;

	copiaMatriz = tab;

	colocar(tab, pieza[i][j], p1);
		cout << tab << endl;
	resolucionPosible = resolver(pieza, tab, ++rep);
     	if(!resolucionPosible)
	  tab= copiaMatriz;
      }

      char c;
      cout << "Cambio de rotación:\n" << tab <<  endl;
    }
    cout << "Paso de pieza \n"<< endl;
  }

  return resolucionPosible;
}

int main () {
  Matriz tab;
  resolver(pieza, tab, 0);
  cout << tab;
}
