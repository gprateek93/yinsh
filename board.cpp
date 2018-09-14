#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "board.h"
using namespace std;

int oppRing = 1;
int myRing = 2;
int oppMarker = 3;
int myMarker = 4;
int empty = 0;
int invalidPos = -1;
iPair temp;

int myInt(string s){
	int i;
	istringstream(s)>>i;
	return i;
}

Board::Board(){
	int i,j,k;
	for(i=0;i<11;i++){
		for(j=0;j<11;j++){
			myBoard[i][j]=-1;
		}
	}
	for(i=0; i<11;i++){
		if(i==0 || i==10){
			for(k=1;k<=4;k++){
				myBoard[i][k+i/2]=0;
			}
			
		}
		else if(i==5){
			for(j=1;j<=9;j++){
				myBoard[i][j]=0;
			}
		}
		else{
			j=(i/5)?i-5:0;
		    k=((i+5)/10)?10:(i+5);
			for(;j<=k;j++){
				myBoard[i][j]=0;
			}
		}
	}
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
void Board :: flipMarker(iPair index,int val){
	if(val == oppMarker){
		markerPosOpp.erase(find(markerPosOpp.begin(),markerPosOpp.end(),index));
		markerPos.push_back(index);
	}
	else{
		markerPos.erase(find(markerPos.begin(),markerPos.end(),index));
		markerPosOpp.push_back(index);
	}
}

void Board :: removeMarker(vector<iPair> &vec, iPair index){
	vec.erase(find(vec.begin(),vec.end(),index));
}

void Board :: moveRing(vector<iPair> &vec,iPair temp, iPair index){
	vec.erase(find(vec.begin(),vec.end(),temp));
	vec.push_back(index);
}

void Board :: movement(string s,iPair temp, iPair index){

	//vertical move
	if(temp.first == index.first){
		if(temp.second>index.second){
			for(int i = temp.second-1; i>index.second; i--){
				if(myBoard[temp.first][i]>0){
					if(s == "M"){
						flipMarker(make_pair(temp.first,i),myBoard[temp.first][i]);
						myBoard[temp.first][i] = oppMarker+myMarker-myBoard[temp.first][i];
					}
					else{
						myBoard[temp.first][i] = empty;
						removeMarker(markerPosOpp,make_pair(temp.first,i));
					}
				}
			}
		}
		else if(temp.second<index.second){
			for(int i = temp.second+1; i<index.second; i++){
				if(myBoard[temp.first][i]>0){
					if(s == "M"){
						flipMarker(make_pair(temp.first,i),myBoard[temp.first][i]);
						myBoard[temp.first][i] = oppMarker+myMarker-myBoard[temp.first][i];
					}
					else{
						myBoard[temp.first][i] = empty;
						removeMarker(markerPosOpp,make_pair(temp.first,i));
					}
				}
			}
		}
	}

	//horizontal move
	else if(temp.second == index.second){
		if(temp.first>index.first){
			for(int i = temp.first-1; i>index.first; i--){
				if(myBoard[i][temp.second]>0){
					if(s == "M"){
						flipMarker(make_pair(i,temp.second),myBoard[i][temp.second]);
						myBoard[i][temp.second] = oppMarker+myMarker-myBoard[i][temp.second];
					}
					else{
						myBoard[i][temp.second] = empty;
						removeMarker(markerPosOpp,make_pair(i,temp.second));
					}
				}
			}
		}
		else if(temp.first<index.first){
			for(int i = temp.first+1; i<index.first; i++){
				if(myBoard[i][temp.second]>0){
					if(s == "M"){
						flipMarker(make_pair(i,temp.second),myBoard[i][temp.second]);
						myBoard[i][temp.second] = oppMarker+myMarker-myBoard[i][temp.second];
					}
					else{
						myBoard[i][temp.second] = empty;
						removeMarker(markerPosOpp,make_pair(i,temp.second));
					}
				}
			}
		}
	}

	//diagonal move
	else{
		int diff = abs(index.second - temp.second);
		if(temp.first<index.first && temp.second<index.second){
			for(int i = 1; i<diff; i++){
				if(myBoard[temp.first+i][temp.second+i]>0){
					if(s == "M"){
						flipMarker(make_pair(temp.first+i,temp.second+i),myBoard[temp.first+i][temp.second+i]);
						myBoard[temp.first+i][temp.second+i] = oppMarker+myMarker-myBoard[temp.first+i][temp.second+i];
					}
					else{
						myBoard[temp.first+i][temp.second+i] = empty;
						removeMarker(markerPosOpp,make_pair(temp.first+i,temp.second+i));
					}
				}
			}
		}
		else if(temp.first>index.first && temp.second>index.second){
			for(int i = 1; i<diff; i++){
				if(myBoard[temp.first-i][temp.second-i]>0){
					if(s == "M"){
						flipMarker(make_pair(temp.first-i,temp.second-i),myBoard[temp.first-i][temp.second-i]);
						myBoard[temp.first-i][temp.second-i] = oppMarker+myMarker-myBoard[temp.first-i][temp.second-i];
					}
					else{
						myBoard[temp.first-i][temp.second-i] = empty;
						removeMarker(markerPosOpp,make_pair(temp.first-i,temp.second-i));
					}
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
		ringPosOpp.push_back(index);
		myBoard[index.first][index.second] = oppRing;
	}

	else if(move == "S" || move == "RS"){
		temp = index;
	}

	else if(move == "M"){
		markerPosOpp.push_back(temp);
		moveRing(ringPosOpp,temp,index);
		movement(move,temp,index);
		myBoard[temp.first][temp.second] = oppMarker;
		myBoard[index.first][index.second] = oppRing;
	}
	else if(move == "RE"){
		movement(move,temp,index);
		removeMarker(markerPosOpp,temp);
		removeMarker(markerPosOpp,index);
		myBoard[temp.first][temp.second] = empty;
		myBoard[index.first][index.second] = empty;
	}
	else if(move == "X"){
		ringPosOpp.erase(find(ringPosOpp.begin(),ringPosOpp.end(),index));
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

void Board:: myMove(){
	int i;
	for(i=0;i<ringPos.size();i++){
		possibleMovements(ringPos[i],i);
	}
    
    // possible moves
	for(i=0;i<5;i++){
		cout<<"[";
		printPair(ringPos[i]);
		cout<<": ";
		for(int j=0;j<possibleMoves[i].size();j++){
			cout<<" ";
			printPair(possibleMoves[i][j]);
		}
		cout<<"]"<<endl;
	}
}
void Board:: printPair(iPair pair){
	cout<<"("<<pair.first-5<<","<<pair.second-5<<")";
}

void Board::initialMove(){
	for(int i=0;i<5;i++){
		int x,y;
		do{
			srand(rand()^time(0));
			x= rand()%5 + 3;
			y= rand()%5 + 3;
		}while(myBoard[x][y]!=0);
		cout<<"P "<<x<<" "<<y<<endl;
		myBoard[x][y]=myRing;
		ringPos.push_back(make_pair(x,y));
	}
}

void Board :: possibleMovements(iPair ring, int ringNo){

	//vertical down move
    int i = ring.first;
    int j;
	for(j = ring.second-1; j>=0;){
		if(myBoard[i][j]==oppRing||myBoard[i][j]==myRing || myBoard[i][j]==invalidPos)
			break;
		else if(myBoard[i][j]==oppMarker||myBoard[i][j]==myMarker){
			for(;j>=0 && (myBoard[i][j]==oppMarker||myBoard[i][j]==myMarker);j--){
				//do nothing
			}
			if(j>=0 && myBoard[i][j]==empty){
				possibleMoves[ringNo].push_back(make_pair(i,j));
			}
			break;
		}
		else if(myBoard[i][j]==empty){
			for(;j>=0 && myBoard[i][j]==empty;j--){
				possibleMoves[ringNo].push_back(make_pair(i,j));
			}
		}				
	}
			
    //verical up move
	for(j = ring.second+1; j<=10;){
		if(myBoard[i][j]==oppRing||myBoard[i][j]==myRing || myBoard[i][j]==invalidPos)
			break;
		else if(myBoard[i][j]==oppMarker||myBoard[i][j]==myMarker){
			for(;j<=10 && (myBoard[i][j]==oppMarker||myBoard[i][j]==myMarker);j++){
				//do nothing
			}
			if(j<=10 && myBoard[i][j]==empty){
				possibleMoves[ringNo].push_back(make_pair(i,j));
			}
			break;
		}
		else if(myBoard[i][j]==empty){
			for(;j<=10 && myBoard[i][j]==empty;j++){
				possibleMoves[ringNo].push_back(make_pair(i,j));
			}
		}				
	}


	//horizontal right move
	j = ring.second;	
	for(i = ring.first+1; i<=10;){
		if(myBoard[i][j]==oppRing||myBoard[i][j]==myRing || myBoard[i][j]==invalidPos)
			break;
		else if(myBoard[i][j]==oppMarker||myBoard[i][j]==myMarker){
			for(;i<=10 && (myBoard[i][j]==oppMarker||myBoard[i][j]==myMarker);i++){
				//do nothing
			}
			if(i<=10 && myBoard[i][j]==empty){
				possibleMoves[ringNo].push_back(make_pair(i,j));
			}
			break;
		}
		else if(myBoard[i][j]==empty){
			for(;i<=10 && myBoard[i][j]==empty;i++){
				possibleMoves[ringNo].push_back(make_pair(i,j));
			}
		}				
	}

	//horizontal left move
	for(i = ring.first-1; i>=0;){
		if(myBoard[i][j]==oppRing||myBoard[i][j]==myRing || myBoard[i][j]==invalidPos)
			break;
		else if(myBoard[i][j]==oppMarker||myBoard[i][j]==myMarker){
			for(;i>=0 && (myBoard[i][j]==oppMarker||myBoard[i][j]==myMarker);i--){
				//do nothing
			}
			if(i>=0 && myBoard[i][j]==empty){
				possibleMoves[ringNo].push_back(make_pair(i,j));
			}
			break;
		}
		else if(myBoard[i][j]==empty){
			for(;i>=0 && myBoard[i][j]==empty;i--){
				possibleMoves[ringNo].push_back(make_pair(i,j));
			}
		}				
	}
		

	//diagonal down move
	i=ring.first+1;
	j=ring.second+1;
    for(; i<=10 && j<=10;){
		if(myBoard[i][j]==oppRing||myBoard[i][j]==myRing || myBoard[i][j]==invalidPos)
			break;
		else if(myBoard[i][j]==oppMarker||myBoard[i][j]==myMarker){
			for(;i<=10 && j<=10 && (myBoard[i][j]==oppMarker||myBoard[i][j]==myMarker);i++,j++){
				//do nothing
			}
			if(i<=10 && j<=10 && myBoard[i][j]==empty){
				possibleMoves[ringNo].push_back(make_pair(i,j));
			}
			break;
		}
		else if(myBoard[i][j]==empty){
			for(;i<=10 && j<=10 && myBoard[i][j]==empty;i++,j++){
				possibleMoves[ringNo].push_back(make_pair(i,j));
			}
		}				
	}


	//diagonal down move
	i=ring.first-1;
	j=ring.second-1;
    for(; i>=0 && j>=0;){
		if(myBoard[i][j]==oppRing||myBoard[i][j]==myRing || myBoard[i][j]==invalidPos)
			break;
		else if(myBoard[i][j]==oppMarker||myBoard[i][j]==myMarker){
			for(;i>=0 && j>=0 && (myBoard[i][j]==oppMarker||myBoard[i][j]==myMarker);i--,j--){
				//do nothing
			}
			if(i>=0 && j>=0 && myBoard[i][j]==empty){
				possibleMoves[ringNo].push_back(make_pair(i,j));
			}
			break;
		}
		else if(myBoard[i][j]==empty){
			for(;i>=0 && j>=0 && myBoard[i][j]==empty;i--,j--){
				possibleMoves[ringNo].push_back(make_pair(i,j));
			}
		}				
	}

}

void reset(bool* flag, int n){
	for(int i=0;i<n;i++){
		flag[i]=true;
	}
}

void Board:: findContinuousMarkers(vector<iPair> &marker, int markerValue){

	int i,j,k,p,q;
	int count = 0;
	bool flag[marker.size()];

	reset(flag,marker.size());
	
	//check horizontally
	for(i=0;i<marker.size();i++){

		if(flag[i]){
			count =1;
			p=marker[i].second;
			for(j=marker[i].first+1;j<=10 && myBoard[j][p]==markerValue;j++){
				flag[find(marker.begin(),marker.end(),make_pair(j,p)) - marker.begin()] = false;				
				count++;
			}

			for(k=marker[i].first-1;k>=0 && myBoard[k][p]==markerValue;k--){
				flag[find(marker.begin(),marker.end(),make_pair(k,p)) - marker.begin()] = false;
				count++;
			}
			//when we have to remove ring
			if(count>=5){
				marker_5.push_back(make_pair(make_pair(k+1,p),make_pair(k+5,p)));
				if(count!=5)
					marker_5.push_back(make_pair(make_pair(j-5,p),make_pair(j-1,p)));
			}
			//4 continuous markers
			else if(count == 4){
				if(j<=10 && myBoard[j][p] == empty){
					marker_4.push_back(make_pair(j,p));
				}
				if(k>=0 && myBoard[k][p] == empty){
					marker_4.push_back(make_pair(k,p));
				}
			}

			//3 continuous markers.....
			flag[i]=false;
		}
	}

	reset(flag,marker.size());
	
	//check Vertically
	for(i=0;i<marker.size();i++){

		if(flag[i]){
			count =1;
			p=marker[i].first;
			for(j=marker[i].second+1;j<=10 && myBoard[p][j]==markerValue;j++){
				flag[find(marker.begin(),marker.end(),make_pair(p,j)) - marker.begin()] = false;				
				count++;
			}

			for(k=marker[i].second-1;k>=0 && myBoard[p][k]==markerValue;k--){
				flag[find(marker.begin(),marker.end(),make_pair(p,k)) - marker.begin()] = false;
				count++;
			}
			//when we have to remove ring
			if(count>=5){
				marker_5.push_back(make_pair(make_pair(p,k+1),make_pair(p,k+5)));
				if(count!=5)
					marker_5.push_back(make_pair(make_pair(p,j-5),make_pair(p,j-1)));
			}
			//4 continuous markers
			else if(count == 4){
				if(j<=10 && myBoard[p][j] == empty){
					marker_4.push_back(make_pair(p,j));
				}
				if(k>=0 && myBoard[p][k] == empty){
					marker_4.push_back(make_pair(p,k));
				}
			}

			//3 continuous markers.....
			flag[i]=false;
		}
	}


	reset(flag,marker.size());
	
	//check diagonally
	for(i=0;i<marker.size();i++){

		if(flag[i]){
			count =1;
			p=marker[i].first+1;
			q=marker[i].second+1;
			for(;p<=10 && q<=10 && myBoard[p][q]==markerValue;p++,q++){
				flag[find(marker.begin(),marker.end(),make_pair(p,q)) - marker.begin()] = false;				
				count++;
			}

			j=marker[i].first-1;
			k=marker[i].second-1;
			for(;j>=0 && k>=0 && myBoard[j][k]==markerValue;j--,k--){
				flag[find(marker.begin(),marker.end(),make_pair(j,k)) - marker.begin()] = false;
				count++;
			}
			//when we have to remove ring
			if(count>=5){
				marker_5.push_back(make_pair(make_pair(j+1,k+1),make_pair(j+5,k+5)));
				if(count!=5)
					marker_5.push_back(make_pair(make_pair(p-5,q-5),make_pair(p-1,q-1)));
			}
			//4 continuous markers
			else if(count == 4){
				if(p<=10 && q<=10 && myBoard[p][q] == empty){
					marker_4.push_back(make_pair(p,q));
				}
				if(j>=0 && k>=0 && myBoard[j][k] == empty){
					marker_4.push_back(make_pair(j,k));
				}
			}

			//3 continuous markers.....
			flag[i]= false;
		}
	}

}