#include <iostream>
#include <utility>
#include "board.h"
#include <vector>
#include <ctime>
using namespace std;
void print(Board);

int main(int argc, char** argv) {
    Board B;
    int player_id, board_size, time_limit;
    string move,dull,time_rem;
    // Get input from server about game specifications
    cin >> player_id >> board_size >> time_limit;
    time_t current = time(0);
    getline(cin,dull);
    if(player_id == 2) {
        // Get other player's move
        time_t now = time(0);
        time_limit = time_limit-now+current;
        while(true) {
            getline(cin,move);
			B.opponent_player_Move(move,0);
            B.myMove();
            cout<<time_limit<<endl;
            cout<<B.playerMove<<endl;
        }
    }
    else if(player_id == 1) {
        while(true){
            time_t now = time(0);
            time_limit = time_limit-now+current;
			B.myMove();
            cout<<time_limit<<endl;
            cout<<B.playerMove<<endl;
            getline(cin,move);
            B.opponent_player_Move(move,0);
        }
    }
    return 0;
}
