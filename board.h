#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <utility>
using namespace std;
typedef pair<int,int> iPair;

class Board{
	public:
	vector<iPair> marker_4;
	vector<pair<iPair,iPair> > marker_5;
	string playerMove;
	vector<iPair > markerPos;
	vector<iPair > markerPosOpp;
	vector<iPair > ringPos;
	vector<iPair > ringPosOpp;
	vector<vector<iPair> > possibleMoves;
	double cost[5];
	int myBoard[11][11];
	Board();
	iPair hex_to_coord(iPair hex);
	iPair coord_to_hex(iPair coord);
	void opponent_player_Move(string s,int flag);
	void newOpp_player_Move(string s, int h, int p,int flag);
	void flipMarker(iPair index, int val);
	void removeMarker(vector<iPair> &vec, iPair index);
	void moveRing(vector<iPair> &vec, iPair temp, iPair index);
	void movement(string s, iPair temp, iPair index,int marker);
	iPair coord_to_index(iPair coord);
	iPair index_to_coord(iPair index);
	void myMove();
	void printPair(iPair);
	void initialMove();
	void possibleMovements(iPair);
	void findContinuousMarkers(vector<iPair> &marker, int markerValue);
};

#endif /* BOARD_H_ */
