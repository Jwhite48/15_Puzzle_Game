#include "helper.h"
#include "Matrix.h"

#include <iostream>
#include <string>
using namespace std;

int main(){
  srand(time(NULL));

  cout << "Enter 3,4, or 5 to make a 3X3,4X4, or 5X5 board: ";
  string line; getline(cin, line);

  int choice = -1;
  do{
    while(!isDigits(line)||line.empty()){
      cout << "-------------\nMUST CONTAIN ONLY NUMBERS\n-------------" << endl;
      cout << "Enter 3,4, or 5 to make a 3X3,4X4, or 5X5 board: ";
      getline(cin, line);
    }
    choice = stoi(line);
    if(choice<3||choice>5){
      cout << "-------------\nMUST BE A 3,4, or 5\n-------------" << endl;
      cout << "Enter 3,4, or 5 to make a 3X3,4X4, or 5X5 board: ";
      getline(cin, line);
    }
  }while(choice<3||choice>5);

  Matrix board = Matrix(choice);
  board.setUp();

  while(!board.win()){
    board.printMatrix();
    board.movePiece();
  }
}
