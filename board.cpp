/*
 * board.cpp
 *
 *  Created on: 10-Sep-2018
 *      Author: cmkmanwani
 */

#include <iostream>
#include <vector>
#include <utility>
#include "board.h"
using namespace std;

pair<int,int> hex_to_coord(int h,int p){
	pair<int,int> coord;
	int x,y;
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

pair<int,int> coord_to_hex(int x, int y){
	pair<int,int> hex;
	int h,p;
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




