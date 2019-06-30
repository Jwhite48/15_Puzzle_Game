#include "helper.h"

//Determines if the user's input contains only digits
bool isDigits(string line){
  for(int i=0; i<line.size(); i++){
    if(!(line[i]>='0'&&line[i]<='9'))return false;
  }
  return true;
}

//RNG needed to shuffle the vector for the board
int rng(int i){
  return rand()%i;
}
