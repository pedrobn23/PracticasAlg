#include <iostream>
#include <vector>


class Matrix {
private:
  const int Tam = 9;
  vector < vector <int>> m (9);

public:
  Matrix () {
    for (int i=0; i<9; ++i) {
      m.resize (9);
      for (int j=0; j < 9; ++j) {
	m[i][j] = -1;
      }
    }
  }


  
}



  class Sudoku {
  private:
    Matrix m;

    inline pair<int,int> cuadra (int fil, int col) {
      return pair<int,int> p (fil-(fil%9), col-(col%9)); 
    } 

  public:
    
    //hecho un poco a lo fuerzabruta, nos compruba si colocar una ficha es posible
    bool posible (const int& fil, const int& col, const int& num) {
      //comprobar que esté vacía
      if (m[fil][col] != -1) {
	return false;
      }


      //comprobar fila y colmuna
      for (int i=0; i<9; ++i) {
	//fila
	if (m[i][col] == num) {
	  return false;
	}
      
	//columna
	if (m[fil][i] == num) {
	  return false;
	}
      }

   
      //comprobar cuadrado
      pair <int,int> pos = cuadra(fil,col)
	for (int i=0; i<3; ++i) {
	  for (int j=0; j<3; ++j) {
	    if(m[pos.first+i][pos.second+j])
	      return false;
	  }
	}

      return true;
    }

    //Esta función nos devuelve el primer termino libre
    pair <int,int> primeraLibre () {
      for (int i=0; i<9; ++i) {
	for (int j=0; j<9; ++j) {
	  if (m[i][j] == -1)
	    return pair <int,int> p(i,j);
	}
      }

      return pair <int,int> p(-1,-1)
    }


    bool resuelve (Matriz &sol){
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
	    sol[p1.first][p2.second] = i
	    ret = resuelve(sol);
	}
	i++;
      }

      return ret;
    }
    
    
  }
    
