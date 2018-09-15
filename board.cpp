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
int initial_counter = 0;
iPair temp;

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
			newOpp_player_Move(move[i],myInt(h),myInt(p),flag);
		}
	}
}

/*iPair Board::coord_to_index(iPair coord){
	int x = coord.first +5;
	int y = coord.second +5;
	return make_pair(x,y);
}

iPair Board::index_to_coord(iPair index){
	int x = index.first +5;
	int y = index.second +5;
	return make_pair(x,y);
}*/

void Board:: myMove(){

	//initial 5 moves
	if(initial_counter<5){
		initialMove();
		//cout<<playerMove<<" here"<<endl;
		initial_counter++;
		opponent_player_Move(playerMove,1);
		return;
	}
	marker_5.clear();
	findContinuousMarkers(markerPos,myMarker);
	//all possible movements of rings
	possibleMoves.clear();
	for(int i=0;i<ringPos.size();i++){
		possibleMovements(ringPos[i]);
	}

	if(marker_5.size()){
		//selecting random 5 continuous markers --> to be changed after heuristic evaluation
		srand(rand()^time(0));
		int size = marker_5.size();
		int index = rand()%size;

		//getting start and end positions for markers to be removed.
		iPair RS = coord_to_hex(marker_5[index].first);
		iPair RE = coord_to_hex(marker_5[index].second);
		playerMove = "RS " + myString(RS.first)+ " " + myString(RS.second) + " RE "+ myString(RE.first)+" "+myString(RE.second);

		//selecting any random ring which has to be removed --> to be changed after heuristic
		size = ringPos.size();
		index = rand()%size;
		iPair X = coord_to_hex(ringPos[index]);
		playerMove+= " X "+myString(X.first)+" "+myString(X.second);
		ringRemoved++;
		if(ringRemoved==3) return;

		opponent_player_Move(playerMove,1);

		int i,j;
		size = ringPos.size();
		do{
			i = rand()%size;
		}while(!possibleMoves[i].size());
		j = rand()%possibleMoves[i].size();
		//cout<<"here"<<endl;
		string heyMove;
		iPair a = coord_to_hex(ringPos[i]);
		iPair b = coord_to_hex(possibleMoves[i][j]);
		heyMove = "S "+myString(a.first)+" "+myString(a.second);
		heyMove+= " M "+myString(b.first)+" "+myString(b.second);
		playerMove+= " S "+myString(a.first)+" "+myString(a.second);
		playerMove+=" M "+myString(b.first)+" "+myString(b.second);
		opponent_player_Move(heyMove,1);
	}
	else{

		int flag = 0;   //for breaking outer loops

		//Game Play
		while(true){
			//cout<<"here"<<endl;

			srand(rand()^time(0));
			int size = ringPos.size();
			//cout<<size<<endl;
			//cout<<ringPos[0].first<<" "<<ringPos[0].second<<endl;

			/*for(int i = 0; i<size;i++){
				if(find(marker_4.begin(),marker_4.end(),ringPos[i])!=marker_4.end()){
					flag = 1;
					int j = possibleMoves[i].size();
					rand()%j;
					iPair a = coord_to_hex(ringPos[i]);
					iPair b = coord_to_hex(possibleMoves[i][j]);
					playerMove = "S "+myString(a.first)+" "+myString(a.second);
					playerMove+=" M "+myString(b.first)+" "+myString(b.second);
					size = ringPos.size();
					index = rand()%size;
					iPair X = coord_to_hex(ringPos[index]);
					playerMove+= " X "+myString(X.first)+" "+myString(X.second);
				}
			}

			if(flag == 1)
				break;*/

			/*for(int i = 0; i<size; i++){
				////cout<<"here"<<endl;
				////cout<<possibleMoves[i].size()<<endl;
				////cout<<"here"<<endl;
				//checking if the ring can be moved adjacent to 4 continuous markers
				for(int j = 0 ; j<possibleMoves[i].size(); j++){
					////cout<<"here"<<endl;
					if(find(marker_4.begin(),marker_4.end(),possibleMoves[i][j])!=marker_4.end()){
						iPair a = coord_to_hex(ringPos[i]);
						iPair b = coord_to_hex(possibleMoves[i][j]);
						playerMove = "S "+myString(a.first)+" "+myString(a.second);
						playerMove+=" M "+myString(b.first)+" "+myString(b.second);
						flag = 1;
						break;
					}
				}
				if(flag == 1){
					break;
				}
			}
			if(flag == 1)
				break;
			*/
			//selecting random ring and random move
			int i,j;
			do{
				i = rand()%size;
			}while(!possibleMoves[i].size());
			j = rand()%possibleMoves[i].size();
			//cout<<"here"<<endl;
			iPair a = coord_to_hex(ringPos[i]);
			iPair b = coord_to_hex(possibleMoves[i][j]);
			playerMove = "S "+myString(a.first)+" "+myString(a.second);
			playerMove+=" M "+myString(b.first)+" "+myString(b.second);
			opponent_player_Move(playerMove,1);
			marker_5.clear();
			findContinuousMarkers(markerPos,myMarker);
			////cout<< playerMove<<endl;
			string heyMove;
			if(marker_5.size()){
				//selecting random 5 continuous markers --> to be changed after heuristic evaluation
				srand(rand()^time(0));
				int size = marker_5.size();
				int index = rand()%size;

				//getting start and end positions for markers to be removed.
				iPair RS = coord_to_hex(marker_5[index].first);
				iPair RE = coord_to_hex(marker_5[index].second);
				heyMove = "RS " + myString(RS.first)+ " " + myString(RS.second) + " RE "+ myString(RE.first)+" "+myString(RE.second);
				playerMove+= " RS " + myString(RS.first)+ " " + myString(RS.second) + " RE "+ myString(RE.first)+" "+myString(RE.second);
				//selecting any random ring which has to be removed --> to be changed after heuristic
				size = ringPos.size();
				index = rand()%size;
				iPair X = coord_to_hex(ringPos[index]);
				heyMove+=" X "+myString(X.first)+" "+myString(X.second);
				playerMove+= " X "+myString(X.first)+" "+myString(X.second);
				ringRemoved++;
				opponent_player_Move(heyMove,1);
			}
			break;
		}
		//cout<<"here"<<endl;
	}

    // possible moves
	/*for(i=0;i<5;i++){
		//cout<<"[";
		printPair(ringPos[i]);
		//cout<<": ";
		for(int j=0;j<possibleMoves[i].size();j++){
			//cout<<" ";
			printPair(possibleMoves[i][j]);
		}
		//cout<<"]"<<endl;
	}*/
}

void Board:: printPair(iPair pair){
	//cout<<"("<<pair.first-5<<","<<pair.second-5<<")";
}

void Board::initialMove(){
	int x,y;
	do{
		srand(rand()^time(0));
		x= rand()%5 + 3;
		y= rand()%4 + 3;
	}while(myBoard[x][y]!=0);
	//cout<<"P "<<x<<" "<<y<<endl;
	iPair hex = coord_to_hex(make_pair(x,y));
	playerMove = "P "+myString(hex.first)+" "+myString(hex.second);
	//myBoard[x][y]=myRing;
	//ringPos.push_back(make_pair(x,y));
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
