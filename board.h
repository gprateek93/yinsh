#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <utility>
using namespace std;
typedef pair<int,int> iPair;

class Board{
	public:
	Board();
	vector<iPair > markerPos;
	vector<iPair > markerPosOpp;
	vector<iPair > ringPos;
	vector<iPair > ringPosOpp;
	vector<iPair> possibleMoves[5];
	vector< pair<iPair,iPair> > marker_5;
	vector<iPair> marker_4;
	double cost[5];
	int myBoard[11][11];
	iPair hex_to_coord(iPair hex);
	iPair coord_to_hex(iPair coord);
	void opponentMove(string s);
	void newOppMove(string s, int h, int p);
	void flipMarker(iPair index, int val);
	void removeMarker(vector<iPair> &vec, iPair index);
	void moveRing(vector<iPair> &vec, iPair temp, iPair index);
	void movement(string s, iPair temp, iPair index);
	iPair coord_to_index(iPair coord);
	iPair index_to_coord(iPair index);
	void myMove();
	void printPair(iPair);
	void initialMove();
	void possibleMovements(iPair,int);
	void findContinuousMarkers(vector<iPair> &marker, int markerValue);
};

#endif /* BOARD_H_ */
