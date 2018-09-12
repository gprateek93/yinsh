#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int Max = 0;
int Min = 1;

typedef struct node{
	int positions[9];
	int type;
	int utility;
	vector<struct node*> children;
}node;


class Solution{
	Board board;
	possibleMoves();

};

node* new_node(int type, int* positions, int position){
	node* newNode = new node();
	for(int i=0; i<9; i++){
		newNode->positions[i] = positions[i];
		//cout<<newNode->positions[i]<<" ";
	}
	newNode->type = type;
	newNode->positions[position] = type;
	return newNode;
}

bool is_terminal(node* state){
	for(int i=0; i<8; i++){

	}
	return true;
}

int utility(node* state){
	return 1;

}
/*
function M AX -V ALUE (state) returns a utility value
if T ERMINAL -T EST(state) then return UTILITY(state)
v ← −∞
for each a in ACTIONS(state) do
v ← M AX(v , MIN -V ALUE(R ESULT (s, a)))
return v
*/

void constructMinMaxTree(node* root){
	// init step and call min_value on all possible moves
}



int main(){
	node* root = new node();
	root->type = Max;
	constructMinMaxTree(root);
	return 0;
}
