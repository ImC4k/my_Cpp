#include <iostream>

using namespace std;

// CONSTANTS
const int BOARD_SIZE = 9;
const int SIZE = 3;

const int board[BOARD_SIZE][BOARD_SIZE] = {{5,3,0,0,7,0,0,0,0},
                                      {6,0,0,1,9,5,0,0,0},
                                      {0,9,8,0,0,0,0,6,0},
                                      {8,0,0,0,6,0,0,0,3},
                                      {4,0,0,8,0,3,0,0,1},
                                      {7,0,0,0,2,0,0,0,6},
                                      {0,6,0,0,0,0,2,8,0},
                                      {0,0,0,4,1,9,0,0,5},
                                      {0,0,0,0,8,0,0,7,9}};

const int task1_board[BOARD_SIZE][BOARD_SIZE] = {{1,4,3,6,2,8,5,7,9},
                                    {5,7,2,1,3,9,4,6,8},
                                    {9,8,6,7,5,4,2,3,1},
                                    {3,9,1,5,4,2,7,8,6},
                                    {4,6,8,9,1,7,3,5,2},
                                    {7,2,5,8,6,3,9,1,4},
                                    {2,3,7,4,8,1,6,9,5},
                                    {6,1,9,2,7,5,8,4,3},
                                    {8,5,4,3,9,6,1,2,7}};

const int debug_board[BOARD_SIZE][BOARD_SIZE] = {{5,3,4,6,7,8,9,1,2},
                                    {6,7,2,1,9,5,3,4,8},
                                    {1,9,8,3,9,0,0,6,0},
                                    {8,0,0,0,6,0,0,0,3},
                                    {4,0,0,8,0,3,0,0,1},
                                    {7,0,0,0,2,0,0,0,6},
                                    {0,6,0,0,0,0,2,8,0},
                                    {0,0,0,4,1,9,0,0,5},
                                    {0,0,0,0,8,0,0,7,9}};


const int simpler_board[SIZE][SIZE] = { {1,0,2},
                                  {0,4,0},
                                  {7,0,0}
                                };

// // API
// // for checking
// bool check_single_region(int[][BOARD_SIZE], int, int);
// bool check_every_region(int[][BOARD_SIZE]);
// bool check_single_row(int[][BOARD_SIZE], int, int);
// bool check_every_row(int[][BOARD_SIZE]);
// bool check_single_column(int[][BOARD_SIZE], int, int);
// bool check_every_column(int[][BOARD_SIZE]);
// bool check_element_condition(int[][BOARD_SIZE], int, int);
// bool check_solution(int[][BOARD_SIZE]);
// // for solving
// bool solve(int[][BOARD_SIZE], int, int);
// bool solve_sudoku(int[][BOARD_SIZE]);
// // for debugging
// void print_board(int[][BOARD_SIZE]);
// // for converting string to array board
// void fill_board(int[][BOARD_SIZE], char[]);




// FUNCTIONS
bool check_single_region(const int board[][BOARD_SIZE], int i, int j){// (i, j) are target location, (scanI, scanJ) are search start location
  // target = board[i][j];
  int scanI, scanJ;

  if(i<3) scanI = 0;
  else if(i<6) scanI = 3;
  else scanI = 6;

  if(j<3) scanJ = 0;
  else if(j<6) scanJ = 3;
  else scanJ = 6;

  for(int m = scanI; m < scanI+3; m++){
    for(int n = scanJ; n < scanJ+3; n++){
      if(m==i && n==j){
        continue;
      }
      if(board[m][n] == board[i][j]){
        // debug
        // cout<<"region check"<<endl;
        // cout<<"i = "<<i<<" j = "<<j<<" m = "<<m<<" n = "<<n<<endl;
        // cout<<"board[m][n] = "<<board[m][n]<<" board[i][j] = "<<board[i][j]<<endl;
        // debug end
        return false;
      }
    }
  }
  return true;
}

bool check_every_region(const int board[][BOARD_SIZE]){
  // i += 3; j += 3; <-inside for-loop, consider 3x3 grids' coor.
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j = 0; j < BOARD_SIZE; j++){
      if(!(check_single_region(board, i, j))){
        return false;
      }
    }
  }
  return true;
}

// check row functions
bool check_single_row(const int board[][BOARD_SIZE], int i, int j){ // this can be used in task 2 too
  // target = board[i][j];
  for(int k = 0; k<BOARD_SIZE; k++){ // check row index, actually can skip check previous items
    if(k==j){
      continue;
    }
    if(board[i][k] == board[i][j]){
      // debug
      // cout<<"row check"<<endl;
      // cout<<"i = "<<i<<" k = "<<k<<" j = "<<j<<endl;
      // cout<<"board[i][k] = "<<board[i][k]<<" board[i][j] = "<<board[i][j]<<endl;
      // debug end
      return false;
    }
  }
  return true;
}

bool check_every_row(const int board[][BOARD_SIZE]){
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j = 0; j < BOARD_SIZE; j++){
      if(!check_single_row(board, i, j)){ // if false, then return false
        return false;
      }
    }
  }
  return true;
}

// check column functions
bool check_single_column(const int board[][BOARD_SIZE], int i, int j){ // this can be used in task 2 too
  // target = board[i][j];
  for(int k = 0; k<BOARD_SIZE; k++){ // check column index, actually can skip checking previous items
    if(k==i){
      continue;
    }
    if(board[k][j] == board[i][j]){
      // debug
      // cout<<"column check"<<endl;
      // cout<<"k = "<<k<<" j = "<<j<<" i = "<<i<<endl;
      // cout<<"board[k][j] = "<<board[k][j]<<" board[i][j] = "<<board[i][j]<<endl;
      // debug end
      return false;
    }
  }
  return true;
}

bool check_every_column(const int board[][BOARD_SIZE]){
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j = 0; j < BOARD_SIZE; j++){
      if(!check_single_row(board, i, j)){ // if false, then return false
        return false;
      }
    }
  }
  return true;
}

// for task 2, check region, row, column for single element
bool check_element_condition(const int board[][BOARD_SIZE], int i, int j){
  return check_single_region(board, i, j) && check_single_row(board, i, j) && check_single_column(board, i, j);
}


// Skeleton code
// Task 1
bool check_solution(int board[][BOARD_SIZE]){
  // TODO done
  return check_every_region(board) && check_every_row(board) && check_every_column(board);
}

// Task 2
bool solve(int board[][BOARD_SIZE], int i, int j){
  // TODO
  // debug
  // cout<<"i = "<<i<<", j = "<<j<<endl;
  // debug end

  int temp = i*BOARD_SIZE+j;
  i = temp/BOARD_SIZE;
  j = temp%BOARD_SIZE;

  // if(j>=9){
  //   i += 1;
  //   j = 0;
  // }

  // debug
  //  cout<<"\t\t\ttemp = "<<temp<<", i = "<<i<<", j = "<<j<<", board[i][j] = "<<board[i][j]<<endl;
  // cout<<"i = "<<i<<", j = "<<j<<endl;
  // debug end
  // cout<<"Reached here"<<endl;
  if(i >= BOARD_SIZE-1 && j >= BOARD_SIZE-1){ // reaching bottom most (base case)
    if(board[i][j] != 0){
      return true;
    }
    else{
      int k = 1;
      while(true){

        if(k > 9){
          board[i][j] = 0;
          return false;
        }
        board[i][j] = k;
        // bool bool_check_element = check_element_condition(board, i, j);
        // debug
        // cout<<"\n\n\n\n\n\n\n";
        // void print_board(int[][BOARD_SIZE]);
        // print_board(board);
        // cout<<"i = "<<i<<", j = "<<j<<endl;
        //debug end

        // attempt newest
        if(check_element_condition(board, i, j)){
          return true;
        }
        else{
          k++;
          continue;
        }

        // old attempt
        // if(k > 9){
        //   board[i][j] = 0;
        //   return false;
        // }
        // if(k <= 9 && !check_element_condition(board, i, j)){
        //   k++;
        //   continue;
        // }
        // if(check_element_condition(board, i, j)){
        //   return true;
        // }

      }
    }
  }


  else if(board[i][j] !=0){ // if already solved, then just give the answer of next element
    return solve(board, i, j+1);
  }

  else{
    int k = 1; // start the attempt by putting 1 through 9 to the 0 element

    while(true){ // if attempt doesn't work, this loop updates k and retry, until k > 9
      if(k > 9){
        board[i][j] = 0;
        return false;
      }
      board[i][j] = k; // attempt: put k into the element and start to test
      // bool bool_check_element = check_element_condition(board, i, j); // check if the attempt element fits the board
      // bool bool_check_next_element = solve(board, i, j+1); // check if used "this" element, whether next element is possible

      // if(k > 9){ // if attempt is pass 9, then this element fails, then tell previous call that its' unsuccessful
      //   board[i][j] = 0;
      //   return false;
      // }

      // debug
      // cout<<"\n\n\n\n\n\n\n";
      // void print_board(int[][BOARD_SIZE]);
      // print_board(board);
      // cout<<"i = "<<i<<", j = "<<j<<endl;
      // debug end

      // newest attempt
      /*I think this if statement can be removed */
      /*because if k=9 and condition wrong, below if statement will return false*/
      if(check_element_condition(board, i, j)){
        if(solve(board, i, j)){
          return true;
        }
        // else{
        //   k++;
        //   continue;
        // }
      }
      // else{
      //   k++;
      //   continue;
      // }
      k++;
      continue;

      // original attempt
      // if(k > 9){
      // board[i][j] = 0;
      // return false;
      // }
      // if(k==9 && !bool_check_element){
      //   board[i][j] = 0;
      //   return false;
      // }
      // if(k<9 && !bool_check_element){
      //   k++;
      //   continue;
      // }
      //
      // if(bool_check_element && bool_check_next_element){
      //   return true;
      // }
      // /*better not to call two function(it maybe correct) */
      // /*in the same if statement, I think*/
      // /*there maybe some problem in ordering as*/
      // /*don't know which one execute first*/
      // /*if need to use two recursion*/
      // /*this is better:  bool check1 = check_element(...)*/
      // /*bool check 2 = solve(...)*/
      // /*if(check1 && check2)*/
      // //resolved
      //
      // if(bool_check_element && !bool_check_next_element){
      //   // board[i][j] = 0;
      //   // return false;
      //   k++;
      //   continue;
      // }
    }
  }
}

bool solve_sudoku(int board[][BOARD_SIZE]){
    return solve(board, 0, 0);
}

void fill_board(int board[][BOARD_SIZE], const char s[]){
    int len = BOARD_SIZE * BOARD_SIZE;
    for(int i = 0; i < len; ++i)
        board[i / BOARD_SIZE][i % BOARD_SIZE] = (int)(s[i] - '0');
}

void print_board(int board[][BOARD_SIZE]){
    cout << "Sudoku board" << endl;
    for(int i = 0; i < BOARD_SIZE; ++i){
        for(int j = 0; j < BOARD_SIZE; ++j)
            cout << (j ? " " : "") << board[i][j];
        cout << endl;
    }
}

void pause(int dur){
  int temp = time(NULL) + dur;
  while(temp > time(NULL));
}




int main(){
  cout<<"Play sudoku!\n\n\n"<<endl;
  cout<<"Input your board, with \'0\' as empty slots"<<endl;
  char inputBoard[BOARD_SIZE*BOARD_SIZE+1];
   int inputBoardArray[BOARD_SIZE][BOARD_SIZE] ;
  cin.getline(inputBoard, BOARD_SIZE*BOARD_SIZE+1, '\n');
  fill_board(inputBoardArray, inputBoard);
  pause(1); cout<<"Loading ."<<endl; pause(1); cout<<"."<<endl; pause(1); cout<<"."<<endl;pause(1); cout<<"."<<endl;

  print_board(inputBoardArray);
  cout<<"solve it? type yes or no\n\n\n\n"<<endl;
  char permission = 'a';
  cin>>permission;
  if(permission == 'y'){
    if(solve_sudoku(inputBoardArray)){
      cout<<"Solution found!"<<endl;
      print_board(inputBoardArray);
    }
  }
  // bool truth = solve_sudoku(board);
  // print_board(board);
  // cout<<boolalpha<<truth<<endl;
  return 0;
}
