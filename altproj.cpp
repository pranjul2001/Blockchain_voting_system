#include "altproj.hpp"

/*
Board cube2mat(const cube& Q){
  int n = Q.n_rows;
  Board board(n,n);
  uvec ix;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++){
      //      board(n,n) = (int)find(Q.tube(i,j) > 0, "last");
      ix = find(Q.tube(i,j) > 0);
      board(i,j) = ix(0) + 1;
    }
  return board;
}
*/
// RC1
cube RC1(const cube& Q){

  int n = Q.n_rows;
  cube P(n,n,n,fill::zeros);
  uvec seq = linspace<uvec>(0,n-1,n), ix(n), order(n);
  for(int i = 0; i < n; i++)
    for(int k = 0; k < n; k++){
      ix = k*n*n + n*seq + i;
      order = sort_index(Q.elem(ix), "descend");
      P(i,order(0),k) = 1;
    }
  return 2*P - Q;
}

// RC2
cube RC2(const cube& Q){
  int n = Q.n_rows;
  cube P(n,n,n,fill::zeros);
  uvec seq = linspace<uvec>(0,n-1,n), ix(n), order(n);
  for(int j = 0; j < n; j++)
    for(int k = 0; k < n; k++){
      ix = k*n*n + j*n + seq;
      order = sort_index(Q.elem(ix), "descend");
      P(order(0),j,k) = 1;
    }
  return 2*P - Q;
}


// RC3
cube RC3(const cube& Q){
  int n = Q.n_rows;
  cube P(n,n,n,fill::zeros);
  // a handy tool for indexing later on
  int blockSize = sqrt(n);
  uvec mask(blockSize*blockSize);
  uvec ix(blockSize*blockSize), order;
  for(int i = 0; i < blockSize; i++)
    for(int j = 0; j < blockSize; j++)
      mask(i+blockSize*j) = i + n*j;
  
  // now do the projection
  for(int k = 0; k < n; k++)
    for(int i = 0; i < blockSize; i++)
      for(int j = 0; j < blockSize; j++){
        ix = mask + (i*blockSize + j*n*blockSize);
        order = sort_index(Q.elem(ix+k*n*n), "descend");
        P(ix(order(0)) + k*n*n) = 1;
      }
  return 2*P - Q;
}

// RC4
cube RC4(const cube& Q){
  int n = Q.n_rows;
  cube P(n,n,n,fill::zeros);
  uvec seq = linspace<uvec>(0,n-1,n), ix(n), order(n);
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++){
      ix = seq*n*n + j*n + i;
      order = sort_index(Q.elem(ix), "descend");
      P(i,j,order(0)) = 1;
    }
  return 2*P - Q;
}

// RC5
/*
cube RC5(const cube&Q, const Board& board){
  int n = Q.n_rows;
  cube P = Q;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(board(i,j) != 0)
        P(i,j,board(i,j)-1) = 1;
  return 2*P - Q;

}
*/

Board DR(const Board& board){
  Board matt = board;
  return matt;
}