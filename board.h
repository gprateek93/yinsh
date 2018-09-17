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
	int myBoard[11][11];
	int ringRemoved;

	Board();
	iPair hex_to_coord(iPair hex);
	iPair coord_to_hex(iPair coord);
	void opponent_player_Move(string s,int flag);
	void newOpp_player_Move(string s, int h, int p,int flag);
	void flipMarker(iPair index, int val);
	void removeMarker(vector<iPair> &vec, iPair index);
	void moveRing(vector<iPair> &vec, iPair temp, iPair index);
	void movement(string s, iPair temp, iPair index,int marker);
	void myMove();
	void initialMove();
	void possibleMovements(iPair);
	void findContinuousMarkers(vector<iPair> &marker, int markerValue);
	iPair removeBadPossibleMove(iPair ring, vector<iPair> &possibleMove);
	int getWeight1(int myBoard[11][11]);
	int getWeight2(int myBoard[11][11]);
	iPair getMaxWeightedMoveofRing(iPair ring,int);
	void update_board(int board[11][11],string);
	void removeAll5ContinuousMarkers();
	void updatePossibleMovementsofRings();
	iPair getEpicMove(iPair ring);
};

#endif /* BOARD_H_ */
