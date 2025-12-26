#include <iostream>
#include <vector>
using namespace std;

bool solvable(vector<vector<int>> &board){
    for(int i = 0;i < 9;i++){
        bool rows[9] = {0};
        bool cols[9] = {0};
        bool boxs[9] = {0};
        for(int j = 0;j < 9;j++){
            if(board[i][j]){
                if(rows[board[i][j] - 1]) return false;
                rows[board[i][j] - 1] = 1;
            }

            if(board[j][i]){
                if(cols[board[j][i] - 1]) return false;
                cols[board[j][i] - 1] = 1;
            }

            if(board[(i/3)*3 + j/3][(i%3)*3+j%3]){
                if(boxs[board[(i/3)*3 + j/3][(i%3)*3+j%3] - 1]) return false;
                boxs[board[(i/3)*3 + j/3][(i%3)*3+j%3] - 1] = 1;
            }
        }                  
    }
    return true;
}

bool Solve(vector<vector<int>> &board){
    if(!solvable(board)) return false;

    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++){
            if(board[i][j] != 0) continue;

            // Find available digits
            bool notAvailable[9] = {0};
            for(int x = 0; x < 9; x++){
                // row
                if(board[i][x] > 0)
                    notAvailable[board[i][x] - 1] = 1;

                // col
                if(board[x][j] > 0)
                    notAvailable[board[x][j] - 1] = 1;

                // box
                if(board[(i/3)*3 + x/3][(j/3)*3 + x%3] > 0)
                    notAvailable[board[(i/3)*3 + x/3][(j/3)*3 + x%3] - 1] = 1;
            }

            for(int x = 0; x < 9; x++){
                if(notAvailable[x]) continue;

                board[i][j] = x+1;
                if(Solve(board)) return true;
                else board[i][j] = 0;

            }

            return false;
        }
    }
    return true;
}


int main(){
    vector<vector<int>> board(9, vector<int>(9,0));
    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++){
            cin >> board[i][j];
        }
    }
    if(!Solve(board)){
        cout << "Cant be solve!" << endl;
    }
    else{
        for(int i = 0;i < 9;i++){
            for(int j = 0;j < 9;j++){
                cout << board[i][j] << ", ";
            }
            cout << endl;
        }
    }

    return 0;
}
