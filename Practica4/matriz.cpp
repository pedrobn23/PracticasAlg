
#include <vector>
#include <utility>
#include <string>
#include <complex>
#include <tuple>
#include <iostream>
#include "pieza.h"

using namespace std;


const int FIL=6;
const int COL=9;

//Esta clase la usaremos para empaquetar el tablero donde hemos de 
class Matrix {
private:
  bool** m;

public:
  Matrix () {
    m = new bool*[FIL];
    for (int i=0; i<FIL; ++i) {
      m[i] = new bool[COL];
      for (int j=0; j < COL; ++j) {
	m[i][j] = 0;
      }
    }
  }

  inline bool get (int i, int j) const {
    return m[i][j];
  }

  inline void set (int i, int j, bool value) {
    m[i][j] = value;
  }


  friend std::istream& operator>>(std::istream& is, Matrix& m) {
    char basura;
    int value;
    for (int i=0; i<FIL; ++i) {
      for (int j=0; i<COL; ++i) {
	is >> value >> basura;
	m.set(i,j,value);
      }
      is >> basura;
    }
  }

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



int ocupadcha (bool pieza[5][5]) {
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



int ocupabajo (bool pieza[5][5]) {
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


bool posible (const Matrix &sol, bool pieza[5][5], pair<int,int> p1) {
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

bool colocar  (Matrix &sol, bool pieza[5][5], pair<int,int> p1) {
  for (int i=0; i<FIL; ++i) {
    for (int j=0; i<COL; ++j) {
      sol.set(i+p1.first, j+p1.second, pieza[i][j]);
    }
  }
}

int primeraPosicionLibre (int *v) {
  for (int i=0; i<16; ++i)
    if(v[i] != -1)
      return i;
}


//res debe inicializarse a -1s
bool resolver (bool pieza[8][4][5][5] , Matrix &sol, int* res){
  pair <int,int> p1 = sol.primeraLibre();
  cout << p1.first << " " << p1.second << "\n";
  bool ret = false;
  Matrix aux;
  int* raux = new int[16];
  bool pos;

  if (p1.first == -1 || p1.second == -1) {
    delete[] raux;
    return true;
  }


  for (int i=0; i<8 && !ret; ++i) {
    for (int j=0; i<4 && !ret; ++j) {
      if (pos = posible (sol, pieza[i][j], p1) ){

	copiaMatriz = sol;
	for (int k=0; k<16; ++k)
	  raux[k] = res[k];

	colocar(sol, pieza[i][j], p1);
	int posicion = primeraPosicionLibre(res);
	res [posicion++] = p1.first;
	res [posicion] = p1.second;
	ret = resolver(pieza, sol, res);
      }

      if(!ret){
	sol = copiaMatriz;
	for (int k=0; k<16; ++k)
	  res[k] = raux[k];
      }
    }
  }

  delete[] raux;
  return ret;
}

int main () {
    ;
}

/*int main () {
  Matrix sol;
  int* vec = new int[16];

  resolver (pieza, sol, vec);

  for (int i=0; i<16; ++i)
    cout << vec[i] << " ";
  delete[] vec; //Se creaba pero nunca se eliminaba
}*/
