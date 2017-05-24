
#include <vector>
#include <utility>
#include <string>
#include <complex>
#include <tuple>
#include <iostream>
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
    return m[i][j];
  }

  //establece la posicion
  inline void set (int i, int j, int value) {
    m[i][j] = value;
  }


  
  // friend std::istream& operator>>(std::istream& is, Matrix& m) {
  //   char basura;
  //   int value;
  //   for (int i=0; i<FIL; ++i) {
  //     for (int j=0; i<COL; ++i) {
  // 	is >> value >> basura;
  // 	m.set(i,j,value);
  //     }
  //     is >> basura;
  //   }
  // }

  friend std::ostream& operator<<(std::ostream& os, Matrix& e) {

    int value;
    for (int i=0; i<FIL; ++i) {
      for (int j=0; i<COL; ++i) {
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


  //Esta función nos devuelve el primer termino libre
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



int ocupadcha (int pieza[5][5]) {
  int index = 0, mret = 0;
  for (int j=0; j<5; ++j) {
    for (int i=0; i<5; ++i) {
      if (pieza[i][j])
	index = i+1;
    }
    mret = mret>index ? mret : index;
    index = 0;
  }

  return mret;
}



int ocupabajo (int pieza[5][5]) {
  int index = 0, mret = 0;
  for (int i=0; i<5; ++i) {
    for (int j=0; j<5; ++j) {
      if (pieza[i][j])
	index = j+1;
    }
    mret = mret>index ? mret : index;
    index = 0;
  }

  return mret;
}


bool posible (const Matrix &sol, int pieza[5][5], pair<int,int> p1) {
  if (FIL - p1.first <= ocupadcha(pieza))
    return false;

  if (COL - p1.second <= ocupabajo(pieza))
    return false;

  for (int i=p1.first; i<FIL; ++i) {
    for (int j=p1.second; i<COL; ++j) {
      if (pieza[i-p1.first][j-p1.second] && sol.get(i,j))
	return false;
    }
  }

  return true;
}

bool colocar  (Matrix &sol, int pieza[5][5], pair<int,int> p1) {
  for (int i=0; i<FIL; ++i) {
    for (int j=0; i<COL; ++j) {
      sol.set(i+p1.first, j+p1.second, pieza[i][j]);
    }
  }
}


bool resolver (int pieza[8][4][5][5] , Matrix &tab){
  pair <int,int> p1 = tab.primeraLibre();
  cout << p1.first << " " << p1.second << "\n";
  bool resolucionPosible = false;
  Matrix copiaMatriz;

  if (p1.first == -1 || p1.second == -1) {
    return true;
  }


  for (int i=0; i<8 && !resolucionPosible; ++i) {
    for (int j=0; i<4 && !resolucionPosible; ++j) {
      if (posible (tab, pieza[i][j], p1) ){

			copiaMatriz = tab;

			colocar(tab, pieza[i][j], p1);
			resolucionPosible = resolver(pieza, tab);
     		if(!resolucionPosible)
				tab= copiaMatriz;
      }  
    }
  }

  return resolucionPosible;
}

int main () {
   Matrix tab;
	resolver(pieza,tab);
	cout << tab;
}

/*int main () {
  Matrix tab;
  int* vec = new int[16];

  resolver (pieza, tab, vec);

  for (int i=0; i<16; ++i)
    cout << vec[i] << " ";
  delete[] vec; //Se creaba pero nunca se eliminaba
}*/
 
