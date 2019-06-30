#include "helper.h"
#include "Matrix.h"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

Matrix::Matrix(int d){
  moves = 0;
  dim=d;
  vector<vector<int> > sub(d, vector<int>(d,0));
  mat = sub;
};

void Matrix::setValue(int y, int x, int val){
  mat[y][x]=val;
};

void Matrix::printMatrix(){
  string o = "\u00af";
  if(dim==4)cout << "________________\n";
  else if(dim==3)cout << "____________\n";
  else if(dim==5)cout << "____________________\n";

  for(int i=0; i<dim; i++){
    for(int j=0; j<dim; j++){
      if(mat[i][j]>=10)cout << "|" << mat[i][j] << "|";
      else if(mat[i][j]==0)cout << "|  |";
      else cout << "| " << mat[i][j] << "|";
    }
    cout << "\n";
  }

  if(dim==4)cout << o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o << endl;
  else if(dim==3)cout << o+o+o+o+o+o+o+o+o+o+o+o << endl;
  else if(dim==5)cout << o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o << endl;
};

bool Matrix::checkSolvability(vector<int> listOfPieces){
  //Determines amount of inverses in the board
  int inverses=0;
  for(int i=0; i<listOfPieces.size()-1; i++){
    for(int j=i+1; j<listOfPieces.size(); j++){
      if(listOfPieces[i] && listOfPieces[j] && listOfPieces[i]>listOfPieces[j]){
        inverses++;
      }
    }
  }

  /*Determines where the empty space is and uses the
    amount of inverses to determine if the board is solveable*/
  if(dim%2==0){
    bool isEven = false;
    if(inverses%2==0)isEven=true;
    int x=0;
    for(int i=0; i<listOfPieces.size(); i++){
      if(listOfPieces[i]==0){
        if(i>=4&&i<8){
          x=1;
        }else if(i<12){
          x=2;
        }else if(i<16){
          x=3;
        }
      }
    }
    if((x==2||x==0)&&!isEven)return true;
    else if((x==3||x==1)&&isEven)return true;
  }else{
    if(inverses%2==0)return true;
  }
  return false;
};

void Matrix::setUp(){
  vector<int> pieceNumbers; int y=0; int x=0;
  for(int i=0; i<(dim*dim); i++) pieceNumbers.push_back(i);
  random_shuffle(pieceNumbers.begin(), pieceNumbers.end(), rng);
  while(!checkSolvability(pieceNumbers)){
    random_shuffle(pieceNumbers.begin(), pieceNumbers.end(), rng);
  }
  while(pieceNumbers.size()!=0){
    setValue(y,x,pieceNumbers[0]);
    if(x!=(dim-1))x++;
    else{
      y++; x=0;
    }
    pieceNumbers.erase(pieceNumbers.begin());
  }
};

void Matrix::movePiece(){
  /*Find where the empty space is and populate
    the possibleMoves vectors with the available moves*/
  int y=0; int x=0; bool flag = false;
  for(int i=0; i<dim; i++){
    for(int j=0; j<dim; j++){
      if(mat[i][j]==0){
        y=i; x=j;
        flag = true; break;
      }
    }
    if(flag)break;
  }
  vector<int> possibleMoves;
  if((y-1)>-1)possibleMoves.push_back(mat[y-1][x]);
  if((y+1)<dim)possibleMoves.push_back(mat[y+1][x]);
  if((x-1)>-1)possibleMoves.push_back(mat[y][x-1]);
  if((x+1)<dim)possibleMoves.push_back(mat[y][x+1]);

  /*Get user's move and makes sure it's valid before
    adding to the moves counter*/
  cout << "Your possible moves are: ";
  for(int i=0; i<possibleMoves.size(); i++)cout << possibleMoves[i] << " ";
  cout << "\nWhat is your move? ";
  string line; getline(cin, line);
  /*Checking to see if there are only digits in the user's move and
    if the user's move is possible*/
  bool validMove = false; int move=-1;
  do{
    while(!isDigits(line)||line.empty()){
      cout << "-------------\nINVALID MOVE\n-------------" << endl;
      printMatrix();
      cout << "Your possible moves are: ";
      for(int i=0; i<possibleMoves.size(); i++)cout << possibleMoves[i] << " ";
      cout << "\nWhat is your move? ";
      getline(cin, line);
    }
    move = stoi(line);
    for(int i=0; i<possibleMoves.size(); i++){
      if(move==possibleMoves[i])validMove=true;
    }
    if(!validMove){
      cout << "-------------\nINVALID MOVE\n-------------" << endl;
      printMatrix();
      cout << "Your possible moves are: ";
      for(int i=0; i<possibleMoves.size(); i++)cout << possibleMoves[i] << " ";
      cout << "\nWhat is your move? ";
      getline(cin, line);
    }
  }while(!validMove);
  moves++;

  /*Logic to determine the movement of the pieces
    based on the user's choice*/
  if(((y-1)>-1)&&(mat[y-1][x]==move)){
    mat[y][x]=move;
    mat[y-1][x]=0;
  }
  if(((y+1)<dim)&&(mat[y+1][x]==move)){
    mat[y][x]=move;
    mat[y+1][x]=0;
  }
  if(((x-1)>-1)&&(mat[y][x-1]==move)){
    mat[y][x]=move;
    mat[y][x-1]=0;
  }
  if(((x+1)<dim)&&(mat[y][x+1]==move)){
    mat[y][x]=move;
    mat[y][x+1]=0;
  }
};

bool Matrix::win(){
  /*Checks to see if the 2d array is in order
    with the empty space in the bottom right*/
  for(int i=0; i<dim; i++){
    for(int j=0; j<dim-1; j++){
      if((mat[i][j]>mat[i][j+1])&&((i!=dim-1)||(j!=dim-2))){
        return false;
      }
    }
    if((i!=dim-1)&&mat[i][dim-1]>mat[i+1][0])return false;
  }
  printMatrix();
  cout << "CONGRATULATIONS! YOU'VE WON! IT TOOK YOU " << moves << " MOVES!" << endl;
  return true;
};
