#include <iostream>
#include <utility>
#include "board.h"
#include <vector>
using namespace std;
void print(Board);

int main(){
	Board B;
	B.opponentMove("P 0 0");
	B.opponentMove("P 1 0");
	B.opponentMove("P 2 0");
	B.opponentMove("P 3 0");
	B.opponentMove("P 4 0");
	for(int i = 0; i<11; i++){
		for(int j = 0; j<11; j++){
			cout<< B.myBoard[i][j]<<" ";
		}
		cout<<endl;
	}
	for(int i = 0; i<B.ringPosOpp.size(); i++){
		cout<<B.ringPosOpp[i].first<<" "<<B.ringPosOpp[i].second<<"; ";
	}
	cout<<endl;
	B.opponentMove("S 0 0 M 1 1");
	B.opponentMove("S 1 0 M 2 1");
	B.opponentMove("S 2 0 M 3 5");
	B.opponentMove("S 3 0 M 4 7");
	B.opponentMove("S 4 0 M 5 9");
	for(int i = 0; i<11; i++){
		for(int j = 0; j<11; j++){
			cout<< B.myBoard[i][j]<<" ";
		}
		cout<<endl;
	}
	for(int i = 0; i<B.markerPosOpp.size(); i++){
		cout<<B.markerPosOpp[i].first<<" "<<B.markerPosOpp[i].second<<"; ";
	}
	cout<<endl;for(int i = 0; i<B.ringPosOpp.size(); i++){
		cout<<B.ringPosOpp[i].first<<" "<<B.ringPosOpp[i].second<<"; ";
	}
	cout<<endl;
	for(int i = 0; i<B.markerPos.size(); i++){
		cout<<B.markerPos[i].first<<" "<<B.markerPos[i].second<<"; ";
	}
	cout<<endl;
	B.opponentMove("RS 0 0 RE 4 0 X 1 1");
	for(int i = 0; i<11; i++){
		for(int j = 0; j<11; j++){
			cout<< B.myBoard[i][j]<<" ";
		}
		cout<<endl;
	}


	print(B);
	B.initialMove();
	print(B);
	B.myMove();
	return 0;
}
void print(Board B){
	for(int i = 0; i<11; i++){
		for(int j = 0; j<11; j++){
			cout<< B.myBoard[i][j]<<" ";
		}
		cout<<endl;
	}
}
