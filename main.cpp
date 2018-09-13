#include <iostream>
#include <utility>
#include "board.h"
#include <vector>
using namespace std;

int main(){
	Board B;
	B.opponentMove("P 0 0");
	B.opponentMove("P 1 0");
	B.opponentMove("P 2 0");
	B.opponentMove("P 3 0");
	B.opponentMove("P 4 0");
	B.opponentMove("S 0 0 M 1 1");
	B.opponentMove("S 1 0 M 2 1");
	B.opponentMove("S 2 0 M 3 5");
	B.opponentMove("S 3 0 M 4 7");
	B.opponentMove("S 4 0 M 5 9");
	B.opponentMove("RS 0 0 RE 4 0 X 1 1");
	for(int i = 0; i<11; i++){
		for(int j = 0; j<11; j++){
			cout<< B.myBoard[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
