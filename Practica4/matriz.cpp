
#include <vector>
#include <utility>
#include <string>
#include <complex>
#include <tuple>
#include <iostream>


using namespace std;

class Matrix {
private:
  const int Tam = 9;
  int** m;

public:
  Matrix () {
    m = new int*[9];
    for (int i=0; i<9; ++i) {
      m[i] = new int[9];
      for (int j=0; j < 9; ++j) {
	m[i][j] = -1;
      }
    }
  }

  inline int get (int i, int j) {
    return m[i][j];
  }

  inline void set (int i, int j, int value) {
    m[i][j] = value;
  }
  

  friend std::istream& operator>>(std::istream& is, Matrix& m) {
    char basura;
    int value;
    for (int i=0; i<9; ++i) {
      for (int j=0; i<9; ++i) {
	is >> value >> basura;
	m.set(i,j,value);
      }
      is >> basura;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, Matrix& e) {
    int value;
    for (int i=0; i<9; ++i) {
      for (int j=0; i<9; ++i) {
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
};



class Sudoku {
private:
  Matrix m;

  inline pair<int,int> cuadra (int fil, int col) {
    return pair<int,int> (fil-(fil%9), col-(col%9)); 
  } 

public:
    
  //hecho un poco a lo fuerzabruta, nos compruba si colocar una ficha es posible
  bool posible (const int& fil, const int& col, const int& num) {
    //comprobar que esté vacía
    if (m.get(fil, col) != -1) {
      return false;
    }


    //comprobar fila y colmuna
    for (int i=0; i<9; ++i) {
      //fila
      if (m.get(i, col) == num) {
	return false;
      }
      
      //columna
      if (m.get(fil, col) == num) {
	return false;
      }
    }



    
    //comprobar cuadrado
    pair <int,int> pos = cuadra(fil,col) ;
    for (int i=0; i<3; ++i) {
      for (int j=0; j<3; ++j) {
	if(m.get(pos.first+i, pos.second+j))
	  return false;
      }
    }

    return true;
  }

  //Esta función nos devuelve el primer termino libre
  pair <int,int> primeraLibre () {
    for (int i=0; i<9; ++i) {
      for (int j=0; j<9; ++j) {
	if (m.get(i,j) == -1)
	  return pair <int,int> (i,j);
      }
    }

    return  pair<int,int> (-1,-1);
  }


  bool resuelve (Matrix &sol){
    //TODO: Calcular la primera libre de una vez
    pair <int,int> p1 = primeraLibre ();
    bool ret = false;
    int i = 1;

    if (p1.first == -1 || p1.second == -1) {
      return true;
      //TODO: Hacer funcioncilla que compruebe toda la matriz;
    }
      
    while (!ret && i<9) {
      if (posible(p1.first, p1.second, i)) {
	sol.set(p1.first, p1.second, i);
	ret = resuelve(sol);
      }
      i++;
    }

    return ret;
  }
    
    
};
    
int main () {}
