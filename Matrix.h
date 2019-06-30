#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
using namespace std;

class Matrix{
private:
  int dim;
  vector<vector<int> > mat;
  int moves;
public:
  Matrix(int);

  void setValue(int, int, int);
  void printMatrix();
  bool checkSolvability(vector<int> listOfPieces);
  void setUp();
  void movePiece();
  bool win();
};

#endif // MATRIX_H
