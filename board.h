#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <utility>
using namespace std;
typedef pair<int,int> iPair;

class Board{
	public:
	vector<iPair > markerPos;
	vector<iPair > markerPosOpp;
	vector<iPair > ringPos;
	vector<iPair > ringPosOpp;
	int myBoard[11][11] = {0};
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
};

#endif /* BOARD_H_ */
