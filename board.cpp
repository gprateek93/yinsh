#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <climits>
#include "board.h"
using namespace std;

int oppRing = 1;
int myRing = 2;
int oppMarker = 3;
int myMarker = 4;
int empty = 0;
int invalidPos = -1;
int initial_counter = 0;
iPair temp;

//Helper Functions

int myInt(string s){
	int i;
	istringstream(s)>>i;
	return i;
}

string myString(int n){
	stringstream ss;
	ss<<n;
	return ss.str();
}

vector<string> tokenize(string s, const char* delimiter){
	vector<string> tokens;
	//trim the starting spaces
	s.erase(0, s.find_first_not_of(" "));

	char* token = strtok((char*)s.c_str(),delimiter);

	while(token!=NULL){
		string tok(token);
		tokens.push_back(tok);
		token = strtok(NULL," ");
	}
	return tokens;
}

//class functions

Board::Board(){
	
	int i,j,k;
	ringRemoved = 0;

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
	coord = make_pair(x+5,y+5);
	return coord;
}

iPair Board :: coord_to_hex(iPair coord){
	iPair hex;
	int h,p;
	int x = coord.first-5;
	int y = coord.second-5;
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
	//cout<<"Here"<<endl;
	vec.push_back(index);
}

void Board :: movement(string s,iPair temp, iPair index, int flag){

	//horizontal move
	vector<iPair> &res = (flag==0)?markerPosOpp:markerPos;
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
						removeMarker(res,make_pair(temp.first,i));
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
						removeMarker(res,make_pair(temp.first,i));
					}
				}
			}
		}
	}

	//vertical move
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
						removeMarker(res,make_pair(i,temp.second));
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
						removeMarker(res,make_pair(i,temp.second));
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
						removeMarker(res,make_pair(temp.first+i,temp.second+i));
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
						removeMarker(res,make_pair(temp.first-i,temp.second-i));
					}
				}
			}
		}
	}
}

void Board :: newOpp_player_Move(string move, int h, int p, int flag){
	iPair hex = make_pair(h,p);
	iPair index = hex_to_coord(hex);
	//iPair index = coord_to_index(coord);

	if(move == "P"){
		if(flag == 0){
			ringPosOpp.push_back(index);
			myBoard[index.first][index.second] = oppRing;
		}
		else{
			ringPos.push_back(index);
			myBoard[index.first][index.second] = myRing;
		}
	}

	else if(move == "S" || move == "RS"){
		temp = index;
	}

	else if(move == "M"){
		if(flag == 0){
			markerPosOpp.push_back(temp);
			moveRing(ringPosOpp,temp,index);
			movement(move,temp,index,flag);
			myBoard[temp.first][temp.second] = oppMarker;
			myBoard[index.first][index.second] = oppRing;
		}
		else{
			//cout<<"Here"<<endl;
			markerPos.push_back(temp);
			//cout<<"Here1"<<endl;
			moveRing(ringPos,temp,index);
			//cout<<"Here1"<<endl;
			movement(move,temp,index,flag);
			myBoard[temp.first][temp.second] = myMarker;
			myBoard[index.first][index.second] = myRing;
		}
	}
	else if(move == "RE"){
		if(flag == 0){
			movement(move,temp,index,flag);
			removeMarker(markerPosOpp,temp);
			removeMarker(markerPosOpp,index);
			myBoard[temp.first][temp.second] = empty;
			myBoard[index.first][index.second] = empty;
		}
		else{
			movement(move,temp,index,flag);
			removeMarker(markerPos,temp);
			removeMarker(markerPos,index);
			myBoard[temp.first][temp.second] = empty;
			myBoard[index.first][index.second] = empty;
		}
	}
	else if(move == "X"){
		if(flag == 0){
			ringPosOpp.erase(find(ringPosOpp.begin(),ringPosOpp.end(),index));
			myBoard[index.first][index.second] = empty;
		}
		else{
			ringPos.erase(find(ringPos.begin(),ringPos.end(),index));
			myBoard[index.first][index.second] = empty;
		}
	}
}
 
void Board :: opponent_player_Move(string s,int flag){
	vector<string> move;
	
	move = tokenize(s," ");
	int n = move.size();
	string h,p;
	for(int i = 0; i<n; i+=3){
		if(i%3 == 0){
			h = move[i+1];
			p = move[i+2];
			newOpp_player_Move(move[i],myInt(h),myInt(p),flag);
		}
	}
}


iPair Board::removeBadPossibleMove(iPair ring, vector<iPair> &possibleMove){
	int i,j,k,l, count =0;
	iPair index;
	//vertical down
	for(k = ring.second-1; k>=0;k--){
		if(myBoard[ring.first][k]!=myMarker)
			break;
		count++;
		if(count ==4 ) break;
	}
	if(count ==4){
		for(i=k-1;i>=0 && (myBoard[ring.first][i]==myMarker || myBoard[ring.first][i]==oppMarker);i--){
			//do nothing
		}
		if(i>=0 && myBoard[ring.first][i]==empty)
		{
			index = make_pair(ring.first,i);
			possibleMove.erase(find(possibleMove.begin(),possibleMove.end(),index));
		}
		return make_pair(ring.first,k);
	}



 	//vertical up
 	count =0;
 	for(k = ring.second+1; k<=10;k++){
		if(myBoard[ring.first][k]!=myMarker)
			break;
		count++;
		if(count ==4 ) break;
	}
	if(count ==4){
		for(i=k+1;i<=10 && (myBoard[ring.first][i]==myMarker || myBoard[ring.first][i]==oppMarker);i++){
			//do nothing
		}

		if( i<=10 && myBoard[ring.first][i]==empty){
			index = make_pair(ring.first,i);
			possibleMove.erase(find(possibleMove.begin(),possibleMove.end(),index));
		}
		return make_pair(ring.first,k);
	}

	//horizontal left
	count =0;
	for(k = ring.first-1; k>=0;k--){
		if(myBoard[k][ring.second]!=myMarker)
			break;
		count++;
		if(count ==4 ) break;
	}
	if(count ==4){
		for(i=k-1;i>=0 && (myBoard[i][ring.second]==myMarker || myBoard[i][ring.second]==oppMarker);i--){
			//do nothing
		}

		if(i>=0 && myBoard[i][ring.second]==empty){
			index = make_pair(i,ring.second);
			possibleMove.erase(find(possibleMove.begin(),possibleMove.end(),index));
		}
		return make_pair(k,ring.second);
	}

	//horizontal right
	count =0;
	for(k = ring.first+1; k<=10;k++){
		if(myBoard[k][ring.second]!=myMarker)
			break;
		count++;
		if(count ==4 ) break;
	}
	if(count ==4){
		for(i=k+1;i<=10 && (myBoard[i][ring.second]==myMarker || myBoard[i][ring.second]==oppMarker);i++){
			//do nothing
		}
		if(i<=10 && myBoard[i][ring.second]==empty){
			index = make_pair(i,ring.second);
			possibleMove.erase(find(possibleMove.begin(),possibleMove.end(),index));
		}
		return make_pair(k,ring.second);
	}

	//diagonal up
	count =0;
	for(j= ring.first+1,k = ring.second+1; j<=10 && k<=10;j++,k++){
		if(myBoard[j][k]!=myMarker)
			break;
		count++;
		if(count ==4 ) break;
	}
	if(count ==4){
		for(int i=j+1,l=k+1;i<=10 && l<=10 && (myBoard[i][l]==myMarker || myBoard[i][l]==oppMarker);i++,l++){
			//do nothing
		}
		if(i<=10 && l<=10 && myBoard[i][l]==empty){
			index = make_pair(i,l);
			possibleMove.erase(find(possibleMove.begin(),possibleMove.end(),index));
		}
		return make_pair(j,k);
	}

	//diagonal down
	count =0;
	for(j= ring.first-1,k = ring.second-1; j>=0 && k>=0;j--,k--){
		if(myBoard[j][k]!=myMarker)
			break;
		count++;
		if(count ==4 ) break;
	}
	if(count ==4){
		for(i=j-1,l=k-1;i>=0 && l>=0 && (myBoard[i][l]==myMarker || myBoard[i][l]==oppMarker);i--,l--){
			//do nothing
		}
		if(i>=0 && l>=0 && myBoard[i][l]==empty){
			index = make_pair(i,l);
			possibleMove.erase(find(possibleMove.begin(),possibleMove.end(),index));
		}
		return make_pair(j,k);
	}
	return make_pair(5,5);
}

void Board:: removeAll5ContinuousMarkers(){
	string heyMove;

	while(true){
		findContinuousMarkers(markerPos,myMarker);

		if(marker_5.size()){
		//selecting random 5 continuous markers --> to be changed after heuristic evaluation

			srand(rand()^time(0));
			int size = marker_5.size();
			int index = rand()%size;

			//getting start and end positions for markers to be removed.
			iPair RS = coord_to_hex(marker_5[index].first);
			iPair RE = coord_to_hex(marker_5[index].second);
			heyMove = "RS " + myString(RS.first)+ " " + myString(RS.second) + " RE "+ myString(RE.first)+" "+myString(RE.second);
			playerMove += " RS " + myString(RS.first)+ " " + myString(RS.second) + " RE "+ myString(RE.first)+" "+myString(RE.second);

			//selecting any random ring which has to be removed --> to be changed after heuristic
			size = ringPos.size();
			index = rand()%size;
			iPair X = coord_to_hex(ringPos[index]);
			heyMove += " X "+myString(X.first)+" "+myString(X.second);
			playerMove+= " X "+myString(X.first)+" "+myString(X.second);
			ringRemoved++;

			opponent_player_Move(heyMove,1);
		}
		else break;
	}

}
void Board::updatePossibleMovementsofRings(){
	//all possible movements of rings
	possibleMoves.clear();
	for(int i=0;i<ringPos.size();i++){
		possibleMovements(ringPos[i]);
	}

}

void Board::initialMove(){
	int h,p;
	iPair index;
	do{
		srand(rand()^time(0));
		h= rand()%3;
		if(h==0){
			p=0;
		}
		else
			p= rand()%(6*h);
		index = hex_to_coord(make_pair(h,p));
	}while(myBoard[index.first][index.second]!=0);
	
	iPair hex = coord_to_hex(index);
	playerMove = "P "+myString(hex.first)+" "+myString(hex.second);
	
}

iPair Board:: getEpicMove(iPair ring){

	int i,j,k,l, count =0;
	iPair index;
	//vertical down
	for(k = ring.second-1; k>=0;k--){
		if(myBoard[ring.first][k]!=oppMarker)
			break;
		count++;
		if(count ==4 ) break;
	}
	if(count ==4){
		for(i=k-1;i>=0 && (myBoard[ring.first][i]==myMarker || myBoard[ring.first][i]==oppMarker);i--){
			//do nothing
		}
		if(i>=0 && myBoard[ring.first][i]==empty)
		{
			index = make_pair(ring.first,i);
			return index;
		}
	}



 	//vertical up
 	count =0;
 	for(k = ring.second+1; k<=10;k++){
		if(myBoard[ring.first][k]!=oppMarker)
			break;
		count++;
		if(count ==4 ) break;
	}
	if(count ==4){
		for(i=k+1;i<=10 && (myBoard[ring.first][i]==myMarker || myBoard[ring.first][i]==oppMarker);i++){
			//do nothing
		}

		if( i<=10 && myBoard[ring.first][i]==empty){
			index = make_pair(ring.first,i);
			return index;
		}
	}

	//horizontal left
	count =0;
	for(k = ring.first-1; k>=0;k--){
		if(myBoard[k][ring.second]!=oppMarker)
			break;
		count++;
		if(count ==4 ) break;
	}
	if(count ==4){
		for(i=k-1;i>=0 && (myBoard[i][ring.second]==myMarker || myBoard[i][ring.second]==oppMarker);i--){
			//do nothing
		}

		if(i>=0 && myBoard[i][ring.second]==empty){
			index = make_pair(i,ring.second);
			return index;
		}
	}

	//horizontal right
	count =0;
	for(k = ring.first+1; k<=10;k++){
		if(myBoard[k][ring.second]!=oppMarker)
			break;
		count++;
		if(count ==4 ) break;
	}
	if(count ==4){
		for(i=k+1;i<=10 && (myBoard[i][ring.second]==myMarker || myBoard[i][ring.second]==oppMarker);i++){
			//do nothing
		}
		if(i<=10 && myBoard[i][ring.second]==empty){
			index = make_pair(i,ring.second);
			return index;
		}
	}

	//diagonal up
	count =0;
	for(j= ring.first+1,k = ring.second+1; j<=10 && k<=10;j++,k++){
		if(myBoard[j][k]!=oppMarker)
			break;
		count++;
		if(count ==4 ) break;
	}
	if(count ==4){
		for(int i=j+1,l=k+1;i<=10 && l<=10 && (myBoard[i][l]==myMarker || myBoard[i][l]==oppMarker);i++,l++){
			//do nothing
		}
		if(i<=10 && l<=10 && myBoard[i][l]==empty){
			index = make_pair(i,l);
			return index;
		}
	}

	//diagonal down
	count =0;
	for(j= ring.first-1,k = ring.second-1; j>=0 && k>=0;j--,k--){
		if(myBoard[j][k]!=oppMarker)
			break;
		count++;
		if(count ==4 ) break;
	}
	if(count ==4){
		for(i=j-1,l=k-1;i>=0 && l>=0 && (myBoard[i][l]==myMarker || myBoard[i][l]==oppMarker);i--,l--){
			//do nothing
		}
		if(i>=0 && l>=0 && myBoard[i][l]==empty){
			index = make_pair(i,l);
			return index;
		}
	}
	return make_pair(0,0);
}

void Board:: myMove(){

	playerMove = "";
	string heyMove;
	//initial 5 moves
	if(initial_counter<5){
		initialMove();
		initial_counter++;
		opponent_player_Move(playerMove,1);
		return;
	}

	//check if there exists multiple 5 continuous markers
	removeAll5ContinuousMarkers();
	if(ringRemoved>=3){
		//trim playerMove
		playerMove.erase(0, playerMove.find_first_not_of(" "));
		return;
	}

	//Priority2. flip if opponent has 4 continuous markers
	
	findContinuousMarkers(markerPosOpp,oppMarker);
	if(marker_4.size()){
		for(int i = 0; i<ringPos.size();i++){
			if(find(marker_4.begin(),marker_4.end(),ringPos[i])!=marker_4.end()){

				//remove the possiblemove which flip your continuous markers
				iPair rs = getEpicMove(ringPos[i]);
				//if epic move does not exists -> check for another ring
				if(rs.first ==0 && rs.second ==0) continue;

				iPair a = coord_to_hex(ringPos[i]);
				iPair b = coord_to_hex(rs);
				heyMove = "S "+myString(a.first)+" "+myString(a.second);
				heyMove +=" M "+myString(b.first)+" "+myString(b.second);
				playerMove += " S "+myString(a.first)+" "+myString(a.second);
				playerMove+=" M "+myString(b.first)+" "+myString(b.second);

				opponent_player_Move(heyMove,1);

				removeAll5ContinuousMarkers();
				//trim playerMove
				playerMove.erase(0, playerMove.find_first_not_of(" "));
				return;
			}
		}
	}


	//if 4 continuous markers

	updatePossibleMovementsofRings();
	findContinuousMarkers(markerPos, myMarker);
	if(marker_4.size()){
		for(int i = 0; i<ringPos.size();i++){
			if(find(marker_4.begin(),marker_4.end(),ringPos[i])!=marker_4.end()){

				//remove the possiblemove which flip your continuous markers
				iPair rs = removeBadPossibleMove(ringPos[i], possibleMoves[i]);

				int size = possibleMoves[i].size();
				if(size == 0) continue;
				int j = rand()%size;
				iPair a = coord_to_hex(ringPos[i]);
				iPair b = coord_to_hex(possibleMoves[i][j]);
				heyMove = "S "+myString(a.first)+" "+myString(a.second);
				heyMove +=" M "+myString(b.first)+" "+myString(b.second);
				playerMove += " S "+myString(a.first)+" "+myString(a.second);
				playerMove+=" M "+myString(b.first)+" "+myString(b.second);

				opponent_player_Move(heyMove,1);

				removeAll5ContinuousMarkers();
				//trim playerMove
				playerMove.erase(0, playerMove.find_first_not_of(" "));
				return;
			}
		}


		//move a ring to neighbour

		for(int i = 0; i<ringPos.size(); i++){
			//checking if the ring can be moved adjacent to 4 continuous markers
			for(int j = 0 ; j<possibleMoves[i].size(); j++){

				if(find(marker_4.begin(),marker_4.end(),possibleMoves[i][j])!=marker_4.end()){
					iPair a = coord_to_hex(ringPos[i]);
					iPair b = coord_to_hex(possibleMoves[i][j]);
					heyMove = "S "+myString(a.first)+" "+myString(a.second);
					heyMove +=" M "+myString(b.first)+" "+myString(b.second);
					playerMove += " S "+myString(a.first)+" "+myString(a.second);
					playerMove+=" M "+myString(b.first)+" "+myString(b.second);

					opponent_player_Move(heyMove,1);
					
					//check for 5 continuous

					removeAll5ContinuousMarkers();
					//trim playerMove
					playerMove.erase(0, playerMove.find_first_not_of(" "));
					return;
				}
			}
		}	
	}
		
	//again set the possible moves
	updatePossibleMovementsofRings();

	int i,j;
	iPair weightLoc;
	int maxWeight = INT_MIN;
	for(int k=0;k<ringPos.size();k++){
		weightLoc = getMaxWeightedMoveofRing(ringPos[k],k);
		if(weightLoc.first > maxWeight){
			i = k;
			j = weightLoc.second;
			maxWeight = weightLoc.first;
		}
	}


	iPair a = coord_to_hex(ringPos[i]);
	iPair b = coord_to_hex(possibleMoves[i][j]);

	heyMove = "S "+myString(a.first)+" "+myString(a.second);
	heyMove += " M "+myString(b.first)+" "+myString(b.second);
	playerMove += " S "+myString(a.first)+" "+myString(a.second);
	playerMove +=" M "+myString(b.first)+" "+myString(b.second);
	opponent_player_Move(heyMove,1);

	removeAll5ContinuousMarkers();

	//trim playerMove
	playerMove.erase(0, playerMove.find_first_not_of(" "));
}

void printPair(iPair pair){
	//cout<<"("<<pair.first-5<<","<<pair.second-5<<")";
}

void Board :: possibleMovements(iPair ring){

	vector<iPair> possibleMove;
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
				possibleMove.push_back(make_pair(i,j));
			}
			break;
		}
		else if(myBoard[i][j]==empty){
			for(;j>=0 && myBoard[i][j]==empty;j--){
				possibleMove.push_back(make_pair(i,j));
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
				possibleMove.push_back(make_pair(i,j));
			}
			break;
		}
		else if(myBoard[i][j]==empty){
			for(;j<=10 && myBoard[i][j]==empty;j++){
				possibleMove.push_back(make_pair(i,j));
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
				possibleMove.push_back(make_pair(i,j));
			}
			break;
		}
		else if(myBoard[i][j]==empty){
			for(;i<=10 && myBoard[i][j]==empty;i++){
				possibleMove.push_back(make_pair(i,j));
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
				possibleMove.push_back(make_pair(i,j));
			}
			break;
		}
		else if(myBoard[i][j]==empty){
			for(;i>=0 && myBoard[i][j]==empty;i--){
				possibleMove.push_back(make_pair(i,j));
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
				possibleMove.push_back(make_pair(i,j));
			}
			break;
		}
		else if(myBoard[i][j]==empty){
			for(;i<=10 && j<=10 && myBoard[i][j]==empty;i++,j++){
				possibleMove.push_back(make_pair(i,j));
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
				possibleMove.push_back(make_pair(i,j));
			}
			break;
		}
		else if(myBoard[i][j]==empty){
			for(;i>=0 && j>=0 && myBoard[i][j]==empty;i--,j--){
				possibleMove.push_back(make_pair(i,j));
			}
		}
	}
	possibleMoves.push_back(possibleMove);

}
//Helper function
void reset(bool* flag, int n){
	for(int i=0;i<n;i++){
		flag[i]=true;
	}
}

//this method gives end points of continuous markers
void Board:: findContinuousMarkers(vector<iPair> &marker, int markerValue){

	int i,j,k,p,q;
	int count = 0;
	bool flag[marker.size()];

	//reset flag, marker_5, marker_4
	reset(flag,marker.size());
	marker_5.clear();
	marker_4.clear();

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
				if(j<=10 && myBoard[j][p]!=invalidPos){
					marker_4.push_back(make_pair(j,p));
				}
				if(k>=0 && myBoard[j][p]!=invalidPos){
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
				if(j<=10 && myBoard[p][j] != invalidPos){
					marker_4.push_back(make_pair(p,j));
				}
				if(k>=0 && myBoard[p][k] != invalidPos){
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
				if(p<=10 && q<=10 && myBoard[p][q] != invalidPos){
					marker_4.push_back(make_pair(p,q));
				}
				if(j>=0 && k>=0 && myBoard[j][k] != invalidPos){
					marker_4.push_back(make_pair(j,k));
				}
			}

			//3 continuous markers.....
			flag[i]= false;
		}
	}
}


int Board::getWeight1(int board[11][11]){
	int countMarker =0;
	
	for(int i=0;i<11;i++){
		for(int j=0;j<11;j++){
			if(board[i][j]==myMarker)
				countMarker++;
		}
	}
	return countMarker;
}

void Board::update_board(int board[11][11],string s){
	iPair temp,index;

	vector<string> move;
	move = tokenize(s," ");
	
	//S h p
	temp = hex_to_coord( make_pair(myInt(move[1]),myInt(move[2])));
	//M h p
	index = hex_to_coord( make_pair(myInt(move[4]),myInt(move[5])));

	//vertical move
	if(temp.first == index.first){
		if(temp.second>index.second){
			for(int i = temp.second-1; i>index.second; i--){
				if(board[temp.first][i]>0){
					board[temp.first][i] = oppMarker+myMarker-board[temp.first][i];	
				}
			}
		}
		else if(temp.second<index.second){
			for(int i = temp.second+1; i<index.second; i++){
				if(board[temp.first][i]>0){
					board[temp.first][i] = oppMarker+myMarker-board[temp.first][i];
				}
			}
		}
	}

	//horizontal move
	else if(temp.second == index.second){
		if(temp.first>index.first){
			for(int i = temp.first-1; i>index.first; i--){
				if(board[i][temp.second]>0){
						board[i][temp.second] = oppMarker+myMarker-board[i][temp.second];
				}
			}
		}
		else if(temp.first<index.first){
			for(int i = temp.first+1; i<index.first; i++){
				if(board[i][temp.second]>0){
						board[i][temp.second] = oppMarker+myMarker-board[i][temp.second];
				}
			}
		}
	}

	//diagonal move
	else{
		int diff = abs(index.second - temp.second);
		if(temp.first<index.first && temp.second<index.second){
			for(int i = 1; i<diff; i++){
				if(board[temp.first+i][temp.second+i]>0){
					board[temp.first+i][temp.second+i] = oppMarker+myMarker-board[temp.first+i][temp.second+i];
				}
			}
		}
		else if(temp.first>index.first && temp.second>index.second){
			for(int i = 1; i<diff; i++){
				if(board[temp.first-i][temp.second-i]>0){
					
					board[temp.first-i][temp.second-i] = oppMarker+myMarker-board[temp.first-i][temp.second-i];
				}
					
			}
		}
	}
}

iPair Board::getMaxWeightedMoveofRing(iPair ring,int i){
	int j,p,q;
	
	int board[11][11];
	int maxWeight = INT_MIN,weight;
	
	iPair a = coord_to_hex(ring) , b ,res;
	res.second = 0;
	for(j=0;j<possibleMoves[i].size();j++){
		
		//copying board
		for(p=0;p<11;p++){
			for(q=0;q<11;q++){
				board[p][q] = myBoard[p][q];
			}
		}

		b = coord_to_hex(possibleMoves[i][j]);
		string move = "S "+myString(a.first)+" "+myString(a.second);
		move +=" M "+myString(b.first)+" "+myString(b.second);
		update_board(board,move);

		weight = getWeight1(board); 
		if(weight > maxWeight){
			maxWeight = weight;
			res.second = j;
		}
	}
	res.first = maxWeight;
	return res;
}