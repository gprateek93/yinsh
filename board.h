#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <utility>
using namespace std;

class Board{
	public:
	int maxHex = 5;
	vector<pair<int, int> > markerPos;
	vector<pair<int, int> > markerPosOpp;
	vector<pair<int, int> > ringPos;
	vector<pair<int, int> > ringPosOpp;
	int[11][11] myBoard = {0};
	pair<int, int> hex_to_coord(int h,int p);
	pair<int, int> coord_to_hex(int x, int y);
	void moveRing(int index, int h, int p);
	pair<int,int> coord_to_index(pair<int,int>);
	pair<int,int> index_to_coord(pair<int,int>);
};

#endif /* BOARD_H_ */
