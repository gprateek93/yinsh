#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <sstream>
#include "board.h"
using namespace std;

int oppRing = 1;
int myRing = 2;
int oppMarker = 3;
int myMarker = 4;
int empty = 0;
iPair temp;

int myInt(string s){
	int i;
	istringstream(s)>>i;
	return i;
}

iPair Board :: hex_to_coord(iPair hex){
	iPair coord;
	int x,y;
	int h  = hex.first;
	int p = hex.second;
	if(p<=h){
		x = p;
		y = h;
	}
	else if(p<=2*h){
		x = h;
		y = 2*h-p;
	}
	else if(p<=3*h){
		x = 3*h-p;
		y = 2*h-p;
	}
	else if(p<=4*h){
		x = 3*h-p;
		y = (-1)*h;
	}
	else if(p<=5*h){
		x = (-1)*h;
		y = p-5*h;
	}
	else{
		x = -6*h+p;
		y = -5*h+p;
	}
	coord = make_pair(x,y);
	return coord;
}

iPair Board :: coord_to_hex(iPair coord){
	iPair hex;
	int h,p;
	int x = coord.first;
	int y = coord.second;
	if(x>=0&&y>=0){
		if(x<=y){
			h = y;
			p = x;
		}
		else{
			h = x;
			p = 2*x-y;
		}
	}
	else if(x<=0&&y<=0){
		if(x>=y){
			h = -y;
			p = -x-3*y;
		}
		else{
			h = -x;
			p = y-5*x;
		}
	}
	else if(x>0&&y<0){
		h = x-y;
		p = 2*x-3*y;
	}
	else{
		h = y-x;
		p = 6*y-5*x;
	}
	hex = make_pair(h,p);
	return hex;
}

void Board :: movement(string s,iPair temp, iPair index){

	//horizontal move
	if(temp.first == index.first){
		if(temp.second>index.second){
			for(int i = temp.second-1; i>index.second; i--){
				if(myBoard[temp.first][i]){
					myBoard[temp.first][i] = (s=="M")?oppMarker+myMarker-myBoard[temp.first][i]:empty;
				}
			}
		}
		else if(temp.second<index.second){
			for(int i = temp.second+1; i<index.second; i++){
				if(myBoard[temp.first][i]){
					myBoard[temp.first][i] = (s=="M")?oppMarker+myMarker-myBoard[temp.first][i]:empty;
				}
			}
		}
	}

	//vertical move
	else if(temp.second == index.second){
		if(temp.first>index.first){
			for(int i = temp.first-1; i>index.first; i--){
				if(myBoard[i][temp.second]){
					myBoard[i][temp.second] = (s=="M")?oppMarker+myMarker-myBoard[i][temp.second]:empty;
				}
			}
		}
		else if(temp.first<index.first){
			for(int i = temp.first+1; i<index.first; i++){
				if(myBoard[i][temp.second]){
					myBoard[i][temp.second] = (s=="M")?oppMarker+myMarker-myBoard[i][temp.second]:empty;
				}
			}
		}
	}

	//diagonal move
	else{
		int diff = abs(index.second - temp.second);
		if(temp.first<index.first && temp.second<index.second){
			for(int i = 1; i<diff; i++){
				if(myBoard[temp.first+i][temp.second+i]){
					myBoard[temp.first+i][temp.second+i] = (s=="M")?oppMarker+myMarker-myBoard[temp.first+i][temp.second+i]:empty;
				}
			}
		}
		else if(temp.first>index.first && temp.second>index.second){
			for(int i = 1; i<diff; i++){
				if(myBoard[temp.first-i][temp.second-i]){
					myBoard[temp.first-i][temp.second-i] = (s=="M")?oppMarker+myMarker-myBoard[temp.first-i][temp.second-i]:empty;
				}
			}
		}
	}
}

void Board :: newOppMove(string move, int h, int p){
	iPair hex = make_pair(h,p);
	iPair coord = hex_to_coord(hex);
	iPair index = coord_to_index(coord);

	if(move == "P"){
		myBoard[index.first][index.second] = oppRing;
	}

	else if(move == "S" || move == "RS"){
		temp = index;
	}

	else if(move == "M"){
		movement(move,temp,index);
		myBoard[temp.first][temp.second] = oppMarker;
		myBoard[index.first][index.second] = oppRing;
	}
	else if(move == "RE"){
		movement(move,temp,index);
		myBoard[temp.first][temp.second] = empty;
		myBoard[index.first][index.second] = empty;
	}
	else if(move == "X"){
		myBoard[index.first][index.second] = empty;
	}
}

void Board :: opponentMove(string s){
	vector<string> move;
	char* token = strtok((char*)s.c_str()," ");
	while(token!=NULL){
		string tok(token);
		move.push_back(tok);
		token = strtok(NULL," ");
	}
	int n = move.size();
	string h,p;
	for(int i = 0; i<n; i+=3){
		if(i%3 == 0){
			h = move[i+1];
			p = move[i+2];
			newOppMove(move[i],myInt(h),myInt(p));
		}
	}
}

iPair Board::coord_to_index(iPair coord){
	int x = coord.first +5;
	int y = coord.second +5;
	return make_pair(x,y);
}

iPair Board::index_to_coord(iPair index){
	int x = index.first +5;
	int y = index.second +5;
	return make_pair(x,y);
}
