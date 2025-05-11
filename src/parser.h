#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <queue>
#include <stack>
#include <limits>



using namespace std;

class net
{
public:
    //////////////////set////////////////////
    void setID ( int ID ) { _ID = ID; }
    void setXs ( int xs ) { _xs = xs; }
    void setYs ( int ys ) { _ys = ys; }
    void setXt ( int xt ) { _xt = xt; }
    void setYt ( int yt ) { _yt = yt; }

    //////////////////get////////////////////
    int getXs ( ) { return _xs; }
    int getYs ( ) { return _ys; }
    int getXt ( ) { return _xt; }
    int getYt ( ) { return _yt; }
    int getID ( ) { return _ID; }

private:
    int _xs;
    int _ys;
    int _xt;
    int _yt;
    int _ID;
};
//
class Pcost
{
public:
	/////////////////set///////////////////
	void setRight ( float r ) { _right = r; }
	void setUp ( float u ) { _up = u; }
	
	/////////////////get///////////////////
	float getRight ( ) { return _right; }
	float getUp ( ) { return _up; }
	
private:
	float _right;
	float _up;
};

class Path
{//
public:
	int cost;
	/////////////////set///////////////////
	void setCost ( float c ) { _cost = c; }
	void setPi ( int p ) { _pi = p; }
	void setX ( int x ) { _x = x; }
	void setY ( int y ) { _y = y; }
	
	/////////////////get///////////////////
	float getCost ( ) { return _cost; }
	int getPi ( ) { return _pi; }
	int getX ( ) { return _x; }
	int getY ( ) { return _y; }
	
private:
	float _cost;
	int _pi;	//from 0:NULL, 1:up, 2:right, 3:bottom, 4:left
	int _x;
	int _y;
};

class glob
{
public:
/////////////////////////////functions/////////////////////////////

    void parser( int argc, char **argv );
    void output( int argc, char **argv );

/////////////////////////////declaration/////////////////////////////

    //number of horizontal, vertical tiles
    int hori;
    int vert;

    //capacity
    int capacity;

    //non default cost
    vector< net > nets;

    //start x y;
    int sx;
    int sy;

    //target x y;
    int tx;
    int ty;
};

#endif // PARSER_H
