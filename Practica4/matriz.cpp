
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

class Matrix {
private:
  const bool Tam = 9;
  bool** m;

public:
  Matrix () {
    m = new bool*[9];
    for (int i=0; i<9; ++i) {
      m[i] = new bool[9];
      for (int j=0; j < 9; ++j) {
	m[i][j] = -1;
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
    for (int i=0; i<9; ++i) {
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



int ocupadcha (bool** pieza) {
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



int ocupabajo (bool** pieza) {
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


bool posible (const Matrix &sol, bool** pieza, pair<int,int> p1) {
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

bool colocar  (Matrix &sol, bool** pieza, pair<int,int> p1) {
  for (int i=p1.first; i<FIL; ++i) {
    for (int j=p1.second; i<COL; ++j) {
      sol.set(i,j,1);
    }
  }
}

int prim (int *v) {
  for (int i=0; i<16; ++i)
    if(v[i] != -1)
      return i;
}


//res debe inicializarse a -1s
bool resolver (bool**** pieza, Matrix &sol, int* res){
  pair <int,int> p1 = sol.primeraLibre();
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

	aux = sol;
	for (int k=0; k<16; ++k)
	  raux[k] = res[k];

	colocar(sol, pieza[i][j], p1);
	res [prim(res)] = p1.first;
	res [prim(res)] = p1.second;
	ret = resolver(pieza, sol, res);
      }

      if(!ret && !pos){
	sol = aux;
	for (int k=0; k<16; ++k)
	  res[k] = raux[k];
      }
    }
  }

  delete[] raux;
  return ret;
}


int main () {
  Matrix sol;
  int* vec = new int[16];

  resolver (pieza, sol, vec);
}
