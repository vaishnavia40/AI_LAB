#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;
int board[9]={2,2,2,2,2,2,2,2,2};
int ai=5;
int human=3;

void show_board() {
    cout << "----------------------------" << endl;
    cout << "|    " << board[0] << "   |    " << board[1] << "   |    " << board[2] << "   |" << endl;
    cout << "----------------------------" << endl;
    cout << "|    " << board[3] << "   |    " << board[4] << "   |    " << board[5] << "   |" << endl;
    cout << "----------------------------" << endl;
    cout << "|    " << board[6] << "   |    " << board[7] << "   |    " << board[8] << "   |" << endl;
    cout << "----------------------------" << endl;
}
int check_winner(){
    for(int i=0;i<9;i+=3){
        if(board[i]==board[i+1]&&board[i+1]==board[i+2]&& board[i]!=2){
            return board[i];
        }
    }
    for(int i=0;i<3;i++){
        if(board[i]==board[i+3]&&board[i+3]==board[i+6]&& board[i]!=2){
            return board[i];
        }
    }
    if(board[0]==board[4]&&board[4]==board[8]&&board[0]!=2){
        return board[0];
    }
    if(board[2]==board[4]&&board[4]==board[6]&&board[2]!=2){
        return board[0];
    }

    for(int i=0;i<9;i++){
        if(board[i]==2){
            return -1;
        }
    }
    return 0;
}
int minimax(int player){
    int result=check_winner();
    //bases cases
    if(result==ai){
        return 1;
    }if(result==human){
        return -1;
    }if(result==0){
        return 0;
    }

    int bestScore=(player==ai)?INT_MIN:INT_MAX;
    for(int i=0;i<9;i++){
        if(board[i]==2){
            board[i]=player;
            int score=minimax((player==ai)?human:ai);
            board[i]=2;

            if(player==ai){
                bestScore=max(score,bestScore);
            }if(player==human){
                bestScore=min(score,bestScore);
            }
        }
    }
    return bestScore;
}
void aiMove(){
    //maximizer
    int bestScore=INT_MIN;
    int bestMove=-1;

    for(int i=0;i<9;i++){
        if(board[i]==2){
            board[i]=ai;
            int score=minimax(human);
            board[i]=2;

            if(score > bestScore){
            bestScore=score;
            bestMove=i;
        }
        }  
    }
    board[bestMove]=ai;
}
void humanMove(){
 int move;
 cin>>move;
 move--;
 while(move<0|| move>=9 || board[move]==3||board[move]==5){
    cout<<"INvalid move try again please: \n";
    cin>>move;
    move--;
 }
 board[move]=human;
}
int main(){
    int turn=0;
    while(true){
        show_board();
        int winner=check_winner();
        if(winner!=-1){
            if(winner==ai){
                cout<<"AI IS WINNER\n";
            }else if(winner==human){
                cout<<"HUMAN IS WINNER\n";
            }else if(winner==0){
                cout<<"IT IS DRAW";
            }
            break;
        } else{
            if(turn==0){
            aiMove();
            turn=1;
        }else{
            humanMove();
            turn=0;
        } 
        }    
    }

    return 0;
}