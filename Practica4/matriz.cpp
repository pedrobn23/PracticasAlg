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

/**
 *@class Matrix
 *@brief Clase que empaqueta el tablero que se usará para colocar las piezas
 */

class Matrix {
private:
  int** m;

public:
  //constructor por defecto, inicializa la matriz a 0
  Matrix () {
    m = new int*[FIL];
    for (int i=0; i<FIL; ++i) {
      m[i] = new int[COL];
      for (int j=0; j < COL; ++j) {
	m[i][j] = 0;
      }
    }
  }

  //devuelve la posicion i,j
  inline int get (int i, int j) const {
    assert (i<FIL && j<COL);
	      
    return m[i][j];
  }

  //establece la posicion
  inline void set (int i, int j, int value) {
    if (i>=FIL)
      cout << "Pazo cenutrio, i vale: " << i << endl;
    
    if (j>=COL)
      cout << "Pazo cenutrio, j vale: " << j << endl;
    
    assert (i<FIL);
    assert (j<COL);
    assert (value >= 0);
    
    m[i][j] = value;
  }



  // friend std::istream& operator>>(std::istream& is, Matrix& m) {
  //   char basura;
  //   int value;
  //   for (int i=0; i<FIL; ++i) {
  //     for (int j=0; j<COL; ++i) {
  // 	is >> value >> basura;
  // 	m.set(i,j,value);
  //     }
  //     is >> basura;
  //   }
  // }

  //Sobrecarga del operador de escritura
  friend std::ostream& operator<<(std::ostream& os, Matrix& e) {

    int value;
    os << "\nImpresion del tablero:\n";
    for (int i=0; i<FIL; ++i) {
      for (int j=0; j<COL; ++j) {
  	//esto es una gitanada pero tenemos muchas cosas que hacer y poco tiempo
  	value=e.get(i,j);
  	os <<  value << ' ';
      }
      os << '\n';
    }
  }

  //Destructor de la matriz, es necesario por usar memoria dinamica
  ~Matrix () {
    for (int i=0; i<FIL; ++i) {
      delete[] m[i];
    }

    delete[] m;
  }


  //Esta función nos devuelve el primer termino libre (es decir, la primera posicion que valga 0)
  pair <int,int> primeraLibre () {
    for (int i=0; i<FIL; ++i) {
      for (int j=0; j<COL; ++j) {
	if (!m[i][j])
	  return pair <int,int> (i,j);
      }
    }

    return  pair<int,int> (-1,-1);
  }

  Matrix& operator=(const Matrix &m) {
    for (int i=0; i<FIL; ++i)
      for (int j=0; j<COL; ++j)
	this->set(i,j,m.get(i,j));
  }
};


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


bool posible (const Matrix &tab, int pieza[5][5], pair<int,int> p1) {
  if (FIL - p1.first <= ocupadcha(pieza))
    return false;

  if (COL - p1.second <= ocupabajo(pieza))
    return false;

  
  for (int i=0,k=p1.second; i<ocupadcha(pieza) && k<COL; ++i, ++k) {
    for (int j=0,  h=p1.first;j<ocupabajo(pieza) && h<FIL; ++j, ++h) {
      if (pieza[j][i] && tab.get(h,k)) {
	return false;
      }
    }
  }

  return true;
}

bool colocar  (Matrix &sol, int pieza[5][5], pair<int,int> p1) {
  assert(posible(sol, pieza, p1));
  for (int i=0,k=p1.second; i<ocupadcha(pieza) && k<COL; ++i, ++k) {
    for (int j=0,  h=p1.first;j<ocupabajo(pieza) && h<FIL; ++j, ++h) {
      sol.set(h, k, pieza[j][i]);
    }
  }
}



//Esta funcion resuelve el problema por backtrack, hay que pasarle el vector de
//piezas a usar y la matriz donde se almacena la solucion
bool resolver (int pieza[8][4][5][5] , Matrix &tab, int rep){
  pair <int,int> p1 = tab.primeraLibre();
  bool resolucionPosible = false, pos=false;
  Matrix copiaMatriz;


      char c;
      cout << "\n\ncout del inicio de resolver:\n" << tab <<  endl;

  
  if (p1.first == -1 || p1.second == -1) {
    return true;
  }

  cout << "viá recorré" << endl;
  for (int i=rep; i<8 && !resolucionPosible; ++i) {
    for (int j=0; j<4 && !resolucionPosible; ++j) {
      if (posible (tab, pieza[i][j], p1) ){
	cout << "Iteracion" << i << endl;
	copiaMatriz = tab;

	colocar(tab, pieza[i][j], p1);
	resolucionPosible = resolver(pieza, tab, ++rep);
     	if(!resolucionPosible)
	  tab= copiaMatriz;
      }

      char c;
      cout << "\ncout de dentro de resolver: " << tab <<  endl;
    }
  }

  return resolucionPosible;
}

int main () {
  Matrix tab;
  resolver(pieza, tab, 0);
}
